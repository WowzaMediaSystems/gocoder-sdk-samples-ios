//
//  VideoViewController.swift
//  SDKSampleApp.swift
//
//  This code and all components © 2015 – 2019 Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//


import UIKit
import WowzaGoCoderSDK

class VideoViewController: UIViewController, WOWZBroadcastStatusCallback, WOWZVideoSink, WOWZAudioSink {

    //MARK: - Class Member Variables

    let SDKSampleSavedConfigKey = "SDKSampleSavedConfigKey"
    let SDKSampleAppLicenseKey = "GOSK-8945-010C-E544-5344-FBAB"
    let BlackAndWhiteEffectKey = "BlackAndWhiteKey"
    let BitmapOverlayEffectKey = "BitmapOverlayKey"

    @IBOutlet weak var broadcastButton:UIButton!
    @IBOutlet weak var settingsButton:UIButton!
    @IBOutlet weak var switchCameraButton:UIButton!
    @IBOutlet weak var torchButton:UIButton!
    @IBOutlet weak var micButton:UIButton!
    @IBOutlet weak var bitmapOverlayImgView:UIImageView!


    var goCoder:WowzaGoCoder?
    var goCoderConfig:WowzaConfig!

    var receivedGoCoderEventCodes = Array<WOWZBroadcastEvent>()

    var blackAndWhiteVideoEffect = false
    var bitmapOverlayVideoEffect = false /// Not supported in swift version
    var goCoderRegistrationChecked = false


    //MARK: - Methods
    override func viewDidLoad() {
        super.viewDidLoad()

        // Reload any saved data
        blackAndWhiteVideoEffect = UserDefaults.standard.bool(forKey: BlackAndWhiteEffectKey)
        bitmapOverlayVideoEffect = UserDefaults.standard.bool(forKey: BitmapOverlayEffectKey)
        WowzaGoCoder.setLogLevel(.default)

        if let savedConfig:Data = UserDefaults.standard.object(forKey: SDKSampleSavedConfigKey) as? Data {
            if let wowzaConfig = NSKeyedUnarchiver.unarchiveObject(with: savedConfig) as? WowzaConfig {
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
        print("WowzaGoCoderSDK version =\n major: \(WOWZVersionInfo.majorVersion())\n minor: \(WOWZVersionInfo.minorVersion())\n revision: \(WOWZVersionInfo.revision())\n build: \(WOWZVersionInfo.buildNumber())\n string: \(WOWZVersionInfo.string())\n verbose string: \(WOWZVersionInfo.verboseString())")

        print("Platform Info:\n\(WOWZPlatformInfo.string())")

        if let goCoderLicensingError = WowzaGoCoder.registerLicenseKey(SDKSampleAppLicenseKey) {
            self.showAlert("GoCoder SDK Licensing Error", error: goCoderLicensingError as NSError)
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)

        let savedConfigData = NSKeyedArchiver.archivedData(withRootObject: goCoderConfig!)
        UserDefaults.standard.set(savedConfigData, forKey: SDKSampleSavedConfigKey)
        UserDefaults.standard.synchronize()

        // Update the configuration settings in the GoCoder SDK
        if (goCoder != nil) {
            goCoder?.config = goCoderConfig
            blackAndWhiteVideoEffect = UserDefaults.standard.bool(forKey: BlackAndWhiteKey)
            bitmapOverlayVideoEffect = UserDefaults.standard.bool(forKey: BitmapOverlayKey)
        }
    }

    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        goCoder?.cameraPreview?.previewLayer?.frame = view.bounds
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)

        if !goCoderRegistrationChecked {
            if let goCoderLicensingError = WowzaGoCoder.registerLicenseKey(SDKSampleAppLicenseKey) {
                self.showAlert("GoCoder SDK Licensing Error", error: goCoderLicensingError as NSError)
            }
            else {
                goCoderRegistrationChecked = true
                
                // Initialize the GoCoder SDK
                if let goCoder = WowzaGoCoder.sharedInstance() {
                    self.goCoder = goCoder

                    // Request camera and microphone permissions
                    WowzaGoCoder.requestPermission(for: .camera, response: { (permission) in
                        print("Camera permission is: \(permission == .authorized ? "authorized" : "denied")")
                    })

                    WowzaGoCoder.requestPermission(for: .microphone, response: { (permission) in
                        print("Microphone permission is: \(permission == .authorized ? "authorized" : "denied")")
                    })

                    self.goCoder?.register(self as WOWZAudioSink)
                    self.goCoder?.register(self as WOWZVideoSink)
                    self.goCoder?.config = self.goCoderConfig

                    // Specify the view in which to display the camera preview
                    self.goCoder?.cameraView = self.view

                    // Start the camera preview
                    self.goCoder?.cameraPreview?.start()
                }

                self.updateUIControls()
            }
        }
        else{
            // Start the camera preview
            self.goCoder?.cameraPreview?.start()
        }
    }
    
    override func viewDidDisappear(_ animated: Bool) {
        self.goCoder?.cameraPreview?.stop()
    }

    override var prefersStatusBarHidden:Bool {
        return true
    }



    //MARK - UI Action Methods

    @IBAction func didTapBroadcastButton(_ sender:AnyObject?) {
        // Ensure the minimum set of configuration settings have been specified necessary to
        // initiate a broadcast streaming session
        if let configError = goCoder?.config.validateForBroadcast() {
            self.showAlert("Incomplete Streaming Settings", error: configError as NSError)
        }
        else {
            // Disable the U/I controls
            broadcastButton.isEnabled    = false
            torchButton.isEnabled        = false
            switchCameraButton.isEnabled = false
            settingsButton.isEnabled     = false

            if goCoder?.status.state == .broadcasting {
                goCoder?.endStreaming(self)
            }
            else {
                receivedGoCoderEventCodes.removeAll()
                goCoder?.startStreaming(self)
                let audioMuted = goCoder?.isAudioMuted ?? false
                micButton.setImage(UIImage(named: audioMuted ? "mic_off_button" : "mic_on_button"), for: UIControl.State())
            }
        }
    }

    @IBAction func didTapSwitchCameraButton(_ sender:AnyObject?) {
        if let otherCamera = goCoder?.cameraPreview?.otherCamera() {
            if !otherCamera.supportsWidth(goCoderConfig.videoWidth) {
                goCoderConfig.load(otherCamera.supportedPresetConfigs.last!.toPreset())
                goCoder?.config = goCoderConfig
            }

            goCoder?.cameraPreview?.switchCamera()
            torchButton.setImage(UIImage(named: "torch_on_button"), for: UIControl.State())
            self.updateUIControls()
        }
    }

    @IBAction func didTapTorchButton(_ sender:AnyObject?) {
        var newTorchState = goCoder?.cameraPreview?.camera?.isTorchOn ?? true
        newTorchState = !newTorchState
        goCoder?.cameraPreview?.camera?.isTorchOn = newTorchState
        torchButton.setImage(UIImage(named: newTorchState ? "torch_off_button" : "torch_on_button"), for: UIControl.State())
    }

    @IBAction func didTapMicButton(_ sender:AnyObject?) {
        var newMutedState = self.goCoder?.isAudioMuted ?? true
        newMutedState = !newMutedState
        goCoder?.isAudioMuted = newMutedState
        micButton.setImage(UIImage(named: newMutedState ? "mic_off_button" : "mic_on_button"), for: UIControl.State())
    }

    @IBAction func didTapSettingsButton(_ sender:AnyObject?) {
        if let settingsNavigationController = UIStoryboard(name: "AppSettings", bundle: nil).instantiateViewController(withIdentifier: "settingsNavigationController") as? UINavigationController {

            if let settingsViewController = settingsNavigationController.topViewController as? SettingsViewController {
                settingsViewController.addAllSections()
                settingsViewController.removeDisplay(.recordVideoLocally)
                settingsViewController.removeDisplay(.backgroundMode)
                let viewModel = SettingsViewModel(sessionConfig: goCoderConfig)
                viewModel?.supportedPresetConfigs = goCoder?.cameraPreview?.camera?.supportedPresetConfigs
                settingsViewController.viewModel = viewModel!
            }
            
            self.present(settingsNavigationController, animated: true, completion: nil)
        }
    }

    func updateUIControls() {
        if self.goCoder?.status.state != .idle && self.goCoder?.status.state != .broadcasting {
            // If a streaming broadcast session is in the process of.connecting up or shutting down,
            // disable the UI controls
            self.broadcastButton.isEnabled    = false
            self.torchButton.isEnabled        = false
            self.switchCameraButton.isEnabled = false
            self.settingsButton.isEnabled     = false
            self.micButton.isHidden           = true
            self.micButton.isEnabled          = false
        }
        else {
            // Set the UI control state based on the streaming broadcast status, configuration,
            // and device capability
            self.broadcastButton.isEnabled    = true
            self.switchCameraButton.isEnabled = ((self.goCoder?.cameraPreview?.cameras?.count) ?? 0) > 1
            self.torchButton.isEnabled        = self.goCoder?.cameraPreview?.camera?.hasTorch ?? false
            let isStreaming                 = self.goCoder?.isStreaming ?? false
            self.settingsButton.isEnabled     = !isStreaming
            // The mic icon should only be displayed while streaming and audio streaming has been enabled
            // in the GoCoder SDK configuration setiings
            self.micButton.isEnabled          = isStreaming && self.goCoderConfig.audioEnabled
            self.micButton.isHidden           = !self.micButton.isEnabled
            
            self.bitmapOverlayImgView.isHidden = !self.bitmapOverlayVideoEffect;
            if(bitmapOverlayVideoEffect){
                let panRecognizer = UIPanGestureRecognizer(target: self, action: #selector(handleBitmapDragged));
                bitmapOverlayImgView.addGestureRecognizer(panRecognizer);
                
                let pinchRecognizer = UIPinchGestureRecognizer(target: self, action: #selector(handleBitmapOverlayPinch));
                self.view.addGestureRecognizer(pinchRecognizer);
            }
        }
    }
    
    @objc func handleBitmapOverlayPinch(_ sender:UIPinchGestureRecognizer){
        let recognizer = sender.view;
        let state = sender.state;
        let recognizerView:UIImageView = bitmapOverlayImgView;
        if (state == UIGestureRecognizer.State.began || state == UIGestureRecognizer.State.changed)
        {
            let scale  = sender.scale;
            recognizerView.transform = view.transform.scaledBy(x: scale, y: scale);
            recognizer?.contentScaleFactor = 1.0;
        }
        if(state == UIGestureRecognizer.State.ended){
            bitmapOverlayImgView.frame = CGRect(x: recognizerView.frame.origin.x, y: recognizerView.frame.origin.y, width: recognizerView.frame.size.width, height: recognizerView.frame.size.height);
        }
    }
    
    @objc func handleBitmapDragged(_ sender:UIPanGestureRecognizer){
        let recognizer:UIImageView = bitmapOverlayImgView;
        self.view.bringSubviewToFront(recognizer)
        let translation = sender.translation(in: recognizer)
        recognizer.center = CGPoint(x: recognizer.center.x + translation.x, y: recognizer.center.y + translation.y)
        sender.setTranslation(CGPoint.zero, in: recognizer)
 
        bitmapOverlayImgView.frame = CGRect(x: recognizer.frame.origin.x, y: recognizer.frame.origin.y, width: recognizer.frame.size.width, height: recognizer.frame.size.height);
    }

    //MARK: - WOWZBroadcastStatusCallback Protocol Instance Methods

    func onWOWZStatus(_ status: WOWZBroadcastStatus!) {
        switch (status.state) {
        case .idle:
            DispatchQueue.main.async { () -> Void in
                self.broadcastButton.setImage(UIImage(named: "start_button"), for: UIControl.State())
                self.updateUIControls()
            }

        case .broadcasting:
            DispatchQueue.main.async { () -> Void in
                self.broadcastButton.setImage(UIImage(named: "stop_button"), for: UIControl.State())
                self.updateUIControls()
            }

        default: break
        }
    }

    func onWOWZEvent(_ status: WOWZBroadcastStatus!) {
        // If an event is reported by the GoCoder SDK, display an alert dialog describing the event,
        // but only if we haven't already shown an alert for this event

        DispatchQueue.main.async { () -> Void in
            if !self.receivedGoCoderEventCodes.contains(status.event) {
                self.receivedGoCoderEventCodes.append(status.event)
                self.showAlert("Live Streaming Event", status: status)
            }

            self.updateUIControls()
        }
    }

    func onWOWZError(_ status: WOWZBroadcastStatus!) {
        // If an error is reported by the GoCoder SDK, display an alert dialog containing the error details
        DispatchQueue.main.async { () -> Void in
            self.showAlert("Live Streaming Error", status: status)
            self.updateUIControls()
        }
    }


    //MARK: - WOWZZVideoSink Protocol Methods

    func videoFrameWasCaptured(_ imageBuffer: CVImageBuffer, framePresentationTime: CMTime, frameDuration: CMTime) {
        if goCoder != nil && goCoder!.isStreaming && blackAndWhiteVideoEffect {
            // convert frame to b/w using CoreImage tonal filter
            var frameImage = CIImage(cvImageBuffer: imageBuffer)
            if let grayFilter = CIFilter(name: "CIPhotoEffectTonal") {
                grayFilter.setValue(frameImage, forKeyPath: "inputImage")
                if let outImage = grayFilter.outputImage {
                    frameImage = outImage

                    let context = CIContext(options: nil)
                    context.render(frameImage, to: imageBuffer)
                }
            }
        }
        
        if goCoder != nil && goCoder!.isStreaming && bitmapOverlayVideoEffect {
            let wowzOverlayImg = bitmapOverlayImgView.image?.ciImage;
            CVPixelBufferLockBaseAddress(imageBuffer, []);
            let context = CGContext(data: CVPixelBufferGetBaseAddress(imageBuffer),
                                    width: CVPixelBufferGetWidth(imageBuffer),
                                    height: CVPixelBufferGetHeight(imageBuffer),
                                    bitsPerComponent: 8,
                                    bytesPerRow: CVPixelBufferGetBytesPerRow(imageBuffer),
                                    space: CGColorSpaceCreateDeviceRGB(),
                                    bitmapInfo: CGBitmapInfo.byteOrder32Little.rawValue | CGImageAlphaInfo.premultipliedFirst.rawValue );
            
            let rect:CGRect = bitmapOverlayImgView.frame;
            let height = goCoderConfig.videoHeight+100; /// accommodating for header / footer areas
            let y = CGFloat(height) - rect.origin.y;
            let newFrame:CGRect = CGRect(x: rect.origin.x, y: y, width: bitmapOverlayImgView.frame.size.width, height: bitmapOverlayImgView.frame.size.height);
     
            let cgImage: CGImage? = bitmapOverlayImgView.image?.cgImage;
            context?.draw(cgImage!, in: newFrame);
            CVPixelBufferUnlockBaseAddress(imageBuffer, []);
            
            if wowzOverlayImg != nil
            {
                let contextOverlay = CIContext(options: nil)
                contextOverlay.render(wowzOverlayImg!, to: imageBuffer)
            }
        }
    }
    
    func videoCaptureInterruptionStarted() {
        goCoder?.endStreaming(self)
    }


    //MARK: - WOWZAudioSink Protocol Methods

    func audioLevelDidChange(_ level: Float) {
//        print("Audio level did change: \(level)");
    }


    //MARK: - Alerts

    func showAlert(_ title:String, status:WOWZBroadcastStatus) {
        let alertController = UIAlertController(title: title, message: status.description, preferredStyle: .alert)

        let action = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(action)

        self.present(alertController, animated: true, completion: nil)
    }

    func showAlert(_ title:String, error:NSError) {
        let alertController = UIAlertController(title: title, message: error.localizedDescription, preferredStyle: .alert)

        let action = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(action)

        self.present(alertController, animated: true, completion: nil)
    }



}
