//
//  CustomFrameSizeViewController.m
//  SDKSampleApp
//
//  This code and all components (c) Copyright 2015-2016, Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//

#import "CustomFrameSizeViewController.h"
#import "SettingsTextFieldCell.h"
#import "SettingsViewModel.h"

@interface CustomFrameSizeViewController ()

@end

@implementation CustomFrameSizeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return SettingsCustomVideoItemCount;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NSString *name = nil;
    NSString *keyPath = nil;
    UIKeyboardType keyboardType = UIKeyboardTypeNumberPad;
    
    switch (indexPath.row) {
        case SettingsCustomVideoItemWidth:
            name = @"Width";
            keyPath = @"customFrameWidth";
            keyboardType = UIKeyboardTypeNumberPad;
            break;
            
        case SettingsCustomVideoItemHeight:
            name = @"Height";
            keyPath = @"customFrameHeight";
            keyboardType = UIKeyboardTypeNumberPad;
            break;
            
        case SettingsCustomVideoItemBitrate:
            name = @"Bitrate";
            keyPath = @"customVideoBitrate";
            keyboardType = UIKeyboardTypeNumberPad;
            break;
            
        case SettingsCustomVideoItemFrameRate:
            name = @"Frame Rate";
            keyPath = @"customVideoFrameRate";
            keyboardType = UIKeyboardTypeNumberPad;
            break;
            
        case SettingsCustomVideoItemKeyFrameInterval:
            name = @"Key Frame Interval";
            keyPath = @"customVideoKeyFrameInterval";
            keyboardType = UIKeyboardTypeNumberPad;
            break;
    }
    
    
    SettingsTextFieldCell *cell = [tableView dequeueReusableCellWithIdentifier:@"textFieldCell" forIndexPath:indexPath];
    cell.viewModel = self.viewModel;
    cell.label.text = name;
    cell.modelKeyPath = keyPath;
    cell.textField.keyboardType = keyboardType;
    
    return cell;
}

@end
