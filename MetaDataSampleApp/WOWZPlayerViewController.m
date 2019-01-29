//
//  WOWZPlayerViewController.m
//  PrivateSDKSampleApp
//
//  Created by Mike Leavy on 9/25/16.
//  © 2016 – 2019 Wowza Media Systems, LLC. All rights reserved.
//

#import "WOWZPlayerViewController.h"

#import <WowzaGoCoderSDK/WowzaGoCoderSDK.h>

#import "SettingsViewModel.h"
#import "SettingsViewController.h"
#import "MetaDataBroadcastViewController.h"


@interface WOWZPlayerViewController () <WOWZStatusCallback, WOWZDataSink>

#pragma mark - UI Elements
@property (nonatomic, weak) IBOutlet UIButton           *playbackButton;
@property (nonatomic, weak) IBOutlet UIButton           *settingsButton;
@property (nonatomic, weak) IBOutlet UIButton           *muteButton;
@property (nonatomic, weak) IBOutlet UISlider           *volumeSlider;
@property (nonatomic, weak) IBOutlet UILabel            *infoLabel;
@property (weak, nonatomic) IBOutlet UIButton           *closeButton;

@property (nonatomic, weak) IBOutlet UILabel						*syncOffsetLabel;

@property IBOutlet UIView *previewView;

#pragma mark - GoCoder SDK Components
@property (nonatomic, strong) WowzaConfig               *goCoderConfig;
@property (nonatomic, strong) WOWZPlayer                  *player;

@end

@implementation WOWZPlayerViewController

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
	
		//default to these on... you can change.
    self.goCoderConfig.audioEnabled = YES;
    self.goCoderConfig.videoEnabled = YES;
	
	//dont let the app sleep from idle timer while watching clips.
	[[UIApplication sharedApplication] setIdleTimerDisabled:YES];
    
    NSLog (@"WowzaGoCoderSDK version =\n major:%lu\n minor:%lu\n revision:%lu\n build:%lu\n short string: %@\n verbose string: %@",
           (unsigned long)[WOWZVersionInfo majorVersion],
           (unsigned long)[WOWZVersionInfo minorVersion],
           (unsigned long)[WOWZVersionInfo revision],
           (unsigned long)[WOWZVersionInfo buildNumber],
           [WOWZVersionInfo string],
           [WOWZVersionInfo verboseString]);
    
    NSLog (@"%@", [WOWZPlatformInfo string]);
    
    // Register the GoCoder SDK license key
    NSError *goCoderLicensingError = [WowzaGoCoder registerLicenseKey:SDKSampleAppLicenseKey];
    if (goCoderLicensingError != nil) {
        // Handle license key registration failure
        [MetaDataBroadcastViewController showAlertWithTitle:@"GoCoder SDK Licensing Error" error:goCoderLicensingError presenter:self];
    }
    else {
        self.player = [WOWZPlayer new];
			
        self.volumeSlider.value = self.player.volume;
				// Set default preroll buffer duration
        self.player.prerollDuration = [[NSUserDefaults standardUserDefaults] floatForKey:PlaybackPrerollKey];
			
				// Optionally set up data sink to handle in stream events
        [self.player registerDataSink:self eventName:@"onFooBar"];
    }
}

- (BOOL)shouldAutorotate {
	return YES;
}

-(UIInterfaceOrientationMask)supportedInterfaceOrientations{
	return UIInterfaceOrientationMaskAll;
}

- (void) viewDidLayoutSubviews {
	[self.player updateViewLayouts];
}

- (void) viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    NSData *savedConfigData = [NSKeyedArchiver archivedDataWithRootObject:self.goCoderConfig];
    [[NSUserDefaults standardUserDefaults] setObject:savedConfigData forKey:SDKSampleSavedConfigKey];
    [[NSUserDefaults standardUserDefaults] synchronize];
	
		//because of the custom SettingsViewModel we constructed we pull the hls value from NSUserDefaults
    self.goCoderConfig.allowHLSPlayback = [[NSUserDefaults standardUserDefaults] boolForKey:AllowHLSKey];
		self.goCoderConfig.hlsURL = [[NSUserDefaults standardUserDefaults] stringForKey:HLSURLKey];
		//setup the player with the preroll duration (seconds)
		self.player.prerollDuration = [[NSUserDefaults standardUserDefaults] floatForKey:PlaybackPrerollKey];
	
	[self.player resetPlaybackErrorCount];
	
	NSError *error;// = nil;
	//[[AVAudioSession sharedInstance] setCategory:AVAudioSessionModeMoviePlayback withOptions:AVAudioSessionCategoryOptionAllowBluetooth error:&error];
	//[[AVAudioSession sharedInstance] overrideOutputAudioPort:AVAudioSessionPortOverrideSpeaker error:&error];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - UI Action Methods

- (IBAction) didTapPlaybackButton:(id)sender {
    
    if ([self.player currentPlayState] == WOWZStateIdle) {
        self.infoLabel.text = @"Connecting...";
        
        self.infoLabel.hidden = NO;
        self.infoLabel.alpha = 1;
        
        self.playbackButton.enabled = NO;
        //self.player.playerView = self.previewView;
        
        [self.player play:self.goCoderConfig callback:self];
   
       
    }
    else {
				[self.player resetPlaybackErrorCount];
        [self.player stop];
    }
}

- (IBAction) didTapSettingsButton:(id)sender {
    UIViewController *settingsNavigationController = [[UIStoryboard storyboardWithName:@"GoCoderSettings" bundle:nil] instantiateViewControllerWithIdentifier:@"settingsNavigationController"];
    
    SettingsViewController *settingsVC = (SettingsViewController *)(((UINavigationController *)settingsNavigationController).topViewController);
    [settingsVC addDisplaySection:SettingsViewSectionPlaybackSettings];
    [settingsVC addDisplaySection:SettingsViewSectionPlayback];
		[settingsVC addDisplaySection:SettingsViewSectionPlaybackHLS];
	//[settingsVC addDisplaySection:SettingsViewSectionConnectionCode];
    
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

- (IBAction) didTapCloseButton:(id)sender {
        if([self.player currentPlayState] == WOWZStateRunning || [self.player currentPlayState] == WOWZStateBuffering){
			[self.player stop];
		}
    [self.player unregisterDataSink:self eventName:@"onTextData"];
    [self dismissViewControllerAnimated:YES completion:nil];
}

-(IBAction)syncSliderChanged:(id)sender {
	UISlider *slider = (UISlider *)sender;
	Float32 value = slider.value;
	self.player.syncOffset = value;
	
}


#pragma mark - WOWZStatusCallback Protocol Instance Methods

- (void) onWOWZStatus:(WOWZStatus *) goCoderStatus {
    // A successful status transition has been reported by the GoCoder SDK
    
    switch (goCoderStatus.state) {
            
        case WOWZStateIdle:
            
            self.settingsButton.hidden = NO;
            self.closeButton.hidden = NO;
            self.playbackButton.enabled = YES;
            [self.playbackButton setImage:[UIImage imageNamed:(@"playback_button")] forState:UIControlStateNormal];
            {
                [UIView animateWithDuration:0.25 animations:^{
                    self.infoLabel.alpha = 0;
                }];
            }
            break;
            
        case WOWZStateStarting:
            // A streaming playback session is starting up
            self.closeButton.hidden = YES;
            self.settingsButton.hidden = YES;
            self.playbackButton.enabled = NO;
            self.infoLabel.text = @"Starting...";
            self.infoLabel.alpha = 1;
						self.player.playerView = self.previewView;

            break;
            
        case WOWZStateRunning:
            [self.playbackButton setImage:[UIImage imageNamed:(@"stop_playback_button")] forState:UIControlStateNormal];
            self.playbackButton.enabled = YES;
            self.infoLabel.text = @"Playing";
            {
                [UIView animateWithDuration:0.25 animations:^{
                    self.infoLabel.alpha = 0;
                }];
            }
            break;
            
        case WOWZStateStopping:
            self.playbackButton.enabled = NO;
            self.infoLabel.alpha = 1;
            self.infoLabel.text = @"Stopping";
            break;
            
        case WOWZStateBuffering:
            self.infoLabel.text = @"Buffering...";
            break;
            
        default:
            break;
    }
}

- (void) onWOWZEvent:(WOWZStatus *) goCoderStatus {
    // nothing to do
}

- (void) onWOWZError:(WOWZStatus *) goCoderStatus {
    // If an error is reported by the GoCoder SDK, display an alert dialog containing the error details
    [WOWZPlayerViewController showAlertWithTitle:@"Playback Error" status:goCoderStatus presenter:self];
}



#pragma mark - WOWZDataSink

- (void) onData:(WOWZDataEvent *)dataEvent {
    NSLog(@"Got data - %@", dataEvent.description);
}

#pragma mark -

+ (void) showAlertWithTitle:(NSString *)title status:(WOWZStatus *)status presenter:(UIViewController *)presenter {
	
	[SettingsViewController presentAlert:title message:status.description presenter:presenter];
}

+ (void) showAlertWithTitle:(NSString *)title error:(NSError *)error presenter:(UIViewController *)presenter {
	
	[SettingsViewController presentAlert:title message:error.localizedDescription presenter:presenter];
}



@end
