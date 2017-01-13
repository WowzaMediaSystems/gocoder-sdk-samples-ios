//
//  VideoPlayerViewController.m
//  SDKSampleApp
//
//  This code and all components (c) Copyright 2015-2016, Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//


#import <WowzaGoCoderSDK/WowzaGoCoderSDK.h>

#import "VideoPlayerViewController.h"
#import "SettingsViewModel.h"
#import "SettingsViewController.h"
#import "MP4Writer.h"


#pragma mark VideoPlayerViewController (GoCoder SDK Sample App) -

NSString *const SDKSampleSavedConfigKey = @"SDKSampleSavedConfigKey";
NSString *const SDKSampleAppLicenseKey = @"GSDK-3943-0003-F27C-B102-D16D";

@interface VideoPlayerViewController () <WZStatusCallback, WZVideoSink, WZAudioSink, WZVideoEncoderSink, WZAudioEncoderSink, WZDataSink>

#pragma mark - UI Elements
@property (nonatomic, weak) IBOutlet UIButton           *broadcastButton;
@property (nonatomic, weak) IBOutlet UIButton           *settingsButton;
@property (nonatomic, weak) IBOutlet UIButton           *switchCameraButton;
@property (nonatomic, weak) IBOutlet UIButton           *torchButton;
@property (nonatomic, weak) IBOutlet UIButton           *micButton;
@property (nonatomic, weak) IBOutlet UIButton           *closeButton;
@property (weak, nonatomic) IBOutlet UILabel            *timeLabel;
@property (weak, nonatomic) IBOutlet UIButton           *pingButton;

#pragma mark - GoCoder SDK Components
@property (nonatomic, strong) WowzaGoCoder      *goCoder;
@property (nonatomic, strong) WowzaConfig       *goCoderConfig;
@property (nonatomic, strong) WZCameraPreview   *goCoderCameraPreview;

#pragma mark - Data
@property (nonatomic, strong) NSMutableArray    *receivedGoCoderEventCodes;
@property (nonatomic, assign) BOOL              blackAndWhiteVideoEffect;
@property (nonatomic, assign) BOOL              recordVideoLocally;
@property (nonatomic, assign) CMTime            broadcastStartTime;

#pragma mark - MP4Writing
@property (nonatomic, strong) MP4Writer         *mp4Writer;
@property (nonatomic, assign) BOOL              writeMP4;
@property (nonatomic, strong) dispatch_queue_t  video_capture_queue;

#pragma mark - WZData injection
@property (nonatomic, assign) long long         broadcastFrameCount;

@end

#pragma mark -
@implementation VideoPlayerViewController

#pragma mark - UIViewController Protocol Instance Methods

- (void) dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    NSLog(@"VideoPlayerViewController - goodbye");
}

- (void) viewDidLoad {
    [super viewDidLoad];
    
    
    self.blackAndWhiteVideoEffect = [[NSUserDefaults standardUserDefaults] boolForKey:BlackAndWhiteKey];
    self.recordVideoLocally = [[NSUserDefaults standardUserDefaults] boolForKey:RecordVideoLocallyKey];
    self.broadcastStartTime = kCMTimeInvalid;
    self.timeLabel.hidden = YES;
    
    
    self.receivedGoCoderEventCodes = [NSMutableArray new];
    
    [WowzaGoCoder setLogLevel:WowzaGoCoderLogLevelDefault];
    
    // Load or initialization the streaming configuration settings
    NSData *savedConfig = [[NSUserDefaults standardUserDefaults] objectForKey:SDKSampleSavedConfigKey];
    if (savedConfig) {
        self.goCoderConfig = [NSKeyedUnarchiver unarchiveObjectWithData:savedConfig];
    }
    else {
        self.goCoderConfig = [WowzaConfig new];
    }
            
    
    NSLog (@"WowzaGoCoderSDK version =\n major:%lu\n minor:%lu\n revision:%lu\n build:%lu\n short string: %@\n verbose string: %@",
           (unsigned long)[WZVersionInfo majorVersion],
           (unsigned long)[WZVersionInfo minorVersion],
           (unsigned long)[WZVersionInfo revision],
           (unsigned long)[WZVersionInfo buildNumber],
           [WZVersionInfo string],
           [WZVersionInfo verboseString]);
    
    NSLog (@"%@", [WZPlatformInfo string]);
    
    self.goCoder = nil;
    
    // Register the GoCoder SDK license key
    NSError *goCoderLicensingError = [WowzaGoCoder registerLicenseKey:SDKSampleAppLicenseKey];
    if (goCoderLicensingError != nil) {
        // Handle license key registration failure
        [VideoPlayerViewController showAlertWithTitle:@"GoCoder SDK Licensing Error" error:goCoderLicensingError presenter:self];
    }
    else {
        // Initialize the GoCoder SDK
        self.goCoder = [WowzaGoCoder sharedInstance];

        // Specify the view in which to display the camera preview
        if (self.goCoder != nil) {
            
            // Request camera and microphone permissions
            [WowzaGoCoder requestPermissionForType:WowzaGoCoderPermissionTypeCamera response:^(WowzaGoCoderCapturePermission permission) {
                NSLog(@"Camera permission is: %@", permission == WowzaGoCoderCapturePermissionAuthorized ? @"authorized" : @"denied");
            }];
            
            [WowzaGoCoder requestPermissionForType:WowzaGoCoderPermissionTypeMicrophone response:^(WowzaGoCoderCapturePermission permission) {
                NSLog(@"Microphone permission is: %@", permission == WowzaGoCoderCapturePermissionAuthorized ? @"authorized" : @"denied");
            }];
            
            [self.goCoder registerVideoSink:self];
            [self.goCoder registerAudioSink:self];
            [self.goCoder registerVideoEncoderSink:self];
            [self.goCoder registerAudioEncoderSink:self];
            
            [self.goCoder registerDataSink:self eventName:@"onTextData"];
            
            self.goCoder.config = self.goCoderConfig;
            self.goCoder.cameraView = self.view;
            
            // Start the camera preview
            self.goCoderCameraPreview = self.goCoder.cameraPreview;
            [self.goCoderCameraPreview startPreview];
        }

        // Update the UI controls
        [self updateUIControls];
    }
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(orientationChanged:) name:UIDeviceOrientationDidChangeNotification object:[UIDevice currentDevice]];

}

- (void) viewDidLayoutSubviews {
    [super viewDidLayoutSubviews];
    
    self.goCoder.cameraPreview.previewLayer.frame = self.view.bounds;
}

- (void) viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];

    NSData *savedConfigData = [NSKeyedArchiver archivedDataWithRootObject:self.goCoderConfig];
    [[NSUserDefaults standardUserDefaults] setObject:savedConfigData forKey:SDKSampleSavedConfigKey];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    // Update the configuration settings in the GoCoder SDK
    if (self.goCoder != nil)
        self.goCoder.config = self.goCoderConfig;
    
    self.blackAndWhiteVideoEffect = [[NSUserDefaults standardUserDefaults] boolForKey:BlackAndWhiteKey];
    self.recordVideoLocally = [[NSUserDefaults standardUserDefaults] boolForKey:RecordVideoLocallyKey];

}

- (void) didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (BOOL) prefersStatusBarHidden {
    return YES;
}

#pragma mark - UI Action Methods

- (IBAction) didTapBroadcastButton:(id)sender {

    // Ensure the minimum set of configuration settings have been specified necessary to
    // initiate a broadcast streaming session
    NSError *configError = [self.goCoder.config validateForBroadcast];
    if (configError != nil) {
        [VideoPlayerViewController showAlertWithTitle:@"Incomplete Streaming Settings" error:configError presenter:self];
        return;
    }
    
    // Disable the U/I controls
    dispatch_async(dispatch_get_main_queue(), ^{
        self.broadcastButton.enabled    = NO;
        self.torchButton.enabled        = NO;
        self.switchCameraButton.enabled = NO;
        self.settingsButton.enabled     = NO;
        self.closeButton.enabled        = NO;
    });
    
    if (self.goCoder.status.state == WZStateRunning) {
        [self.goCoder endStreaming:self];
        [UIApplication sharedApplication].idleTimerDisabled = NO;
    }
    else {
        [self.receivedGoCoderEventCodes removeAllObjects];
        [self.goCoder startStreaming:self];

        dispatch_async(dispatch_get_main_queue(), ^{
            [self.micButton setImage:[UIImage imageNamed:(self.goCoder.isAudioMuted ? @"mic_off_button" : @"mic_on_button")] forState:UIControlStateNormal];
            [UIApplication sharedApplication].idleTimerDisabled = YES;
        });
    }
}

- (IBAction) didTapSwitchCameraButton:(id)sender {
    WZCamera *otherCamera = [self.goCoderCameraPreview otherCamera];
    if (![otherCamera supportsWidth:self.goCoderConfig.videoWidth]) {
        [self.goCoderConfig loadPreset:otherCamera.supportedPresetConfigs.lastObject.toPreset];
        self.goCoder.config = self.goCoderConfig;
    }
    [self.goCoderCameraPreview switchCamera];
    [self.torchButton  setImage:[UIImage imageNamed:@"torch_on_button"] forState:UIControlStateNormal];
    [self updateUIControls];
}

- (IBAction) didTapTorchButton:(id)sender {
    BOOL newTorchOnState = !self.goCoderCameraPreview.camera.torchOn;
    
    self.goCoderCameraPreview.camera.torchOn = newTorchOnState;
    [self.torchButton setImage:[UIImage imageNamed:(newTorchOnState ? @"torch_off_button" : @"torch_on_button")] forState:UIControlStateNormal];
}

- (IBAction) didTapMicButton:(id)sender {
    BOOL newMutedState = !self.goCoder.isAudioMuted;
    
    self.goCoder.audioMuted = newMutedState;
    [self.micButton setImage:[UIImage imageNamed:(newMutedState ? @"mic_off_button" : @"mic_on_button")] forState:UIControlStateNormal];
}

- (IBAction) didTapSettingsButton:(id)sender {
    
    UIViewController *settingsNavigationController = [[UIStoryboard storyboardWithName:@"GoCoderSettings" bundle:nil] instantiateViewControllerWithIdentifier:@"settingsNavigationController"];
    
    SettingsViewController *settingsVC = (SettingsViewController *)(((UINavigationController *)settingsNavigationController).topViewController);
    [settingsVC addAllSections];
    
    SettingsViewModel *settingsModel = [[SettingsViewModel alloc] initWithSessionConfig:self.goCoderConfig];
    settingsModel.supportedPresetConfigs = self.goCoder.cameraPreview.camera.supportedPresetConfigs;
    settingsVC.viewModel = settingsModel;
    
    [self presentViewController:settingsNavigationController animated:YES completion:NULL];
}

- (IBAction) didTapCloseButton:(id)sender {
    [self.goCoderCameraPreview stopPreview];
    self.goCoder.cameraView = nil;
    [self.goCoder unregisterVideoSink:self];
    [self.goCoder unregisterAudioSink:self];
    [self.goCoder unregisterVideoEncoderSink:self];
    [self.goCoder unregisterAudioEncoderSink:self];
    [self.goCoder unregisterDataSink:self eventName:@"onTextData"];
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction) didTapPingButton:(id)sender {
    /*
     The "Ping" button exists in order to demonstrate making a server function call; in this case, the call
     is "onGetPingTime". The server module that implements "onGetPingTime" must exist in order to receive
     a callback.
    */
    if (self.goCoder.status.state == WZStateRunning) {
        WZDataMap *params = [WZDataMap new];
        [self.goCoder sendDataEvent:WZDataScopeModule eventName:@"onGetPingTime" params:params callback:^(WZDataMap * _Nullable result, BOOL isError) {
            if (!isError && result) {
                WZDataItem *item = [result.data valueForKey:@"pingTime"];
                if (item) {
                    NSLog(@"onGetPingTime result - ping time = %0.2f", item.doubleValue);
                }
            }
        }];
    }
}

#pragma mark - Notifications

- (void) orientationChanged:(NSNotification *)notification {
    
    /*
     We are looking at orientation changed events in order to demonstrate sending stream data to the server.
    */
    
    WZDataMap *params = [WZDataMap new];
    UIDevice * device = notification.object;
    switch(device.orientation) {
        case UIDeviceOrientationPortrait:
            [params setString:@"portrait" forKey:@"deviceOrientation"];
            [params setInteger:0 forKey:@"deviceRotation"];
            break;
            
        case UIDeviceOrientationPortraitUpsideDown:
            [params setString:@"portrait" forKey:@"deviceOrientation"];
            [params setInteger:180 forKey:@"deviceRotation"];
            break;
            
        case UIDeviceOrientationLandscapeLeft:
            [params setString:@"landscape" forKey:@"deviceOrientation"];
            [params setInteger:90 forKey:@"deviceRotation"];
            break;
            
        case UIDeviceOrientationLandscapeRight:
            [params setString:@"landscape" forKey:@"deviceOrientation"];
            [params setInteger:270 forKey:@"deviceRotation"];
            break;
            
        default:
            break;
    };
    
    if (params.data.count > 0) {
        [self.goCoder sendDataEvent:WZDataScopeStream eventName:@"onDeviceOrientation" params:params callback:nil];
    }
}


#pragma mark - Instance Methods

// Update the state of the UI controls
- (void) updateUIControls {
    if (self.goCoder.status.state != WZStateIdle && self.goCoder.status.state != WZStateRunning) {
        // If a streaming broadcast session is in the process of starting up or shutting down,
        // disable the UI controls
        self.broadcastButton.enabled    = NO;
        self.torchButton.enabled        = NO;
        self.switchCameraButton.enabled = NO;
        self.settingsButton.enabled     = NO;
        self.closeButton.enabled        = NO;
        self.micButton.hidden           = YES;
        self.micButton.enabled          = NO;
        self.pingButton.hidden          = YES;
    } else {
        // Set the UI control state based on the streaming broadcast status, configuration,
        // and device capability
        self.broadcastButton.enabled    = YES;
        self.switchCameraButton.enabled = self.goCoderCameraPreview.cameras.count > 1;
        self.torchButton.enabled        = [self.goCoderCameraPreview.camera hasTorch];
        self.settingsButton.enabled     = !self.goCoder.isStreaming;
        self.closeButton.enabled        = !self.goCoder.isStreaming;
        // The mic icon should only be displayed while streaming and audio streaming has been enabled
        // in the GoCoder SDK configuration setiings
        self.micButton.enabled          = self.goCoder.isStreaming && self.goCoderConfig.audioEnabled;
        self.micButton.hidden           = !self.micButton.enabled;
        self.pingButton.hidden          = !self.goCoder.isStreaming;
    }
}

#pragma mark - WZStatusCallback Protocol Instance Methods

- (void) onWZStatus:(WZStatus *) goCoderStatus {
    // A successful status transition has been reported by the GoCoder SDK
    
    switch (goCoderStatus.state) {

        case WZStateIdle:
            self.timeLabel.hidden = YES;
            if (self.writeMP4 && self.mp4Writer.writing) {
                if (self.video_capture_queue) {
                    dispatch_async(self.video_capture_queue, ^{
                        [self.mp4Writer stopWriting];
                    });
                }
                else {
                    [self.mp4Writer stopWriting];
                }
            }
            self.writeMP4 = NO;
            break;
            
        case WZStateStarting:
            // A streaming broadcast session is starting up
            self.broadcastStartTime = kCMTimeInvalid;
            self.timeLabel.text = @"00:00";
            self.broadcastFrameCount = 0;
            break;
            
        case WZStateRunning:
            // A streaming broadcast session is running
            self.timeLabel.hidden = NO;
            self.writeMP4 = NO;
            if (self.recordVideoLocally) {
                self.mp4Writer = [MP4Writer new];
                self.writeMP4 = [self.mp4Writer prepareWithConfig:self.goCoderConfig];
                if (self.writeMP4) {
                    [self.mp4Writer startWriting];
                }
            }
            break;

        case WZStateStopping:
            // A streaming broadcast session is shutting down
            break;
            
        default:
            break;
    }
    
    dispatch_async(dispatch_get_main_queue(), ^{
        if (self.goCoder.status.state == WZStateIdle || self.goCoder.status.state == WZStateRunning) {
            [self.broadcastButton setImage:[UIImage imageNamed:(_goCoder.status.state == WZStateIdle) ? @"start_button" : @"stop_button"] forState:UIControlStateNormal];
        }
        
        [self updateUIControls];
    });
}

- (void) onWZEvent:(WZStatus *) goCoderStatus {
    // If an event is reported by the GoCoder SDK, display an alert dialog describing the event,
    // but only if we haven't already shown an alert for this event
    
    dispatch_async(dispatch_get_main_queue(), ^{
        __block BOOL haveSeenAlertForEvent = NO;
        [self.receivedGoCoderEventCodes enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            if ([((NSNumber *)obj) isEqualToNumber:[NSNumber numberWithInteger:goCoderStatus.error.code]]) {
                haveSeenAlertForEvent = YES;
                *stop = YES;
            }
        }];
                
        if (!haveSeenAlertForEvent) {
            [VideoPlayerViewController showAlertWithTitle:@"Live Streaming Event" status:goCoderStatus presenter:self];
            [self.receivedGoCoderEventCodes addObject:[NSNumber numberWithInteger:goCoderStatus.error.code]];
        }
        
        [self updateUIControls];
    });
}

- (void) onWZError:(WZStatus *) goCoderStatus {
    // If an error is reported by the GoCoder SDK, display an alert dialog containing the error details
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [VideoPlayerViewController showAlertWithTitle:@"Live Streaming Error" status:goCoderStatus presenter:self];
        
        [self updateUIControls];
    });
}

#pragma mark - WZVideoSink

#warning Don't implement this protocol unless your application makes use of it
- (void) videoFrameWasCaptured:(nonnull CVImageBufferRef)imageBuffer framePresentationTime:(CMTime)framePresentationTime frameDuration:(CMTime)frameDuration {
    if (self.goCoder.isStreaming) {
        
        if (self.blackAndWhiteVideoEffect) {
            // convert frame to b/w using CoreImage tonal filter
            CIImage *frameImage = [[CIImage alloc] initWithCVImageBuffer:imageBuffer];
            CIFilter *grayFilter = [CIFilter filterWithName:@"CIPhotoEffectTonal"];
            [grayFilter setValue:frameImage forKeyPath:@"inputImage"];
            frameImage = [grayFilter outputImage];

            CIContext * context = [CIContext contextWithOptions:nil];
            [context render:frameImage toCVPixelBuffer:imageBuffer];
        }
        
    }
}

- (void) videoCaptureInterruptionStarted {
    if (!self.goCoderConfig.backgroundBroadcastEnabled) {
        [self.goCoder endStreaming:self];
    }
}

- (void) videoCaptureUsingQueue:(nullable dispatch_queue_t)queue {
    self.video_capture_queue = queue;
}

#pragma mark - WZAudioSink

#warning Don't implement this protocol unless your application makes use of it
- (void) audioLevelDidChange:(float)level {
//    NSLog(@"%@ %0.2f", @"Audio level did change", level);
}

#warning Don't implement this protocol unless your application makes use of it
- (void) audioPCMFrameWasCaptured:(nonnull const AudioStreamBasicDescription *)pcmASBD bufferList:(nonnull const AudioBufferList *)bufferList time:(CMTime)time sampleRate:(Float64)sampleRate {
    // The commented-out code below simply dampens the amplitude of the audio data.
    // It is intended as an example of how one would access and modify the audio sample data.

//    int16_t *fdata = bufferList->mBuffers[0].mData;
//    
//    for (int i = 0; i < bufferList->mBuffers[0].mDataByteSize/sizeof(*fdata); i++) {
//        *fdata = (int16_t)(*fdata * 0.1);
//        fdata++;
//    }
}


#pragma mark - WZAudioEncoderSink

#warning Don't implement this protocol unless your application makes use of it
- (void) audioSampleWasEncoded:(nullable CMSampleBufferRef)data {
    if (self.writeMP4) {
        [self.mp4Writer appendAudioSample:data];
    }
}


#pragma mark - WZVideoEncoderSink

#warning Don't implement this protocol unless your application makes use of it
- (void) videoFrameWasEncoded:(nonnull CMSampleBufferRef)data {
    
    // update the broadcast time label
    if (CMTimeCompare(self.broadcastStartTime, kCMTimeInvalid) == 0) {
        self.broadcastStartTime = CMSampleBufferGetPresentationTimeStamp(data);
    }
    else {
        CMTime diff = CMTimeSubtract(CMSampleBufferGetPresentationTimeStamp(data), self.broadcastStartTime);
        Float64 seconds = CMTimeGetSeconds(diff);
        NSInteger duration = (NSInteger)seconds;
        
        NSString *timeString = [NSString stringWithFormat:@"%02ld:%02ld", (long)(duration / 60), (long)(duration % 60)];
        
        dispatch_async(dispatch_get_main_queue(), ^{
            self.timeLabel.text = timeString;
        });
        
    }
    
    if (self.writeMP4) {
        [self.mp4Writer appendVideoSample:data];
    }
}

#pragma mark - WZDataSink

- (void) onData:(WZDataEvent *)dataEvent {
    NSLog(@"Got data - %@", dataEvent.description);
}

#pragma mark -

+ (void) showAlertWithTitle:(NSString *)title status:(WZStatus *)status presenter:(UIViewController *)presenter {
    
    [SettingsViewController presentAlert:title message:status.description presenter:presenter];
}

+ (void) showAlertWithTitle:(NSString *)title error:(NSError *)error presenter:(UIViewController *)presenter {
    
    [SettingsViewController presentAlert:title message:error.localizedDescription presenter:presenter];
}


@end





