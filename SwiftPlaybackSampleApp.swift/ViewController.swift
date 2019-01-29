//
//  ViewController.swift
//  SwiftPlaybackSampleApp
//
//  Created by Benji Brown on 7/2/18.
//  Copyright © 2019 Wowza. All rights reserved.
//

import UIKit
import WowzaGoCoderSDK

class ViewController: UIViewController, WOWZStatusCallback  {
    
    let SDKSampleSavedConfigKey = "SDKSampleSavedConfigKey"
    let SDKSampleAppLicenseKey = "GOSK-3245-010C-F211-6F2F-FC79"
    
    @IBOutlet weak var playButton:UIButton!
    @IBOutlet weak var settingsButton:UIButton!
    @IBOutlet weak var muteButton:UIButton!
    @IBOutlet weak var volumeSlider: UISlider!
    @IBOutlet weak var infoLabel: UILabel!

    var goCoderConfig:WowzaConfig!
    
    lazy var player = WOWZPlayer()
    @IBOutlet weak var previewView:UIView!

    
    var receivedGoCoderEventCodes = Array<WOWZEvent>()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
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

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        let savedConfigData = NSKeyedArchiver.archivedData(withRootObject: goCoderConfig)
        UserDefaults.standard.set(savedConfigData, forKey: SDKSampleSavedConfigKey)
        UserDefaults.standard.synchronize()
   
        /*
        self.goCoderConfig.allowHLSPlayback = UserDefaults.standard.bool(forKey: AllowHLSKey)
        self.goCoderConfig.hlsURL = UserDefaults.standard.string(forKey: HLSURLKey)! as NSString
        self.player.prerollDuration = Float64(UserDefaults.standard.float(forKey: PlaybackPrerollKey))
        */
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func didTapSettingsButton(_ sender:AnyObject?) {
        if let settingsNavigationController = UIStoryboard(name: "AppSettings", bundle: nil).instantiateViewController(withIdentifier: "settingsNavigationController") as? UINavigationController {
            
            if let settingsViewController = settingsNavigationController.topViewController as? SettingsViewController {
                
                settingsViewController.addDisplay(.playbackSettings)
                settingsViewController.addDisplay(.playback)
                settingsViewController.addDisplay(.playbackHLS)
                
               
                let viewModel = SettingsViewModel(sessionConfig: goCoderConfig)
                
                settingsViewController.viewModel = viewModel!
            }
            
            
            self.present(settingsNavigationController, animated: true, completion: nil)
        }
    }
    
    @IBAction func didTapMuteButton(_ sender:AnyObject?) {
        self.player.muted = !self.player.muted
        let muteButtonImage = UIImage.init(named: self.player.muted ? "volume_mute" :"volume_unmute")
        self.muteButton.setImage(muteButtonImage, for: UIControlState.normal)
        self.volumeSlider.isEnabled = !self.player.muted
    }
    
    @IBAction func didTapPlayButton(_ sender:AnyObject?) {
        if(self.player.currentPlayState() == WOWZState.idle){
            self.infoLabel.text = "Connecting..."
            
            self.infoLabel.isHidden = false;
            self.infoLabel.alpha = 1;
            
            self.playButton.isEnabled = false;
            
            self.player.play(self.goCoderConfig, callback: self)
        }else{
            self.player.resetPlaybackErrorCount()
            self.player.stop()
        }
    }
    
    /*
    - (IBAction)didChangeVolume:(id)sender {
    
    UISlider *slider = (UISlider *)sender;
    self.player.volume = slider.value;
    }
*/

    @IBAction func didChangeVolume(_ sender:AnyObject?) {
        let slider:UISlider = sender as! UISlider
        self.player.volume = slider.value
    }

    func onWOWZStatus(_ status: WOWZStatus!) {
        switch (status.state) {
        case .idle:
            
            DispatchQueue.main.async { () -> Void in
                self.settingsButton.isHidden = false;
                self.playButton.isEnabled = true;
                    self.playButton.setImage(UIImage.init(named: "playback_button"), for: UIControlState.normal)
                    UIView.animate(withDuration: 0.25, animations: {
                        self.infoLabel.alpha = 0
                    })
    
            }
            break
        
        case .starting:
            DispatchQueue.main.async { () -> Void in

            // A streaming playback session is starting up
            self.settingsButton.isHidden = true
            self.playButton.isEnabled = false
            self.infoLabel.text = "Starting..."
            self.infoLabel.alpha = 1;
            self.player.playerView = self.previewView;
            }
            break;
        case .running:
            DispatchQueue.main.async { () -> Void in

            self.playButton.setImage(UIImage.init(named: "stop_playback_button"), for: UIControlState.normal)
                self.playButton.isEnabled = true
            self.infoLabel.text = "Playing"
            UIView.animate(withDuration: 0.25, animations: {
                self.infoLabel.alpha = 0;

            })
            }
            break;
        case .stopping:
            DispatchQueue.main.async { () -> Void in

                self.playButton.isEnabled = false
            self.infoLabel.alpha = 1
            self.infoLabel.text = "Stopping"
            }
            break;

        case .buffering:
            DispatchQueue.main.async { () -> Void in

            self.infoLabel.text = "Buffering..."
            }
            break;

        default: break
        }
    }
    
    func onWOWZError(_ status: WOWZStatus!) {
        print(status.error?.localizedDescription ?? "error occured")
    }
    
    func showAlert(_ title:String, error:NSError) {
        let alertController = UIAlertController(title: title, message: error.localizedDescription, preferredStyle: .alert)
        
        let action = UIAlertAction(title: "OK", style: .default, handler: nil)
        alertController.addAction(action)
        
        self.present(alertController, animated: true, completion: nil)
    }

}

