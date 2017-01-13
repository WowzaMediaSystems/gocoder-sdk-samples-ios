//
//  WZPlayerViewController.m
//  PrivateSDKSampleApp
//
//  Created by Mike Leavy on 9/25/16.
//  Copyright © 2016 Wowza, Inc. All rights reserved.
//

#import "WZPlayerViewController.h"

#import <WowzaGoCoderSDK/WowzaGoCoderSDK.h>

#import "SettingsViewModel.h"
#import "SettingsViewController.h"
#import "VideoPlayerViewController.h"


@interface WZPlayerViewController () <WZStatusCallback, WZDataSink>

#pragma mark - UI Elements
@property (nonatomic, weak) IBOutlet UIButton           *playbackButton;
@property (nonatomic, weak) IBOutlet UIButton           *settingsButton;
@property (nonatomic, weak) IBOutlet UIButton           *muteButton;
@property (nonatomic, weak) IBOutlet UISlider           *volumeSlider;
@property (nonatomic, weak) IBOutlet UILabel            *infoLabel;

#pragma mark - GoCoder SDK Components
@property (nonatomic, strong) WowzaConfig               *goCoderConfig;
@property (nonatomic, strong) WZPlayer                  *player;


@end

@implementation WZPlayerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [WowzaGoCoder setLogLevel:WowzaGoCoderLogLevelDefault];
    
    // Load or initialization the streaming configuration settings
    NSData *savedConfig = [[NSUserDefaults standardUserDefaults] objectForKey:SDKSampleSavedConfigKey];
    if (savedConfig) {
        self.goCoderConfig = [NSKeyedUnarchiver unarchiveObjectWithData:savedConfig];
    }
    else {
        self.goCoderConfig = [WowzaConfig new];
    }
    
    self.goCoderConfig.audioEnabled = YES;
    self.goCoderConfig.videoEnabled = YES;
    
    NSLog (@"WowzaGoCoderSDK version =\n major:%lu\n minor:%lu\n revision:%lu\n build:%lu\n short string: %@\n verbose string: %@",
           (unsigned long)[WZVersionInfo majorVersion],
           (unsigned long)[WZVersionInfo minorVersion],
           (unsigned long)[WZVersionInfo revision],
           (unsigned long)[WZVersionInfo buildNumber],
           [WZVersionInfo string],
           [WZVersionInfo verboseString]);
    
    NSLog (@"%@", [WZPlatformInfo string]);
    
    
    // Register the GoCoder SDK license key
    NSError *goCoderLicensingError = [WowzaGoCoder registerLicenseKey:SDKSampleAppLicenseKey];
    if (goCoderLicensingError != nil) {
        // Handle license key registration failure
        [VideoPlayerViewController showAlertWithTitle:@"GoCoder SDK Licensing Error" error:goCoderLicensingError presenter:self];
    }
    else {
        self.player = [WZPlayer new];
        self.player.playerView = self.view;
        self.volumeSlider.value = self.player.volume;
        self.player.prerollDuration = [[NSUserDefaults standardUserDefaults] floatForKey:PlaybackPrerollKey];
        
        [self.player registerDataSink:self eventName:@"onTextData"];
    }
}


- (void) viewDidLayoutSubviews {
    self.player.playerView = self.view;
}

- (void) viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    NSData *savedConfigData = [NSKeyedArchiver archivedDataWithRootObject:self.goCoderConfig];
    [[NSUserDefaults standardUserDefaults] setObject:savedConfigData forKey:SDKSampleSavedConfigKey];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    // Update the configuration settings in the GoCoder SDK
    self.goCoderConfig = self.goCoderConfig;
    
    self.player.prerollDuration = [[NSUserDefaults standardUserDefaults] floatForKey:PlaybackPrerollKey];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - UI Action Methods

- (IBAction) didTapPlaybackButton:(id)sender {
    if (!self.player.playing) {
        [self.player play:self.goCoderConfig callback:self];
    }
    else {
        [self.player stop];
    }
}

- (IBAction) didTapSettingsButton:(id)sender {
    UIViewController *settingsNavigationController = [[UIStoryboard storyboardWithName:@"GoCoderSettings" bundle:nil] instantiateViewControllerWithIdentifier:@"settingsNavigationController"];
    
    SettingsViewController *settingsVC = (SettingsViewController *)(((UINavigationController *)settingsNavigationController).topViewController);
    [settingsVC addDisplaySection:SettingsViewSectionBroadcast];
    [settingsVC addDisplaySection:SettingsViewSectionPlayback];
    
    SettingsViewModel *settingsModel = [[SettingsViewModel alloc] initWithSessionConfig:self.goCoderConfig];
    settingsVC.viewModel = settingsModel;
    
    [self presentViewController:settingsNavigationController animated:YES completion:NULL];
}

- (IBAction)didTapMuteButton:(id)sender {
    self.player.muted = !self.player.muted;
    UIImage *muteButtonImage = [UIImage imageNamed:self.player.muted ? @"volume_mute" : @"volume_unmute"];
    [self.muteButton setImage:muteButtonImage forState:UIControlStateNormal];
    self.volumeSlider.enabled = !self.player.muted;
}

- (IBAction)didChangeVolume:(id)sender {
    
    UISlider *slider = (UISlider *)sender;
    self.player.volume = slider.value;
}

#pragma mark - WZStatusCallback Protocol Instance Methods

- (void) onWZStatus:(WZStatus *) goCoderStatus {
    // A successful status transition has been reported by the GoCoder SDK
    
    switch (goCoderStatus.state) {
            
        case WZStateIdle:
            self.settingsButton.hidden = NO;
            self.playbackButton.enabled = YES;
            [self.playbackButton setImage:[UIImage imageNamed:(@"playback_button")] forState:UIControlStateNormal];
            {
                [UIView animateWithDuration:0.25 animations:^{
                    self.infoLabel.alpha = 0;
                }];
            }
            break;
            
        case WZStateStarting:
            // A streaming broadcast session is starting up
            self.settingsButton.hidden = YES;
            self.playbackButton.enabled = NO;
            self.infoLabel.text = @"Starting";
            self.infoLabel.alpha = 1;
            break;
            
        case WZStateRunning:
            [self.playbackButton setImage:[UIImage imageNamed:(@"stop_playback_button")] forState:UIControlStateNormal];
            self.playbackButton.enabled = YES;
            self.infoLabel.text = @"Playing";
            {
                [UIView animateWithDuration:0.25 animations:^{
                    self.infoLabel.alpha = 0;
                }];
            }
            break;
            
        case WZStateStopping:
            self.playbackButton.enabled = NO;
            self.infoLabel.alpha = 1;
            self.infoLabel.text = @"Stopping";
            break;
            
        case WZStateBuffering:
            self.infoLabel.text = @"Buffering...";
            break;
            
        default:
            break;
    }
}

- (void) onWZEvent:(WZStatus *) goCoderStatus {
    // nothing to do
}

- (void) onWZError:(WZStatus *) goCoderStatus {
    // If an error is reported by the GoCoder SDK, display an alert dialog containing the error details
    [VideoPlayerViewController showAlertWithTitle:@"Playback Error" status:goCoderStatus presenter:self];
}

#pragma mark - WZDataSink

- (void) onData:(WZDataEvent *)dataEvent {
    NSLog(@"Got data - %@", dataEvent.description);
}



@end
