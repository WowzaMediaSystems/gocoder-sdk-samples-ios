//
//  VideoPlayerViewController.h
//  SDKSampleApp
//
//  This code and all components (c) Copyright 2015-2016, Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//

#import <UIKit/UIKit.h>

@class WZStatus;

extern NSString *const SDKSampleSavedConfigKey;
extern NSString *const SDKSampleAppLicenseKey;

@interface VideoPlayerViewController : UIViewController

+ (void) showAlertWithTitle:(NSString *)title status:(WZStatus *)status presenter:(UIViewController *)presenter;
+ (void) showAlertWithTitle:(NSString *)title error:(NSError *)error presenter:(UIViewController *)presenter;

@end

