//
//  SettingsViewModel.h
//  SDKSampleApp
//
//  This code and all components © 2015 – 2019 Wowza Media Systems, LLC. All rights reserved.
//  This code is licensed pursuant to the BSD 3-Clause License.
//

#import <Foundation/Foundation.h>
#import <WowzaGoCoderSDK/WowzaGoCoderSDK.h>

extern NSString * const BlackAndWhiteKey;
extern NSString * const BitmapOverlayKey;
extern NSString * const RecordVideoLocallyKey;
extern NSString * const PlaybackPrerollKey;
extern NSString * const AllowHLSKey;
extern NSString * const HLSURLKey;

typedef NS_ENUM(NSUInteger, SettingsBroadcastItem) {
    SettingsBroadcastItemHostAddress = 0,
    SettingsBroadcastItemPort,
    SettingsBroadcastItemApplicationName,
    SettingsBroadcastItemStreamName,
    SettingsBroadcastItemUsername,
    SettingsBroadcastItemPassword,
    SettingsBroadcastItemCount
};

typedef NS_ENUM(NSUInteger, SettingsAudioItem) {
    SettingsAudioItemBitrate = 0,
    SettingsAudioItemSampleRate,
    SettingsAudioItemChannels,
    SettingsAudioItemCount
};

typedef NS_ENUM(NSUInteger, SettingsLowBandwidthItem) {
    SettingsLowBandwidthItemBitrateScale = 0,
    SettingsLowBandwidthItemFrameBufferMultiplier,
    SettingsLowBandwidthItemFrameSkipCount,
    SettingsLowBandwidthItemCount
};

typedef NS_ENUM(NSUInteger, SettingsCustomVideoItem) {
    SettingsCustomVideoItemWidth = 0,
    SettingsCustomVideoItemHeight,
    SettingsCustomVideoItemBitrate,
    SettingsCustomVideoItemFrameRate,
    SettingsCustomVideoItemKeyFrameInterval,
    SettingsCustomVideoItemCount
    
};

typedef NS_ENUM(NSUInteger, SettingsPlaybackItem) {
    SettingsPlaybackItemPrerollDuration = 0,
    SettingsPlaybackItemCount
};

@class WowzaConfig;

@interface SettingsViewModel : NSObject

@property (nonatomic, strong) NSArray<WOWZMediaConfig *> *supportedPresetConfigs;
@property (nonatomic, readonly) NSArray<NSString *> *videoQualityDisplayNames;
@property (nonatomic, assign) NSUInteger selectedVideoQuality;

@property (nonatomic, readonly) NSString *videoConfigDescription;

@property (nonatomic, strong) NSString *hostAddress;
@property (nonatomic, strong) NSString *port;
@property (nonatomic, strong) NSString *applicationName;
@property (nonatomic, strong) NSString *streamName;
@property (nonatomic, strong) NSString *username;
@property (nonatomic, strong) NSString *password;

@property (nonatomic, strong) WowzaConfig *config;


// the connection code used for quick connection settings setup
@property (nonatomic, strong) NSString *connectionCode;

// the user-selected orientation mode
@property (nonatomic, assign) BOOL capturedVideoRotates;
@property (nonatomic, assign) BOOL videoPreviewRotates;
@property (nonatomic, assign) WOWZBroadcastOrientation broadcastVideoOrientation;
@property (nonatomic, assign) WOWZBroadcastScaleMode broadcastScaleMode;

// the user-selected black-and-white mode (on or off)
@property (nonatomic, assign) BOOL blackAndWhite;
@property (nonatomic, assign) BOOL bitmapOverlay;

// the user-selected hls fallback mode (on or off)
@property (nonatomic, assign) BOOL allowHLS;
// the url string for HLS
@property (nonatomic, strong) NSString *hlsURL;

// the user-selected custom frame width and height
@property (nonatomic, strong) NSString *customFrameWidth;
@property (nonatomic, strong) NSString *customFrameHeight;

// the user-selected custom video bitrate, frame rate and key frame interval
@property (nonatomic, strong) NSString *customVideoBitrate;
@property (nonatomic, strong) NSString *customVideoFrameRate;
@property (nonatomic, strong) NSString *customVideoKeyFrameInterval;

// Audio settings
@property (nonatomic, strong) NSString *audioBitrate;
@property (nonatomic, strong) NSString *audioSampleRate;
@property (nonatomic, strong) NSString *audioChannels;

// Low bandwidth settings
@property (nonatomic, strong) NSString *videoBitrateScale;
@property (nonatomic, strong) NSString *videoFrameBufferMultiplier;
@property (nonatomic, strong) NSString *videoFrameSkipCount;

// the user-selected local recording mode (on or off)
@property (nonatomic, assign) BOOL recordVideoLocally;

// the user-selected local background broadcasting mode (on or off)
@property (nonatomic, assign) BOOL backgroundBroadcastEnabled;

// the user-selected video mirroring mode
@property (nonatomic, assign) BOOL mirrorFrontCamera;
    
@property (nonatomic, assign) WOWZVideoRenderMethod videoRenderingMethod;

- (instancetype) initWithSessionConfig:(WowzaConfig *)config;

@end
