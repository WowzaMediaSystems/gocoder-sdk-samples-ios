//
//  SettingsViewController.m
//  SDKSampleApp
//
//  This code and all components (c) Copyright 2015-2016, Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//

#import "SettingsViewController.h"
#import "SettingsViewModel.h"
#import "SettingsTextFieldCell.h"
#import "CustomFrameSizeViewController.h"


@interface SettingsViewController ()

@property (nonatomic, strong, nonnull) NSMutableArray *sectionsToDisplay;

@end

@implementation SettingsViewController

- (NSMutableArray *) sectionsToDisplay {
    if (!_sectionsToDisplay) {
        _sectionsToDisplay = [NSMutableArray new];
    }
    
    return _sectionsToDisplay;
}

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void) viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.tableView reloadData];
}

- (void) didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void) addDisplaySection:(SettingsViewSection)section {
    [self.sectionsToDisplay addObject:[NSNumber numberWithInteger:section]];
}

- (void) removeDisplaySection:(SettingsViewSection)section {
    [self.sectionsToDisplay removeObject:[NSNumber numberWithInteger:section]];
}

- (void) addAllSections {
    [self.sectionsToDisplay removeAllObjects];
    
    [self addDisplaySection:SettingsViewSectionVideo];
    [self addDisplaySection:SettingsViewSectionAudio];
    [self addDisplaySection:SettingsViewSectionBroadcast];
    [self addDisplaySection:SettingsViewSectionCaptureOrientationMode];
    [self addDisplaySection:SettingsViewSectionBroadcastOrientationMode];
    [self addDisplaySection:SettingsViewSectionBroadcastScaleMode];
    [self addDisplaySection:SettingsViewSectionBandwidthThrottling];
    [self addDisplaySection:SettingsViewSectionBackgroundMode];
    [self addDisplaySection:SettingsViewSectionVideoEffects];
    [self addDisplaySection:SettingsViewSectionRecordVideoLocally];
}

- (SettingsViewSection) sectionAtIndex:(NSUInteger)index {
    return ((NSNumber *)[self.sectionsToDisplay objectAtIndex:index]).integerValue;
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return self.sectionsToDisplay.count;
}

- (NSString *) tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    NSString *title = @"";
    
    SettingsViewSection settingsSection = [self sectionAtIndex:section];
    
    switch (settingsSection) {
        case SettingsViewSectionVideo:
            title = @"Video Settings";
            break;
            
        case SettingsViewSectionAudio:
            title = @"Audio Settings";
            break;
            
        case SettingsViewSectionBroadcast:
            title = @"Wowza Broadcast Settings";
            break;
            
        case SettingsViewSectionCaptureOrientationMode:
            title = @"Capture Orientation Settings";
            break;
            
        case SettingsViewSectionBroadcastOrientationMode:
            title = @"Broadcast Orientation Settings";
            break;
            
        case SettingsViewSectionBroadcastScaleMode:
            title = @"Broadcast Scale Mode";
            break;
            
        case SettingsViewSectionBandwidthThrottling:
            title = @"Low Bandwidth Throttling";
            break;
            
        case SettingsViewSectionBackgroundMode:
            title = @"Background Broadcast";
            break;
            
        case SettingsViewSectionVideoEffects:
            title = @"Video Effects";
            break;
            
        case SettingsViewSectionRecordVideoLocally:
            title = @"Video Recording";
            break;
            
        default:
            break;
    }
    
    return title;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSInteger count = 0;
    
    SettingsViewSection settingsSection = [self sectionAtIndex:section];
    
    switch (settingsSection) {
        case SettingsViewSectionVideo:
            count = self.viewModel.videoQualityDisplayNames.count + 1;
            break;
            
        case SettingsViewSectionAudio:
            count = SettingsAudioItemCount;
            break;
            
        case SettingsViewSectionBroadcast:
            count = SettingsBroadcastItemCount;
            break;
            
        case SettingsViewSectionCaptureOrientationMode:
            count = 2;
            break;
            
        case SettingsViewSectionBroadcastOrientationMode:
            count = 3;
            break;
            
        case SettingsViewSectionBroadcastScaleMode:
            count = 2;
            break;
            
        case SettingsViewSectionBandwidthThrottling:
            count = SettingsLowBandwidthItemCount;
            break;
            
        case SettingsViewSectionBackgroundMode:
            count = 1;
            break;
            
        case SettingsViewSectionVideoEffects:
        case SettingsViewSectionRecordVideoLocally:
            count = 1;
            break;
            
        default:
            break;
    }
    
    return count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    SettingsViewSection settingsSection = [self sectionAtIndex:indexPath.section];
    
    if (settingsSection == SettingsViewSectionVideo) {
        if (indexPath.row == self.viewModel.videoQualityDisplayNames.count) {
            UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"customFrameSizeCell" forIndexPath:indexPath];
            if (self.viewModel.selectedVideoQuality == NSNotFound) {
                cell.textLabel.text = @"Custom";
                cell.detailTextLabel.text = [NSString stringWithFormat:@"%@, %@ fps, keyframe int. %@", self.viewModel.videoConfigDescription, self.viewModel.customVideoFrameRate, self.viewModel.customVideoKeyFrameInterval];
            }
            else {
                cell.detailTextLabel.text = @"";
            }
            return cell;
        }
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"videoSettingCell" forIndexPath:indexPath];
        cell.textLabel.text = [self.viewModel.videoQualityDisplayNames objectAtIndex:indexPath.row];
        
        cell.accessoryType = (self.viewModel.selectedVideoQuality == indexPath.row) ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;
        cell.accessoryView = nil;
        
        return cell;
    }
    
    else if (settingsSection == SettingsViewSectionCaptureOrientationMode) {
        NSString *title = @"";
        BOOL on = NO;
        switch (indexPath.row) {
            case 0:
                title = @"Rotate Captured Video";
                on = self.viewModel.capturedVideoRotates;
                break;
                
            case 1:
                title = @"Rotate Video Preview";
                on = self.viewModel.videoPreviewRotates;
                break;
                
            default:
                break;
        }
        
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"videoSettingCell" forIndexPath:indexPath];
        cell.textLabel.text = title;
        
        cell.accessoryType = on ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;
        cell.accessoryView = nil;
        
        return cell;
    }
    
    else if (settingsSection == SettingsViewSectionBroadcastOrientationMode) {
        NSString *title = @"";
        BOOL on = NO;
        switch (indexPath.row) {
            case 0:
                title = @"Same as Device";
                on = self.viewModel.broadcastVideoOrientation == WZBroadcastOrientationSameAsDevice;
                break;
                
            case 1:
                title = @"Always Landscape";
                on = self.viewModel.broadcastVideoOrientation == WZBroadcastOrientationAlwaysLandscape;
                break;
                
            case  2:
                title = @"Always Portrait";
                on = self.viewModel.broadcastVideoOrientation == WZBroadcastOrientationAlwaysPortrait;
                
            default:
                break;
        }
        
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"videoSettingCell" forIndexPath:indexPath];
        cell.textLabel.text = title;
        
        cell.accessoryType = on ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;
        cell.accessoryView = nil;
        
        return cell;
    }
    
    else if (settingsSection == SettingsViewSectionBroadcastScaleMode) {
        NSString *title = @"";
        BOOL on = NO;
        switch (indexPath.row) {
            case 0:
                title = @"Aspect Fit";
                on = self.viewModel.broadcastScaleMode == WZBroadcastScaleModeAspectFit;
                break;
                
            case 1:
                title = @"Aspect Fill";
                on = self.viewModel.broadcastScaleMode == WZBroadcastScaleModeAspectFill;
                break;
                
            default:
                break;
        }
        
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"videoSettingCell" forIndexPath:indexPath];
        cell.textLabel.text = title;
        
        cell.accessoryType = on ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;
        cell.accessoryView = nil;
        
        return cell;
    }
    
    else if (settingsSection == SettingsViewSectionVideoEffects) {
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"videoSettingCell" forIndexPath:indexPath];
        cell.textLabel.text = @"Black and White";
        cell.accessoryType = UITableViewCellAccessoryNone;
        UISwitch *effectSwitch = [[UISwitch alloc] init];
        effectSwitch.on = self.viewModel.blackAndWhite;
        [effectSwitch addTarget:self action:@selector(didChangeBlackAndWhiteSwitch:) forControlEvents:UIControlEventValueChanged];
        cell.accessoryView = effectSwitch;
        
        return cell;
    }
    
    else if (settingsSection == SettingsViewSectionRecordVideoLocally) {
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"videoSettingCell" forIndexPath:indexPath];
        cell.textLabel.text = @"Record Video Locally";
        cell.accessoryType = UITableViewCellAccessoryNone;
        UISwitch *recordSwitch = [[UISwitch alloc] init];
        recordSwitch.on = self.viewModel.recordVideoLocally;
        [recordSwitch addTarget:self action:@selector(didChangeRecordVideoLocallySwitch:) forControlEvents:UIControlEventValueChanged];
        cell.accessoryView = recordSwitch;
        
        return cell;
    }
    
    NSString *name = nil;
    NSString *keyPath = nil;
    NSString *cellIdentifier = @"textFieldCell";
    UIKeyboardType keyboardType = UIKeyboardTypeDefault;
    
    if (settingsSection == SettingsViewSectionAudio) {
        switch (indexPath.row) {
            case SettingsAudioItemBitrate:
                name = @"Bitrate";
                keyPath = @"audioBitrate";
                keyboardType = UIKeyboardTypeNumberPad;
                break;
                
            case SettingsAudioItemSampleRate:
                name = @"Sample rate";
                keyPath = @"audioSampleRate";
                keyboardType = UIKeyboardTypeNumberPad;
                break;
                
            case SettingsAudioItemChannels:
                name = @"Channels";
                keyPath = @"audioChannels";
                keyboardType = UIKeyboardTypeNumberPad;
                break;
        }
    }
    
    else if (settingsSection == SettingsViewSectionBandwidthThrottling) {
        cellIdentifier = @"floatingTextFieldCell";
        
        switch (indexPath.row) {
            case SettingsLowBandwidthItemBitrateScale:
                name = @"Bitrate Scale Factor";
                keyPath = @"videoBitrateScale";
                keyboardType = UIKeyboardTypeDecimalPad;
                break;
                
            case SettingsLowBandwidthItemFrameBufferMultiplier:
                name = @"Frame Buffer Multiplier";
                keyPath = @"videoFrameBufferMultiplier";
                keyboardType = UIKeyboardTypeNumberPad;
                break;

            case SettingsLowBandwidthItemFrameSkipCount:
                name = @"Frame Skip Count";
                keyPath = @"videoFrameSkipCount";
                keyboardType = UIKeyboardTypeNumberPad;
                break;

        }
    }
    else if (settingsSection == SettingsViewSectionBackgroundMode) {
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"videoSettingCell" forIndexPath:indexPath];
        cell.textLabel.text = @"Background Broadcast Enabled";
        cell.accessoryType = UITableViewCellAccessoryNone;
        UISwitch *backgroundSwitch = [[UISwitch alloc] init];
        backgroundSwitch.on = self.viewModel.backgroundBroadcastEnabled;
        [backgroundSwitch addTarget:self action:@selector(didChangeBackgroundBroadcastSwitch:) forControlEvents:UIControlEventValueChanged];
        cell.accessoryView = backgroundSwitch;
        
        return cell;
    }
    
    else {
        switch (indexPath.row) {
            case SettingsBroadcastItemHostAddress:
                name = @"Host Address";
                keyPath = @"hostAddress";
                keyboardType = UIKeyboardTypeURL;
                break;
                
            case SettingsBroadcastItemPort:
                name = @"Port";
                keyPath = @"port";
                keyboardType = UIKeyboardTypeNumberPad;
                break;
                
            case SettingsBroadcastItemApplicationName:
                name = @"Application Name";
                keyPath = @"applicationName";
                break;
                
            case SettingsBroadcastItemStreamName:
                name = @"Stream Name";
                keyPath = @"streamName";
                break;
                
            case SettingsBroadcastItemUsername:
                name = @"User name";
                keyPath = @"username";
                break;
                
            case SettingsBroadcastItemPassword:
                name = @"Password";
                keyPath = @"password";
                break;
                
            default:
                break;
        }
    }
    
    SettingsTextFieldCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier forIndexPath:indexPath];
    cell.viewModel = self.viewModel;
    cell.label.text = name;
    cell.modelKeyPath = keyPath;
    cell.textField.keyboardType = keyboardType;
    cell.textField.secureTextEntry = (indexPath.row == SettingsBroadcastItemPassword);
    
    return cell;
}

- (void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    SettingsViewSection settingsSection = [self sectionAtIndex:indexPath.section];
    
    if (settingsSection == SettingsViewSectionVideo && indexPath.row < self.viewModel.videoQualityDisplayNames.count) {
        self.viewModel.selectedVideoQuality = indexPath.row;
        [self.tableView reloadData];
    }
    else if (settingsSection == SettingsViewSectionCaptureOrientationMode) {
        switch (indexPath.row) {
            case 0:
                self.viewModel.capturedVideoRotates = !self.viewModel.capturedVideoRotates;
                break;
                
            case 1:
                self.viewModel.videoPreviewRotates = !self.viewModel.videoPreviewRotates;
                break;
                
            default:
                break;
        }
        
        [self.tableView reloadData];
    }
    else if (settingsSection == SettingsViewSectionBroadcastOrientationMode) {
        switch (indexPath.row) {
            case 0:
                self.viewModel.broadcastVideoOrientation = WZBroadcastOrientationSameAsDevice;
                break;
                
            case 1:
                self.viewModel.broadcastVideoOrientation = WZBroadcastOrientationAlwaysLandscape;
                break;
                
            case 2:
                self.viewModel.broadcastVideoOrientation = WZBroadcastOrientationAlwaysPortrait;
                break;
                
            default:
                break;
        }
        
        [self.tableView reloadData];
    }
    
    else if (settingsSection == SettingsViewSectionBroadcastScaleMode) {
        switch (indexPath.row) {
            case 0:
                self.viewModel.broadcastScaleMode = WZBroadcastScaleModeAspectFit;
                break;
                
            case 1:
                self.viewModel.broadcastScaleMode = WZBroadcastScaleModeAspectFill;
                break;
                
            default:
                break;
        }
        
        [self.tableView reloadData];
    }
}


#pragma mark - Actions

- (IBAction) didTapDoneButton:(id)sender {
    [self.navigationController dismissViewControllerAnimated:YES completion:nil];
}

- (IBAction) didChangeBlackAndWhiteSwitch:(id)sender {
    UISwitch *effectSwitch = (UISwitch *)sender;
    self.viewModel.blackAndWhite = effectSwitch.isOn;
}

- (IBAction) didChangeBackgroundBroadcastSwitch:(id)sender {
    UISwitch *backgroundSwitch = (UISwitch *)sender;
    self.viewModel.backgroundBroadcastEnabled = backgroundSwitch.isOn;
}

- (IBAction) didChangeRecordVideoLocallySwitch:(id)sender {
    UISwitch *recordSwitch = (UISwitch *)sender;
    self.viewModel.recordVideoLocally = recordSwitch.isOn;
}

#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.destinationViewController isKindOfClass:[CustomFrameSizeViewController class]]) {
        ((CustomFrameSizeViewController *)segue.destinationViewController).viewModel = self.viewModel;
    }
}

@end
