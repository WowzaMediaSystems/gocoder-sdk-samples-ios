//
//  VideoViewController.swift
//  SDKSampleApp.swift
//
//  This code and all components (c) Copyright 2015-2016, Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//


import UIKit
import WowzaGoCoderSDK

class VideoViewController: UIViewController, WZStatusCallback, WZVideoSink, WZAudioSink {
    
    //MARK: - Class Member Variables
    
    let SDKSampleSavedConfigKey = "SDKSampleSavedConfigKey"
    let SDKSampleAppLicenseKey = "GSDK-4642-0003-0DA7-5E52-572D"
    let BlackAndWhiteEffectKey = "BlackAndWhiteKey"
    
    @IBOutlet weak var broadcastButton:UIButton!
    @IBOutlet weak var settingsButton:UIButton!
    @IBOutlet weak var switchCameraButton:UIButton!
    @IBOutlet weak var torchButton:UIButton!
    @IBOutlet weak var micButton:UIButton!
    
    
    var goCoder:WowzaGoCoder?
    var goCoderConfig:WowzaConfig!
    
    var receivedGoCoderEventCodes = Array<WZEvent>()
    
    var blackAndWhiteVideoEffect = false
    
    var goCoderRegistrationChecked = false

    
    //MARK: - Methods
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Reload any saved data
        blackAndWhiteVideoEffect = NSUserDefaults.standardUserDefaults().boolForKey(BlackAndWhiteEffectKey)
        WowzaGoCoder.setLogLevel(.Default)
        
        if let savedConfig:NSData = NSUserDefaults.standardUserDefaults().objectForKey(SDKSampleSavedConfigKey) as? NSData {
            if let wowzaConfig = NSKeyedUnarchiver.unarchiveObjectWithData(savedConfig) as? WowzaConfig {
                goCoderConfig = wowzaConfig
            }
            else {
                goCoderConfig = WowzaConfig()
            }
        }
        else {
            goCoderConfig = WowzaConfig()
        }
        
        // Log version and platform info
        print("WowzaGoCoderSDK version =\n major: \(WZVersionInfo.majorVersion())\n minor: \(WZVersionInfo.minorVersion())\n revision: \(WZVersionInfo.revision())\n build: \(WZVersionInfo.buildNumber())\n string: \(WZVersionInfo.string())\n verbose string: \(WZVersionInfo.verboseString())")
        
        print("Platform Info:\n\(WZPlatformInfo.string())")
        
        if let goCoderLicensingError = WowzaGoCoder.registerLicenseKey(SDKSampleAppLicenseKey) {
            self.showAlert("GoCoder SDK Licensing Error", error: goCoderLicensingError)
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        
        let savedConfigData = NSKeyedArchiver.archivedDataWithRootObject(goCoderConfig)
        NSUserDefaults.standardUserDefaults().setObject(savedConfigData, forKey: SDKSampleSavedConfigKey)
        NSUserDefaults.standardUserDefaults().synchronize()
        
        // Update the configuration settings in the GoCoder SDK
        if (goCoder != nil) {
            goCoder?.config = goCoderConfig
            blackAndWhiteVideoEffect = NSUserDefaults.standardUserDefaults().boolForKey(BlackAndWhiteKey)
        }
    }

    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        goCoder?.cameraPreview?.previewLayer?.frame = view.bounds
    }
    
    override func viewDidAppear(animated: Bool) {
        super.viewDidAppear(animated)
        
        if !goCoderRegistrationChecked {
            goCoderRegistrationChecked = true
            if let goCoderLicensingError = WowzaGoCoder.registerLicenseKey(SDKSampleAppLicenseKey) {
                self.showAlert("GoCoder SDK Licensing Error", error: goCoderLicensingError)
            }
            else {
                // Initialize the GoCoder SDK
                if let goCoder = WowzaGoCoder.sharedInstance() {
                    self.goCoder = goCoder
                    
                    // Request camera and microphone permissions
                    WowzaGoCoder.requestPermissionForType(.Camera, response: { (permission) in
                        print("Camera permission is: \(permission == .Authorized ? "authorized" : "denied")")
                    })
                    
                    WowzaGoCoder.requestPermissionForType(.Microphone, response: { (permission) in
                        print("Microphone permission is: \(permission == .Authorized ? "authorized" : "denied")")
                    })
                    
                    self.goCoder?.registerVideoSink(self)
                    self.goCoder?.registerAudioSink(self)
                    self.goCoder?.config = self.goCoderConfig
                    
                    // Specify the view in which to display the camera preview
                    self.goCoder?.cameraView = self.view
                    
                    // Start the camera preview
                    self.goCoder?.cameraPreview?.startPreview()
                }
                
                self.updateUIControls()
                
            }
        }
    }
    
    override func prefersStatusBarHidden() -> Bool {
        return true
    }
    

    //MARK - UI Action Methods
    
    @IBAction func didTapBroadcastButton(sender:AnyObject?) {
        // Ensure the minimum set of configuration settings have been specified necessary to
        // initiate a broadcast streaming session
        if let configError = goCoder?.config.validateForBroadcast() {
            self.showAlert("Incomplete Streaming Settings", error: configError)
        }
        else {
            // Disable the U/I controls
            broadcastButton.enabled    = false
            torchButton.enabled        = false
            switchCameraButton.enabled = false
            settingsButton.enabled     = false
            
            if goCoder?.status.state == .Running {
                goCoder?.endStreaming(self)
            }
            else {
                receivedGoCoderEventCodes.removeAll()
                goCoder?.startStreaming(self)
                let audioMuted = goCoder?.audioMuted ?? false
                micButton.setImage(UIImage(named: audioMuted ? "mic_off_button" : "mic_on_button"), forState: .Normal)
            }
        }
    }
    
    @IBAction func didTapSwitchCameraButton(sender:AnyObject?) {
        if let otherCamera = goCoder?.cameraPreview?.otherCamera() {
            if !otherCamera.supportsWidth(goCoderConfig.videoWidth) {
                goCoderConfig.loadPreset(otherCamera.supportedPresetConfigs.last!.toPreset())
                goCoder?.config = goCoderConfig
            }
            
            goCoder?.cameraPreview?.switchCamera()
            torchButton.setImage(UIImage(named: "torch_on_button"), forState: .Normal)
            self.updateUIControls()
        }
    }
    
    @IBAction func didTapTorchButton(sender:AnyObject?) {
        var newTorchState = goCoder?.cameraPreview?.camera?.torchOn ?? true
        newTorchState = !newTorchState
        goCoder?.cameraPreview?.camera?.torchOn = newTorchState
        torchButton.setImage(UIImage(named: newTorchState ? "torch_off_button" : "torch_on_button"), forState: .Normal)
    }
    
    @IBAction func didTapMicButton(sender:AnyObject?) {
        var newMutedState = self.goCoder?.audioMuted ?? true
        newMutedState = !newMutedState
        goCoder?.audioMuted = newMutedState
        micButton.setImage(UIImage(named: newMutedState ? "mic_off_button" : "mic_on_button"), forState: .Normal)
    }
    
    @IBAction func didTapSettingsButton(sender:AnyObject?) {
        if let settingsNavigationController = UIStoryboard(name: "GoCoderSettings", bundle: nil).instantiateViewControllerWithIdentifier("settingsNavigationController") as? UINavigationController {
        
            if let settingsViewController = settingsNavigationController.topViewController as? SettingsViewController {
                settingsViewController.addAllSections()
                settingsViewController.removeDisplaySection(.RecordVideoLocally)
                let viewModel = SettingsViewModel(sessionConfig: goCoderConfig)
                viewModel.supportedPresetConfigs = goCoder?.cameraPreview?.camera?.supportedPresetConfigs
                settingsViewController.viewModel = viewModel
            }
            
            
            self.presentViewController(settingsNavigationController, animated: true, completion: nil)
        }
    }
    
    func updateUIControls() {
        if self.goCoder?.status.state != .Idle && self.goCoder?.status.state != .Running {
            // If a streaming broadcast session is in the process of starting up or shutting down,
            // disable the UI controls
            self.broadcastButton.enabled    = false
            self.torchButton.enabled        = false
            self.switchCameraButton.enabled = false
            self.settingsButton.enabled     = false
            self.micButton.hidden           = true
            self.micButton.enabled          = false
        }
        else {
            // Set the UI control state based on the streaming broadcast status, configuration,
            // and device capability
            self.broadcastButton.enabled    = true
            self.switchCameraButton.enabled = self.goCoder?.cameraPreview?.cameras?.count > 1
            self.torchButton.enabled        = self.goCoder?.cameraPreview?.camera?.hasTorch ?? false
            let isStreaming                 = self.goCoder?.isStreaming ?? false
            self.settingsButton.enabled     = !isStreaming
            // The mic icon should only be displayed while streaming and audio streaming has been enabled
            // in the GoCoder SDK configuration setiings
            self.micButton.enabled          = isStreaming && self.goCoderConfig.audioEnabled
            self.micButton.hidden           = !self.micButton.enabled
        }
    }
    
    
    //MARK: - WZStatusCallback Protocol Instance Methods
    
    func onWZStatus(status: WZStatus!) {
        switch (status.state) {
        case .Idle:
            dispatch_async(dispatch_get_main_queue()) { () -> Void in
                self.broadcastButton.setImage(UIImage(named: "start_button"), forState: .Normal)
                self.updateUIControls()
            }
            
        case .Running:
            dispatch_async(dispatch_get_main_queue()) { () -> Void in
                self.broadcastButton.setImage(UIImage(named: "stop_button"), forState: .Normal)
                self.updateUIControls()
            }
        case .Stopping, .Starting:
            dispatch_async(dispatch_get_main_queue()) { () -> Void in
                self.updateUIControls()
            }
        }
        
    }
    
    func onWZEvent(status: WZStatus!) {
        // If an event is reported by the GoCoder SDK, display an alert dialog describing the event,
        // but only if we haven't already shown an alert for this event
        
        dispatch_async(dispatch_get_main_queue()) { () -> Void in
            if !self.receivedGoCoderEventCodes.contains(status.event) {
                self.receivedGoCoderEventCodes.append(status.event)
                self.showAlert("Live Streaming Event", status: status)
            }
            
            self.updateUIControls()
        }
    }
    
    func onWZError(status: WZStatus!) {
        // If an error is reported by the GoCoder SDK, display an alert dialog containing the error details
        dispatch_async(dispatch_get_main_queue()) { () -> Void in
            self.showAlert("Live Streaming Error", status: status)
            self.updateUIControls()
        }
    }
    
    
    //MARK: - WZVideoSink Protocol Methods
    
    func videoFrameWasCaptured(imageBuffer: CVImageBuffer, framePresentationTime: CMTime, frameDuration: CMTime) {
        if goCoder != nil && goCoder!.isStreaming && blackAndWhiteVideoEffect {
            // convert frame to b/w using CoreImage tonal filter
            var frameImage = CIImage(CVImageBuffer: imageBuffer)
            if let grayFilter = CIFilter(name: "CIPhotoEffectTonal") {
                grayFilter.setValue(frameImage, forKeyPath: "inputImage")
                if let outImage = grayFilter.outputImage {
                    frameImage = outImage
                    
                    let context = CIContext(options: nil)
                    context.render(frameImage, toCVPixelBuffer: imageBuffer)
                }
                
            }
        }
    }
    
    
    //MARK: - WZAudioSink Protocol Methods
    
    func audioLevelDidChange(level: Float) {
//        print("Audio level did change: \(level)");
    }
    
    
    //MARK: - Alerts
    
    func showAlert(title:String, status:WZStatus) {
        let alertController = UIAlertController(title: title, message: status.description, preferredStyle: .Alert)
        
        let action = UIAlertAction(title: "OK", style: .Default, handler: nil)
        alertController.addAction(action)
        
        self.presentViewController(alertController, animated: true, completion: nil)
    }
    
    func showAlert(title:String, error:NSError) {
        let alertController = UIAlertController(title: title, message: error.localizedDescription, preferredStyle: .Alert)
        
        let action = UIAlertAction(title: "OK", style: .Default, handler: nil)
        alertController.addAction(action)
        
        self.presentViewController(alertController, animated: true, completion: nil)
    }

    

}

