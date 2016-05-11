//
//  MP4Writer.m
//  SDKSampleApp
//
//  This code and all components (c) Copyright 2015-2016, Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//

#import "MP4Writer.h"
#import <AVFoundation/AVFoundation.h>

NSString *const MP4Filename = @"GoCoderMovie.mov";

@interface MP4Writer () {
}

@property (nonatomic, strong) AVAssetWriter* writer;
@property (nonatomic, strong) AVAssetWriterInput *videoWriterInput;
@property (nonatomic, strong) AVAssetWriterInput *audioWriterInput;
@property (nonatomic, assign) BOOL startedSession;
@property (nonatomic, assign) BOOL firstAudioBuffer;
@property (nonatomic, assign) BOOL waitForAudioFrame;

@end

@implementation MP4Writer

- (BOOL) prepareWithConfig:(WowzaConfig *)config {
    
    BOOL result = FALSE;
    
    NSError *error = nil;
    
    NSURL *videoURL = [self videoFilePath];
    if (videoURL) {
        self.writer = [[AVAssetWriter alloc] initWithURL:videoURL fileType:AVFileTypeMPEG4 error:&error];
        if (error) {
            return result;
        }
      
        // video input
        CMVideoFormatDescriptionRef formatDescription = nil;
        CMVideoFormatDescriptionCreate(NULL, kCMVideoCodecType_H264, (int32_t)config.videoWidth, (int32_t)config.videoHeight, nil, &formatDescription);
        
        self.videoWriterInput = [AVAssetWriterInput assetWriterInputWithMediaType:AVMediaTypeVideo outputSettings:nil sourceFormatHint:formatDescription];
        
        self.videoWriterInput.expectsMediaDataInRealTime = YES;
        
        [self.writer addInput:self.videoWriterInput];
        
        
        // audio input will be initialized when first audio frame arrives
        if (config.audioEnabled) {
            self.waitForAudioFrame = YES;
        }
        
        result = TRUE;
    }
    
    
    return result;
}

- (void) prepareAudioWriter:(CMAudioFormatDescriptionRef)audioFormatDescription {
    if (self.audioWriterInput == nil) {
        self.audioWriterInput = [AVAssetWriterInput assetWriterInputWithMediaType:AVMediaTypeAudio outputSettings:nil sourceFormatHint:audioFormatDescription];
        
        self.audioWriterInput.expectsMediaDataInRealTime = YES;
        [self.writer addInput:self.audioWriterInput];
    }
}

- (void) startWriting {
    if (self.waitForAudioFrame)
        return;
    
    if (self.writer.status != AVAssetWriterStatusWriting) {
        self.startedSession = NO;
        self.firstAudioBuffer = YES;
        
        if (![self.writer startWriting]) {
            NSLog (@"Error in startWriting");
            [self logWriterStatus];
        }
        else {
            NSLog (@"Started writing video file");
        }
    }
}

- (void) stopWriting {
    [self.writer finishWritingWithCompletionHandler:^{
        //
    }];
}

- (void) appendVideoSample:(CMSampleBufferRef)videoSample {
    if (self.videoWriterInput.readyForMoreMediaData && self.writer.status == AVAssetWriterStatusWriting) {
        if (videoSample != nil) {
            if (!self.startedSession) {
                CMTime pts = CMSampleBufferGetPresentationTimeStamp(videoSample);
                [self.writer startSessionAtSourceTime:pts];
                self.startedSession = YES;
            }
            BOOL appended = [self.videoWriterInput appendSampleBuffer:videoSample];
            
            if (!appended) {
                [self logWriterStatus];
                
            }
        }
    }
}


- (void) appendAudioSample:(CMSampleBufferRef)audioSample {
    if (audioSample != nil && self.waitForAudioFrame) {
        CMFormatDescriptionRef formatDescription = CMSampleBufferGetFormatDescription(audioSample);
        CMAudioFormatDescriptionRef audioFormatDescription = (CMAudioFormatDescriptionRef)formatDescription;
        [self prepareAudioWriter:audioFormatDescription];
        self.waitForAudioFrame = NO;
        [self startWriting];
    }
    
    if (self.audioWriterInput.readyForMoreMediaData && self.writer.status == AVAssetWriterStatusWriting) {
        if (audioSample != nil) {
            if (!self.startedSession) {
                CMTime pts = CMSampleBufferGetPresentationTimeStamp(audioSample);
                [self.writer startSessionAtSourceTime:pts];
                self.startedSession = YES;
            }
            
            BOOL appended = [self.audioWriterInput appendSampleBuffer:audioSample];
            
            if (!appended) {
                [self logWriterStatus];
                
            }
        }
    }
}

- (void) logWriterStatus {
    switch (self.writer.status) {
        case AVAssetWriterStatusFailed:
            NSLog (@"AVAssetWriter status: AVAssetWriterStatusFailed");
            NSLog (@"%@", self.writer.error.description);
            break;
        case AVAssetWriterStatusCancelled:
            NSLog (@"AVAssetWriter status: AVAssetWriterStatusCancelled");
            break;
        case AVAssetWriterStatusUnknown:
            NSLog (@"AVAssetWriter status: AVAssetWriterStatusUnknown");
            break;
        case AVAssetWriterStatusWriting:
            NSLog (@"AVAssetWriter status: AVAssetWriterStatusWriting");
            break;
        case AVAssetWriterStatusCompleted:
            NSLog (@"AVAssetWriter status: AVAssetWriterStatusCompleted");
            break;
        default:
            break;
    }
}

- (NSURL *) videoFilePath {
    NSArray * paths = [[NSFileManager defaultManager] URLsForDirectory:NSCachesDirectory inDomains:NSUserDomainMask];
    if (paths.count) {
        NSURL *url = paths.lastObject;
        url = [url URLByAppendingPathComponent:MP4Filename];
        
        if ([[NSFileManager defaultManager] fileExistsAtPath:url.path]) {
            NSError *error = nil;
            [[NSFileManager defaultManager] removeItemAtURL:url error:&error];
        }
        
        return url;
    }
    
    return nil;
    
}

@end
