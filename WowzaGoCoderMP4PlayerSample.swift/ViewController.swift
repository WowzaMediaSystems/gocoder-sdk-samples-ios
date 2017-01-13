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
    
    var movieURL:URL? {
        get {
            
            var url:URL?
            if let moviePath = Bundle.main.path(forResource: movieTitle, ofType: movieType) {
                url = URL(fileURLWithPath: moviePath)
            }
            return url
        }
    }
    
    
    //MARK: - AVAsset variables
    var reader_queue:DispatchQueue = DispatchQueue(label: "com.wowza.goCoderReaderQueue", attributes: [])
    var videoAsset:AVAsset?
    var videoTrack:AVAssetTrack?
    var readerOutput:AVAssetReaderTrackOutput!
    
    var assetReader:AVAssetReader?
    
    //MARK: - GoCoder variables
    let SDKSampleSavedConfigKey = "SDKSampleSavedConfigKey"
    let SDKSampleAppLicenseKey = "GSDK-3943-0003-640D-148D-6AF0"
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
        
        goCoderConfig.broadcastVideoOrientation = .alwaysLandscape
        
        if setupAssetReader() {
            goCoderConfig.videoWidth = UInt(videoTrack!.naturalSize.width)
            goCoderConfig.videoHeight = UInt(videoTrack!.naturalSize.height)
            goCoderConfig.videoFrameRate = UInt(videoTrack!.nominalFrameRate > 0 ? videoTrack!.nominalFrameRate : 30)
        }
        
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        let savedConfigData = NSKeyedArchiver.archivedData(withRootObject: goCoderConfig)
        UserDefaults.standard.set(savedConfigData, forKey: SDKSampleSavedConfigKey)
        UserDefaults.standard.synchronize()
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        if !goCoderRegistrationChecked {
            goCoderRegistrationChecked = true
            if let goCoderLicensingError = WowzaGoCoder.registerLicenseKey(SDKSampleAppLicenseKey) {
                self.showAlert("GoCoder SDK Licensing Error", error: goCoderLicensingError as NSError)
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
        
        videoAsset = AVAsset(url: assetURL)
        
        let videoTracks = videoAsset!.tracks(withMediaType: AVMediaTypeVideo)
        
        guard let track = videoTracks.first else {
            return false
        }
        videoTrack = track
        
        guard let reader = try? AVAssetReader(asset: self.videoAsset!) else {
            return false
        }
        
        assetReader = reader
        
        let options:[String : AnyObject] = [kCVPixelBufferPixelFormatTypeKey as String : NSNumber(value: kCVPixelFormatType_32BGRA)]
        
        readerOutput = AVAssetReaderTrackOutput(track: track, outputSettings: options)
        reader.add(readerOutput)
        
        return true
    }
    
    func updateUIControls() {
        if goCoderStatus.state != .idle && goCoderStatus.state != .running {
            // If a streaming broadcast session is in the process of starting up or shutting down,
            // disable the UI controls
            self.broadcastButton.isEnabled    = false
            self.settingsButton.isEnabled     = false
        }
        else {
            // Set the UI control state based on the streaming broadcast status, configuration,
            // and device capability
            self.broadcastButton.isEnabled    = true
            let isStreaming                 = self.broadcast.status.state == .running
            self.settingsButton.isEnabled     = !isStreaming
        }
    }
    
    //MARK: - Broadcasting
    
    func startBroadcast() {
        if broadcast.status.state == .idle {
            if setupAssetReader() {
                broadcast.start(goCoderConfig, statusCallback: self)
            }
        }
    }
    
    func renderLoop() {
        if let reader = assetReader {
            
            reader_queue.async { () -> Void in
                
                reader.startReading()
                
                while reader.status == .reading && self.broadcast.status.state == .running {
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
                    CVPixelBufferLockBaseAddress(imageBuffer, CVPixelBufferLockFlags(rawValue: CVOptionFlags(0)))
                    
                    let rowBytes = CVPixelBufferGetBytesPerRow(imageBuffer)
                    let width = CVPixelBufferGetWidth(imageBuffer)
                    let height = CVPixelBufferGetHeight(imageBuffer)
                    
                    let colorSpace = CGColorSpaceCreateDeviceRGB()
                    let data = CVPixelBufferGetBaseAddress(imageBuffer)
                    
                    let bitmapInfo:CGBitmapInfo = CGBitmapInfo(rawValue: CGImageAlphaInfo.premultipliedFirst.rawValue | CGBitmapInfo.byteOrder32Little.rawValue)
                    
                    let context = CGContext(data: data, width: width, height: height, bitsPerComponent: 8, bytesPerRow: rowBytes, space: colorSpace, bitmapInfo: bitmapInfo.rawValue)
                    
                    guard let imageRef = context?.makeImage() else {
                        continue
                    }
                    
                    DispatchQueue.main.async(execute: { () -> Void in
                        self.imageView.image = UIImage(cgImage: imageRef)
                    })
                    
                    // slow the render loop down to 30 fps
                    Thread.sleep(forTimeInterval: 0.03)
                }
                
                if self.loop {
                    let dispatchTime: DispatchTime = DispatchTime.now() + Double(Int64(0.1 * Double(NSEC_PER_SEC))) / Double(NSEC_PER_SEC)
                    DispatchQueue.main.asyncAfter(deadline: dispatchTime, execute: {
                        if self.setupAssetReader() {
                            self.renderLoop()
                        }
                    })
                }
                else {
                    DispatchQueue.main.async(execute: { () -> Void in
                        self.stopBroadcast()
                    })
                }
                
            }
        }
    }
    
    func stopBroadcast() {
        if broadcast.status.state != .idle {
            broadcast.end(self)
        }
    }
    
    //MARK: - WZStatusCallback Protocol Instance Methods
    
    func onWZStatus(_ status: WZStatus!) {
        switch (status.state) {
        case .idle:
            DispatchQueue.main.async { () -> Void in
                self.broadcastButton.setImage(UIImage(named: "start_button"), for: UIControlState())
                self.updateUIControls()
            }
            
        case .running:
            renderLoop()
            DispatchQueue.main.async { () -> Void in
                self.broadcastButton.setImage(UIImage(named: "stop_button"), for: UIControlState())
                self.updateUIControls()
            }
            
        case .stopping:
            assetReader?.cancelReading()
            DispatchQueue.main.async { () -> Void in
                self.updateUIControls()
            }
            
        case .starting:
            DispatchQueue.main.async { () -> Void in
                self.updateUIControls()
            }
            
        case .buffering:
            break
        }
        
        
    }
    
    func onWZEvent(_ status: WZStatus!) {
        DispatchQueue.main.async { () -> Void in
            self.showAlert("Live Streaming Event", status: status)
            self.updateUIControls()
        }
    }
    
    func onWZError(_ status: WZStatus!) {
        // If an error is reported by the GoCoder SDK, display an alert dialog containing the error details
        DispatchQueue.main.async { () -> Void in
            self.showAlert("Live Streaming Error", status: status)
            self.updateUIControls()
        }
    }

    //MARK: - Actions
    
    @IBAction func didTapSettings(_ sender:AnyObject?) {
        if let settingsNavigationController = UIStoryboard(name: "GoCoderSettings", bundle: nil).instantiateViewController(withIdentifier: "settingsNavigationController") as? UINavigationController {
            
            if let settingsViewController = settingsNavigationController.topViewController as? SettingsViewController {
                settingsViewController.addDisplay(.broadcast)
                settingsViewController.addDisplay(.bandwidthThrottling)
                
                let viewModel = SettingsViewModel(sessionConfig: goCoderConfig)
                settingsViewController.viewModel = viewModel!
            }
            
            self.present(settingsNavigationController, animated: true, completion: nil)
        }
    }
    
    @IBAction func didTapBroadcast(_ sender:AnyObject?) {
        // Ensure the minimum set of configuration settings have been specified necessary to
        // initiate a broadcast streaming session
        if let configError = goCoderConfig.validateForBroadcast() {
            self.showAlert("Incomplete Streaming Settings", error: configError as NSError)
        }
        else {
            // Disable the U/I controls
            broadcastButton.isEnabled    = false
            settingsButton.isEnabled     = false
            
            if broadcast.status.state == .running {
                stopBroadcast()
            }
            else {
                startBroadcast()
            }
            
        }
    }
    
    @IBAction func didTapLoopButton(_ sender:AnyObject?) {
        if let loopButton = sender as? UIButton {
            loopButton.isSelected = !loopButton.isSelected
            loop = loopButton.isSelected
            UIApplication.shared.isIdleTimerDisabled = loop
        }
    }
    
    //MARK: - Alerts
    
    func showAlert(_ title:String, status:WZStatus) {
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

