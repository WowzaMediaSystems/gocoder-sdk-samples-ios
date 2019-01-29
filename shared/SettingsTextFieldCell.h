//
//  SettingsTextFieldCell.h
//  SDKSampleApp
//
//  This code and all components © 2015 – 2019 Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//

#import <UIKit/UIKit.h>

@class SettingsViewModel;

@interface SettingsTextFieldCell : UITableViewCell

@property (nonatomic, strong) IBOutlet UILabel *label;
@property (nonatomic, strong) IBOutlet UITextField *textField;
@property (nonatomic, strong) NSString *modelKeyPath;
@property (nonatomic, strong) SettingsViewModel *viewModel;

@end
