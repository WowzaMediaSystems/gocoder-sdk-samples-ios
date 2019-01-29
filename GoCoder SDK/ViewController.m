//
//  ViewController.m
//  GoCoder SDK
//
//  Created by Benji Brown on 9/19/18.
//  Copyright © 2019 Wowza. All rights reserved.
//

#import "ViewController.h"
#import <WowzaGoCoderSDK/WowzaGoCoderSDK.h>
#import "BroadcastViewController.h"
#import "SettingsViewModel.h"

@interface ViewController ()
@property (nonatomic, strong) WowzaConfig       *goCoderConfig;
@property (nonatomic, strong) SettingsViewModel       *settingsModel;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.versionLabel.text = [NSString stringWithFormat:@"GoCoder SDK v%@", [WOWZVersionInfo verboseString]];
}

-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    [self initConfigValues];
}

-(void)initConfigValues{
    NSData *savedConfig = [[NSUserDefaults standardUserDefaults] objectForKey:SDKSampleSavedConfigKey];
    if (savedConfig) {
        self.goCoderConfig = [NSKeyedUnarchiver unarchiveObjectWithData:savedConfig];
        self.settingsModel = [[SettingsViewModel alloc] initWithSessionConfig:self.goCoderConfig];
        [self.settingsModel setBitmapOverlay:NO];
        NSLog(@"Set new values for segue.");
    }
    else{
        self.settingsModel = [[SettingsViewModel alloc] init];
    }
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Make sure your segue name in storyboard is the same as this line
    if ([[segue identifier] isEqualToString:@"bitmapsegue"])
    {
        [self.settingsModel setBitmapOverlay:YES];
        NSLog(@"Set new values for segue2.");
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
