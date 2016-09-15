//
//  SettingsTextFieldCell.m
//  SDKSampleApp
//
//  This code and all components (c) Copyright 2015-2016, Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//

#import "SettingsTextFieldCell.h"
#import "SettingsViewModel.h"

@interface SettingsTextFieldCellToolbar : UIToolbar

@property (nonatomic, weak) UITextField *textField;

@end

@implementation SettingsTextFieldCellToolbar

- (instancetype) initWithTextField:(UITextField *)textField {
    if (self = [super initWithFrame:CGRectMake(0, 0, 0, 30)]) {
        [self setup];
        _textField = textField;
    }
    
    return self;
}

- (void) setup {
    UIBarButtonItem *done = [[UIBarButtonItem alloc] initWithTitle:@"Done" style:UIBarButtonItemStylePlain target:self action:@selector(didTapDone:)];
    UIBarButtonItem *space = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil];
    self.items = @[space, done];
}

- (void) didTapDone:(id)sender {
    if (self.textField)
        [self.textField resignFirstResponder];
}

@end


@interface SettingsTextFieldCell () <UITextFieldDelegate>

@end

@implementation SettingsTextFieldCell

- (void)awakeFromNib {
    [super awakeFromNib];
    
    if (self.textField) {
        self.textField.delegate = self;
        self.textField.inputAccessoryView = [[SettingsTextFieldCellToolbar alloc] initWithTextField:self.textField];
    }
}

- (void) setModelKeyPath:(NSString *)modelKeyPath {
    _modelKeyPath = modelKeyPath;
    self.textField.text = [self.viewModel valueForKey:_modelKeyPath];
}

#pragma mark - UITextFieldDelegate

- (void)textFieldDidEndEditing:(UITextField *)textField {
    [self.viewModel setValue:textField.text forKey:self.modelKeyPath];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return NO;
}

@end
