//
//  SettingsViewController.h
//  SDKSampleApp
//
//  This code and all components (c) Copyright 2015-2016, Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//

#import <UIKit/UIKit.h>

@class SettingsViewModel;

typedef NS_ENUM(NSUInteger, SettingsViewSection) {
    SettingsViewSectionVideo = 0,
    SettingsViewSectionAudio,
    SettingsViewSectionBroadcast,
    SettingsViewSectionCaptureOrientationMode,
    SettingsViewSectionBroadcastOrientationMode,
    SettingsViewSectionBroadcastScaleMode,
    SettingsViewSectionBandwidthThrottling,
    SettingsViewSectionBackgroundMode,
    SettingsViewSectionVideoEffects,
    SettingsViewSectionRecordVideoLocally,
    SettingsViewSectionCount
};

@interface SettingsViewController : UITableViewController

@property (nonatomic, strong, nonnull) SettingsViewModel *viewModel;

- (void) addDisplaySection:(SettingsViewSection)section;
- (void) addAllSections;
- (void) removeDisplaySection:(SettingsViewSection)section;

@end
