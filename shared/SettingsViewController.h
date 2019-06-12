//
//  SettingsViewController.h
//  SDKSampleApp
//
//  This code and all components © 2015 – 2019 Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//

#import <UIKit/UIKit.h>

@class SettingsViewModel;

typedef NS_ENUM(NSUInteger, SettingsViewSection) {
    SettingsViewSectionVideo = 0,
    SettingsViewSectionAudio,
    SettingsViewSectionBroadcast,
    SettingsViewSectionPlaybackSettings,
    SettingsViewSectionCaptureOrientationMode,
    SettingsViewSectionBroadcastOrientationMode,
    SettingsViewSectionBroadcastScaleMode,
    SettingsViewSectionBandwidthThrottling,
    SettingsViewSectionBackgroundMode,
    SettingsViewSectionVideoMirroring,
    SettingsViewSectionVideoEffects,
    SettingsViewSectionVideoRenderingMethod,
    SettingsViewSectionRecordVideoLocally,
    SettingsViewSectionPlayback,
    SettingsViewSectionPlaybackHLS,
    SettingsViewSectionConnectionCode,
    SettingsViewSectionCount
};

@interface SettingsViewController : UITableViewController

@property (nonatomic, strong, nonnull) SettingsViewModel *viewModel;

+ (void) presentAlert:(nullable NSString *)title message:(nullable NSString *)message presenter:(nonnull UIViewController *)presenter;

- (void) addDisplaySection:(SettingsViewSection)section;
- (void) addAllSections;
- (void) removeDisplaySection:(SettingsViewSection)section;

@end

