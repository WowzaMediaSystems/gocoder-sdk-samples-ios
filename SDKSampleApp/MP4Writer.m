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

static BOOL isKeyFrame(CMSampleBufferRef sample) {
    BOOL isKey = NO;
    
    CFArrayRef attachments = CMSampleBufferGetSampleAttachmentsArray(sample, 0);
    if (CFArrayGetCount(attachments) > 0) {
        CFBooleanRef value;
        Boolean notSyncValue = CFDictionaryGetValueIfPresent
            ((CFDictionaryRef) CFArrayGetValueAtIndex(attachments, 0),
             kCMSampleAttachmentKey_NotSync,
             (const void **)(&value));
        
        isKey = !notSyncValue || !CFBooleanGetValue(value);
    }
    
    return isKey;
}

@interface MP4Writer () {
}

@property (nonatomic, assign, readwrite) BOOL writing;
@property (nonatomic, strong) AVAssetWriter* writer;
@property (nonatomic, strong) AVAssetWriterInput *videoWriterInput;
@property (nonatomic, strong) AVAssetWriterInput *audioWriterInput;
@property (nonatomic, assign) BOOL startedSession;
@property (nonatomic, assign) BOOL firstVideoBuffer;
@property (nonatomic, assign) BOOL firstAudioBuffer;
@property (nonatomic, assign) CMTime firstVideoFrameTime;

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
            [self prepareAudioWriter];
        }
        
        result = TRUE;
    }
    
    
    return result;
}

- (CMAudioFormatDescriptionRef) makeAudioFormatDescription {
    
    CMAudioFormatDescriptionRef audioFormat = nil;
    
    AudioStreamBasicDescription absd = {0};
    absd.mSampleRate = [[AVAudioSession sharedInstance] sampleRate];
    absd.mFormatID = kAudioFormatMPEG4AAC;
    absd.mFormatFlags = kMPEG4Object_AAC_Main;
    
    CMAudioFormatDescriptionCreate(NULL, &absd, 0, NULL, 0, NULL, NULL, &audioFormat);
    
    return audioFormat;
}

- (void) prepareAudioWriter {
    if (self.audioWriterInput == nil) {
        self.audioWriterInput = [AVAssetWriterInput assetWriterInputWithMediaType:AVMediaTypeAudio outputSettings:nil sourceFormatHint:self.makeAudioFormatDescription];
        
        self.audioWriterInput.expectsMediaDataInRealTime = YES;
        [self.writer addInput:self.audioWriterInput];
    }
}

- (void) startWriting {
    
    if (self.writer.status != AVAssetWriterStatusWriting) {
        self.startedSession = NO;
        self.firstAudioBuffer = YES;
        self.firstVideoBuffer = YES;
        self.firstVideoFrameTime = kCMTimeInvalid;
        self.writing = YES;
        
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
    self.writing = NO;
    [self.writer finishWritingWithCompletionHandler:^{
        NSLog(@"Stopped writing video file");
    }];
}

- (void) logPresentationTime:(CMSampleBufferRef)sample logPrefix:(NSString *)logPrefix {
    // Note: uncomment the below if you want to log the time stamp of each audio and video sample that is written
//    CMTime time = CMSampleBufferGetPresentationTimeStamp(sample);
//    float seconds = CMTimeGetSeconds(time);
//    NSLog(@"%@ time: %0.3f", logPrefix, seconds);
}

- (void) appendVideoSample:(CMSampleBufferRef)videoSample {
    if (self.firstVideoBuffer && !isKeyFrame(videoSample)) {
        NSLog(@"MP4Writer:appendVideoSample: first frame not key, discarding");
        return;
    }
    
    self.firstVideoBuffer = NO;
    
    if (self.videoWriterInput.readyForMoreMediaData && self.writer.status == AVAssetWriterStatusWriting) {
        if (videoSample != nil) {
            if (!self.startedSession) {
                CMTime pts = CMSampleBufferGetPresentationTimeStamp(videoSample);
                [self.writer startSessionAtSourceTime:pts];
                self.startedSession = YES;
                NSLog(@"MP4Writer: started session in appendVideoSample");
            }
            BOOL appended = [self.videoWriterInput appendSampleBuffer:videoSample];
            
            if (CMTimeCompare(kCMTimeInvalid, self.firstVideoFrameTime) == 0) {
                self.firstVideoFrameTime = CMSampleBufferGetPresentationTimeStamp(videoSample);
            }
            
            [self logPresentationTime:videoSample logPrefix:@"Video Sample"];
            
            if (!appended) {
                [self logWriterStatus];
            }
        }
    }
    else {
        NSLog(@"MP4Writer:appendVideoSample - sample not appended;  readyForMoreMediaData = %d, status = %ld", self.audioWriterInput.readyForMoreMediaData, (long)self.writer.status);
    }
}


- (void) primeAudio:(CMSampleBufferRef)audioSample {
    CMAttachmentMode attachmentMode;
    CFTypeRef trimDuration = CMGetAttachment(audioSample, kCMSampleBufferAttachmentKey_TrimDurationAtStart, &attachmentMode);
    
    if (!trimDuration) {
        NSLog(@"MP4Writer - Priming audio");
        CMTime trimTime = CMTimeMakeWithSeconds(0.1, 1000000000);
        CFDictionaryRef timeDict = CMTimeCopyAsDictionary(trimTime, kCFAllocatorDefault);
        CMSetAttachment(audioSample, kCMSampleBufferAttachmentKey_TrimDurationAtStart, timeDict, kCMAttachmentMode_ShouldPropagate);
        CFRelease(timeDict);
    }
}

- (void) appendAudioSample:(CMSampleBufferRef)audioSample {
    
    if (CMTimeCompare(kCMTimeInvalid, self.firstVideoFrameTime) == 0 ||
        CMTimeCompare(self.firstVideoFrameTime, CMSampleBufferGetPresentationTimeStamp(audioSample)) == 1) {
        return;
    }
    
    if (self.audioWriterInput.readyForMoreMediaData && self.writer.status == AVAssetWriterStatusWriting) {
        if (audioSample != nil) {
            if (!self.startedSession) {
                CMTime pts = CMSampleBufferGetPresentationTimeStamp(audioSample);
                [self.writer startSessionAtSourceTime:pts];
                self.startedSession = YES;
                NSLog(@"MP4Writer: started session in appendAudioSample");
            }
            
            if (_firstAudioBuffer) {
                _firstAudioBuffer = NO;
                [self primeAudio:audioSample];
            }
            
            BOOL appended = [self.audioWriterInput appendSampleBuffer:audioSample];
            
            [self logPresentationTime:audioSample logPrefix:@"Audio Sample"];
            
            if (!appended) {
                [self logWriterStatus];
                
            }
        }
    }
    else {
        NSLog(@"MP4Writer:appendAudioSample - sample not appended;  readyForMoreMediaData = %d, status = %ld", self.audioWriterInput.readyForMoreMediaData, (long)self.writer.status);
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
