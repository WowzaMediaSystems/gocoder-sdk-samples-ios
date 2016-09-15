//
//  MP4Writer.h
//  SDKSampleApp
//
//  This code and all components (c) Copyright 2015-2016, Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//


#import <Foundation/Foundation.h>
#import <WowzaGoCoderSDK/WowzaGoCoderSDK.h>

@interface MP4Writer : NSObject

@property (nonatomic, assign, readonly) BOOL writing;

- (BOOL) prepareWithConfig:(WowzaConfig *)config;
- (void) startWriting;
- (void) stopWriting;
- (void) appendVideoSample:(CMSampleBufferRef)videoSample;
- (void) appendAudioSample:(CMSampleBufferRef)audioSample;

@end
