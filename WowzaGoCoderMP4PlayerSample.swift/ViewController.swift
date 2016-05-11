//
//  ViewController.swift
//  WowzaGoCoderMP4PlayerSample.swift
//
//  This code and all components (c) Copyright 2015-2016, Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//

import UIKit
import AVFoundation
import WowzaGoCoderSDK

class ViewController: UIViewController, WZStatusCallback {
    
    @IBOutlet var imageView:UIImageView!
    @IBOutlet var settingsButton:UIButton!
    @IBOutlet var broadcastButton:UIButton!
    
    var movieTitle = "Movie"
    var movieType = "m4v"
    
    var loop = false
    
    var movieURL:NSURL? {
        get {
            
            var url:NSURL?
            if let moviePath = NSBundle.mainBundle().pathForResource(movieTitle, ofType: movieType) {
                url = NSURL(fileURLWithPath: moviePath)
            }
            return url
        }
    }
    
    
    //MARK: - AVAsset variables
    var reader_queue:dispatch_queue_t = dispatch_queue_create("com.wowza.goCoderReaderQueue", DISPATCH_QUEUE_SERIAL)
    var videoAsset:AVAsset?
    var videoTrack:AVAssetTrack?
    var readerOutput:AVAssetReaderTrackOutput!
    
    var assetReader:AVAssetReader?
    
    //MARK: - GoCoder variables
    let SDKSampleSavedConfigKey = "SDKSampleSavedConfigKey"
    let SDKSampleAppLicenseKey = "GSDK-4842-0003-C385-E5FA-F1F1"
    var goCoderConfig:WowzaConfig!
    var goCoderStatus = WZStatus()
    var goCoderRegistrationChecked = false
    
    lazy var broadcast:WZBroadcast = {
        let broadcaster = WZBroadcast()
        broadcaster.videoEncoder = self.encoder
        return broadcaster
    }()
    
    lazy var encoder:WZH264Encoder = {
        let encoder = WZH264Encoder()
        return encoder
    }()
    
    

    override func viewDidLoad() {
        super.viewDidLoad()
        
        // load/create the Config settings
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
        
        goCoderConfig.broadcastVideoOrientation = .AlwaysLandscape
        
        if setupAssetReader() {
            goCoderConfig.videoWidth = UInt(videoTrack!.naturalSize.width)
            goCoderConfig.videoHeight = UInt(videoTrack!.naturalSize.height)
            goCoderConfig.videoFrameRate = UInt(videoTrack!.nominalFrameRate > 0 ? videoTrack!.nominalFrameRate : 30)
        }
        
    }
    
    override func viewWillAppear(animated: Bool) {
        super.viewWillAppear(animated)
        
        let savedConfigData = NSKeyedArchiver.archivedDataWithRootObject(goCoderConfig)
        NSUserDefaults.standardUserDefaults().setObject(savedConfigData, forKey: SDKSampleSavedConfigKey)
        NSUserDefaults.standardUserDefaults().synchronize()
    }
    
    override func viewDidAppear(animated: Bool) {
        super.viewDidAppear(animated)
        
        if !goCoderRegistrationChecked {
            goCoderRegistrationChecked = true
            if let goCoderLicensingError = WowzaGoCoder.registerLicenseKey(SDKSampleAppLicenseKey) {
                self.showAlert("GoCoder SDK Licensing Error", error: goCoderLicensingError)
            }
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func setupAssetReader() -> Bool {
        
        // create an AVAsset for reading
        guard let assetURL = self.movieURL else {
            return false
        }
        
        videoAsset = AVAsset(URL: assetURL)
        
        let videoTracks = videoAsset!.tracksWithMediaType(AVMediaTypeVideo)
        
        guard let track = videoTracks.first else {
            return false
        }
        videoTrack = track
        
        guard let reader = try? AVAssetReader(asset: self.videoAsset!) else {
            return false
        }
        
        assetReader = reader
        
        let options:[String : AnyObject] = [kCVPixelBufferPixelFormatTypeKey as String : NSNumber(unsignedInt: kCVPixelFormatType_32BGRA)]
        
        readerOutput = AVAssetReaderTrackOutput(track: track, outputSettings: options)
        reader.addOutput(readerOutput)
        
        return true
    }
    
    func updateUIControls() {
        if goCoderStatus.state != .Idle && goCoderStatus.state != .Running {
            // If a streaming broadcast session is in the process of starting up or shutting down,
            // disable the UI controls
            self.broadcastButton.enabled    = false
            self.settingsButton.enabled     = false
        }
        else {
            // Set the UI control state based on the streaming broadcast status, configuration,
            // and device capability
            self.broadcastButton.enabled    = true
            let isStreaming                 = self.broadcast.status.state == .Running
            self.settingsButton.enabled     = !isStreaming
        }
    }
    
    //MARK: - Broadcasting
    
    func startBroadcast() {
        if broadcast.status.state == .Idle {
            if setupAssetReader() {
                broadcast.startBroadcast(goCoderConfig, statusCallback: self)
            }
        }
    }
    
    func renderLoop() {
        if let reader = assetReader {
            
            dispatch_async(reader_queue) { () -> Void in
                
                reader.startReading()
                
                while reader.status == .Reading && self.broadcast.status.state == .Running {
                    guard let sampleBuffer = self.readerOutput.copyNextSampleBuffer() else {
                        continue
                    }
                    
                    guard let imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer) else {
                        continue
                    }
                    
                    // send the image buffer to the Wowza encoder
                    self.encoder.videoFrameWasCaptured(imageBuffer, framePresentationTime: kCMTimeInvalid, frameDuration: kCMTimeInvalid)
                    
                    // the below is simply here to show the video frame in the iOS UI; it has nothing
                    // to do with broadcasting to Wowza
                    CVPixelBufferLockBaseAddress(imageBuffer, 0)
                    
                    let rowBytes = CVPixelBufferGetBytesPerRow(imageBuffer)
                    let width = CVPixelBufferGetWidth(imageBuffer)
                    let height = CVPixelBufferGetHeight(imageBuffer)
                    
                    let colorSpace = CGColorSpaceCreateDeviceRGB()
                    let data = CVPixelBufferGetBaseAddress(imageBuffer)
                    
                    let bitmapInfo:CGBitmapInfo = CGBitmapInfo(rawValue: CGImageAlphaInfo.PremultipliedFirst.rawValue | CGBitmapInfo.ByteOrder32Little.rawValue)
                    
                    let context = CGBitmapContextCreate(data, width, height, 8, rowBytes, colorSpace, bitmapInfo.rawValue)
                    
                    guard let imageRef = CGBitmapContextCreateImage(context) else {
                        continue
                    }
                    
                    dispatch_async(dispatch_get_main_queue(), { () -> Void in
                        self.imageView.image = UIImage(CGImage: imageRef)
                    })
                    
                    // slow the render loop down to 30 fps
                    NSThread.sleepForTimeInterval(0.03)
                }
                
                if self.loop {
                    let dispatchTime: dispatch_time_t = dispatch_time(DISPATCH_TIME_NOW, Int64(0.1 * Double(NSEC_PER_SEC)))
                    dispatch_after(dispatchTime, dispatch_get_main_queue(), {
                        if self.setupAssetReader() {
                            self.renderLoop()
                        }
                    })
                }
                else {
                    dispatch_async(dispatch_get_main_queue(), { () -> Void in
                        self.stopBroadcast()
                    })
                }
                
            }
        }
    }
    
    func stopBroadcast() {
        if broadcast.status.state != .Idle {
            broadcast.endBroadcast(self)
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
            renderLoop()
            dispatch_async(dispatch_get_main_queue()) { () -> Void in
                self.broadcastButton.setImage(UIImage(named: "stop_button"), forState: .Normal)
                self.updateUIControls()
            }
            
        case .Stopping:
            assetReader?.cancelReading()
            dispatch_async(dispatch_get_main_queue()) { () -> Void in
                self.updateUIControls()
            }
            
        case .Starting:
            dispatch_async(dispatch_get_main_queue()) { () -> Void in
                self.updateUIControls()
            }
        }
        
    }
    
    func onWZEvent(status: WZStatus!) {
        dispatch_async(dispatch_get_main_queue()) { () -> Void in
            self.showAlert("Live Streaming Event", status: status)
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

    //MARK: - Actions
    
    @IBAction func didTapSettings(sender:AnyObject?) {
        if let settingsNavigationController = UIStoryboard(name: "GoCoderSettings", bundle: nil).instantiateViewControllerWithIdentifier("settingsNavigationController") as? UINavigationController {
            
            if let settingsViewController = settingsNavigationController.topViewController as? SettingsViewController {
                settingsViewController.addDisplaySection(.Broadcast)
                settingsViewController.addDisplaySection(.BandwidthThrottling)
                
                let viewModel = SettingsViewModel(sessionConfig: goCoderConfig)
                settingsViewController.viewModel = viewModel
            }
            
            self.presentViewController(settingsNavigationController, animated: true, completion: nil)
        }
    }
    
    @IBAction func didTapBroadcast(sender:AnyObject?) {
        // Ensure the minimum set of configuration settings have been specified necessary to
        // initiate a broadcast streaming session
        if let configError = goCoderConfig.validateForBroadcast() {
            self.showAlert("Incomplete Streaming Settings", error: configError)
        }
        else {
            // Disable the U/I controls
            broadcastButton.enabled    = false
            settingsButton.enabled     = false
            
            if broadcast.status.state == .Running {
                stopBroadcast()
            }
            else {
                startBroadcast()
            }
            
        }
    }
    
    @IBAction func didTapLoopButton(sender:AnyObject?) {
        if let loopButton = sender as? UIButton {
            loopButton.selected = !loopButton.selected
            loop = loopButton.selected
            UIApplication.sharedApplication().idleTimerDisabled = loop
        }
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

