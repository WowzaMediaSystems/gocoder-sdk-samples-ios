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
#import "BroadcastViewController.h"


@interface WOWZPlayerViewController () <WOWZStatusCallback, WOWZDataSink, UICollectionViewDelegate, UICollectionViewDataSource>

#pragma mark - UI Elements
@property (nonatomic, weak) IBOutlet UIButton           *playbackButton;
@property (nonatomic, weak) IBOutlet UIButton           *settingsButton;
@property (nonatomic, weak) IBOutlet UIButton           *muteButton;
@property (nonatomic, weak) IBOutlet UISlider           *volumeSlider;
@property (nonatomic, weak) IBOutlet UILabel            *infoLabel;
@property (weak, nonatomic) IBOutlet UIButton           *closeButton;
@property (weak, nonatomic) IBOutlet UIButton           *aspectButton;

@property IBOutlet UILabel *bitrateLabel;

@property (nonatomic, weak) IBOutlet UILabel						*syncOffsetLabel;

@property IBOutlet UIView *previewView;

@property IBOutlet UICollectionView *collectionView;

#pragma mark - GoCoder SDK Components
@property (nonatomic, strong) WowzaConfig               *goCoderConfig;
@property (nonatomic, strong) WOWZPlayer                  *player;

@end

@implementation WOWZPlayerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [WowzaGoCoder setLogLevel:WowzaGoCoderLogLevelVerbose];
    
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
        dispatch_async(dispatch_get_main_queue(), ^{

        [BroadcastViewController showAlertWithTitle:@"GoCoder SDK Licensing Error" error:goCoderLicensingError presenter:self];
        
        [self.playbackButton setEnabled:NO];
        });
    }
    else {
        self.player = [WOWZPlayer new];
			
        //self.player.shouldAutoStopPlayerOnAppBackground = NO;
        
        self.volumeSlider.value = self.player.volume;
				// Set default preroll buffer duration
        self.player.prerollDuration = [[NSUserDefaults standardUserDefaults] floatForKey:PlaybackPrerollKey];
			
				// Optionally set up data sink to handle in stream events
        [self.player registerDataSink:self eventName:@"onTextData"];
    }
    
    //register for bitrate
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateBitrateLabel) name:@"WOWZBitrateUpdate" object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(hlsPlaybackStarted) name:@"HLSPlaybackStarted" object:nil];
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
    //self.goCoderConfig.allowHLSPlayback = YES;
	[self.player resetPlaybackErrorCount];
	
	NSError *error;// = nil;
	//[[AVAudioSession sharedInstance] setCategory:AVAudioSessionModeMoviePlayback withOptions:AVAudioSessionCategoryOptionAllowBluetooth error:&error];
	//[[AVAudioSession sharedInstance] overrideOutputAudioPort:AVAudioSessionPortOverrideSpeaker error:&error];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)updateBitrateLabel{
    dispatch_async(dispatch_get_main_queue(), ^{
        self.bitrateLabel.text = [NSString stringWithFormat:@"%.02f kbps", self.player.currentInjestBitrate];
    });
}

-(void)hlsPlaybackStarted{
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.playbackButton setImage:[UIImage imageNamed:(@"stop_playback_button")] forState:UIControlStateNormal];
        self.playbackButton.enabled = YES;
        self.infoLabel.text = @"Playing";
        {
            [UIView animateWithDuration:0.25 animations:^{
                self.infoLabel.alpha = 0;
            }];
        }
    });
}


#pragma mark - UI Action Methods
-(IBAction) didTapStopPlayButton:(id)sender{
    [self.player resetPlaybackErrorCount];
    [self.player stop];
    
    
    self.infoLabel.text = @"Connecting...";
    
    self.infoLabel.hidden = NO;
    self.infoLabel.alpha = 1;
    
    self.playbackButton.enabled = NO;
    
    [self.player play:self.goCoderConfig callback:self];
}

- (IBAction) didTapPlaybackButton:(id)sender {
    
    if ([self.player currentPlayState] == WOWZStateIdle && self.player.hlsPlayer.timeControlStatus != AVPlayerTimeControlStatusPlaying) {
        if([self.player currentPlaybackErrorCount] > 2){
            self.infoLabel.text = @"Connecting to HLS fallback...";
        }else{
            self.infoLabel.text = @"Connecting...";
        }
        
        
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

-(IBAction)didTapAspectButton:(id)sender{
    if(self.player.playerViewGravity == WOWZPlayerViewGravityResizeAspectFill){
        self.player.playerViewGravity = WOWZPlayerViewGravityResizeAspect;
    }else{
        self.player.playerViewGravity = WOWZPlayerViewGravityResizeAspectFill;
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
        }else{
            
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
            self.player.playerViewGravity = WOWZPlayerViewGravityResizeAspect;
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
    self.infoLabel.text = @"";
    self.playbackButton.enabled = YES;
    
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


#pragma mark - UICOLLECITONVIEW DATASOURCE
- (nonnull __kindof UICollectionViewCell *)collectionView:(nonnull UICollectionView *)collectionView cellForItemAtIndexPath:(nonnull NSIndexPath *)indexPath {
    UICollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"MyCell" forIndexPath:indexPath];
    // cell customization
    return cell;
}

- (NSInteger)collectionView:(nonnull UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return 15;
}

//- (void)encodeWithCoder:(nonnull NSCoder *)aCoder {
//    <#code#>
//}
//
//- (void)traitCollectionDidChange:(nullable UITraitCollection *)previousTraitCollection {
//    <#code#>
//}
//
//- (void)preferredContentSizeDidChangeForChildContentContainer:(nonnull id<UIContentContainer>)container {
//    <#code#>
//}
//
//- (CGSize)sizeForChildContentContainer:(nonnull id<UIContentContainer>)container withParentContainerSize:(CGSize)parentSize {
//    <#code#>
//}
//
//- (void)systemLayoutFittingSizeDidChangeForChildContentContainer:(nonnull id<UIContentContainer>)container {
//    <#code#>
//}
//
//- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(nonnull id<UIViewControllerTransitionCoordinator>)coordinator {
//    <#code#>
//}
//
//- (void)willTransitionToTraitCollection:(nonnull UITraitCollection *)newCollection withTransitionCoordinator:(nonnull id<UIViewControllerTransitionCoordinator>)coordinator {
//    <#code#>
//}
//
//- (void)didUpdateFocusInContext:(nonnull UIFocusUpdateContext *)context withAnimationCoordinator:(nonnull UIFocusAnimationCoordinator *)coordinator {
//    <#code#>
//}
//
//- (void)setNeedsFocusUpdate {
//    <#code#>
//}
//
//- (BOOL)shouldUpdateFocusInContext:(nonnull UIFocusUpdateContext *)context {
//    <#code#>
//}
//
//- (void)updateFocusIfNeeded {
//    <#code#>
//}

@end
