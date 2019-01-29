//
//  MetaDataBroadcastViewController.h
//  SDKSampleApp
//
//  This code and all components © 2015 – 2019 Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//

#import <UIKit/UIKit.h>

@class WOWZStatus;

extern NSString *const SDKSampleSavedConfigKey;
extern NSString *const SDKSampleAppLicenseKey;

@interface MetaDataBroadcastViewController : UIViewController

+ (void) showAlertWithTitle:(NSString *)title status:(WOWZStatus *)status presenter:(UIViewController *)presenter;
+ (void) showAlertWithTitle:(NSString *)title error:(NSError *)error presenter:(UIViewController *)presenter;

@end

