//
//  WZMediaConfig.h
//  WowzaGoCoderSDK
//
//  Copyright 2007 – 2016, Wowza Media Systems, LLC.  All rights
//  reserved.
//
//  The above copyright notice and this permission notice shall be
//  included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
//  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.
//

#import <AVFoundation/AVFoundation.h>




/*!
 @class WZMediaConfig
 @discussion The WZMediaConfig class provides configuration properties for the capture and encoding of video and audio
 */
@interface WZMediaConfig : NSObject <NSMutableCopying, NSCopying, NSCoding>

/*!
 *  @typedef WZFrameSizePreset
 *  @constant WZFrameSizePreset352x288 352 x 288 frame size.
 *  @constant WZFrameSizePreset640x480 640 x 480 frame size.
 *  @constant WZFrameSizePreset1280x720 1280 x 720 frame size (720p).
 *  @constant WZFrameSizePreset1920x1080 1920 x 1080 frame size (1080p).
 *  @constant WZFrameSizePreset3840x2160 3840 x 2160 frame size (UHD 4K).
 *  @constant WZFrameSizePresetCount Count of known frame sizes
 *  @discussion Frame size presets availabe at compile time. Note that not all of these
 *  presets are guarenteed to be supported by a particular device or device camera.
 */
typedef NS_ENUM(NSUInteger, WZFrameSizePreset) {
    WZFrameSizePreset352x288,
    WZFrameSizePreset640x480,
    WZFrameSizePreset1280x720,
    WZFrameSizePreset1920x1080,
    WZFrameSizePreset3840x2160,
    WZFrameSizePresetCount
};

/*!
 *  @typedef WZBroadcastOrientation
 *  @constant WZBroadcastOrientationAlwaysLandscape Always broadcast in landscape orientation.
 *  @constant WZBroadcastOrientationAlwaysPortrait Always broadcast in portrait orientation.
 *  @constant WZBroadcastOrientationSameAsDevice The broadcast orientation will be set according to the orientation of the device at broadcast start time.
 *  @discussion Describes the orientation of the broadcasted video.
 */
typedef NS_ENUM(NSUInteger, WZBroadcastOrientation) {
    WZBroadcastOrientationSameAsDevice,
    WZBroadcastOrientationAlwaysLandscape,
    WZBroadcastOrientationAlwaysPortrait
};

/*!
 *  @typedef WZAudioChannels
 *  @constant WZAudioChannelsMono Mono, or single channel.
 *  @constant WZAudioChannels Stereo, or two-channel.
 *  @discussion Number of audio channels. Note that not all of these channel counts
 *  are guarenteed to be supported by a particular device.
 */
typedef NS_ENUM(NSUInteger, WZAudioChannels) {
    WZAudioChannelsMono     = 1,
    WZAudioChannelsStereo   = 2
};

#pragma mark - Public Class Methods -

/*!
 *  Converts a WZFrameSizePreset to an AVFoundation AVCaptureSessionPreset string.
 *
 *  @param wzPreset The WZFrameSizePreset to be converted.
 *
 *  @return The AVFoundation AVCaptureSessionPreset string that corresponds to the given WZFrameSizePreset.
 */
+ (nullable NSString *) AVCaptureSessionPresetFromPreset:(WZFrameSizePreset)wzPreset;

/*!
 *  Converts a WZFrameSizePreset to the corresponding CGSize for that preset.
 *
 *  @param preset The WZFrameSizePreset to be converted.
 *
 *  @return The CGSize which corresponds to the given WZFrameSizePreset.
 */
+ (CGSize) CGSizeFromPreset:(WZFrameSizePreset)preset;

/*!
 *  Given a width, returns the AVFoundation AVCaptureSessionPreset string that most closely matches that width.
 *
 *  @param width The width being matched.
 *
 *  @return The closest AVFoundation AVCaptureSessionPreset string matching the given width.
 */
+ (nullable NSString *) closestAVCaptureSessionPresetByWidth:(NSUInteger)width;

#pragma mark -

/*!
 *  Returns an array of NSNumber values for each WZFrameSizePreset
 *
 *  @return The array of NSNumber values
 */
+ (nonnull NSArray *) presets;

/*!
 *  Returns an array of WZMediaConfig objects for each WZFrameSizePreset.
 *
 *  @return The array of WZMediaConfig objects.
 */
+ (nonnull NSArray *) presetConfigs;


#pragma mark - Properties -

/*!
 *  Enable or disable video for the configuration.
 */
@property (nonatomic, assign) BOOL videoEnabled;

/*!
 *  Enable or disable audio for the configuration.
 */
@property (nonatomic, assign) BOOL audioEnabled;

#pragma mark -

/*!
 *  The video frame width for the configuration.
 */
@property (nonatomic, assign) NSUInteger videoWidth;

/*!
 *  The video frame height for the configuration.
 */
@property (nonatomic, assign) NSUInteger videoHeight;

/*!
 *  The desired frame rate for the configuration. Note that the actual frame rate
 *  might be reduced if network bandwidth cannot keep up with the desired frame rate.
 */
@property (nonatomic, assign) NSUInteger videoFrameRate;

/*!
 *  The video key frame interval.
 */
@property (nonatomic, assign) NSUInteger videoKeyFrameInterval;

/*!
 *  The desired video bitrate. Note that the actual bitrate
 *  might be reduced if network bandwidth cannot keep up with the desired bitrate.
 */
@property (nonatomic, assign) NSUInteger videoBitrate;

/*!
 *  The factor by which to scale the desired bitrate in low bandwidth conditions.
 *  Valid range is 0.0 to 1.0; any other value will be ignored. Setting a value of
 *  0.0 indicates that the encoder should choose the best value; setting a value of
 *  1.0 indicates that bitrate will never be throttled.
 *  The default is 0.75
 */
@property (nonatomic, assign) Float32 videoBitrateLowBandwidthScalingFactor;

/*!
 *  The value by which to multiply the video frame rate to derive the number of
 *  video frames to buffer before the encoder starts to throttle bitrate 
 *  and/or frame rate.
 *  For example: if the frame rate is 30 and the videoFrameBufferSizeMultiplier is 5,
 *  the encoder will buffer 150 (5 * 30) frames before throttling.
 *  Setting a value of 0 indicates that the encoder should choose the best value.
 *  The default is 4.
 */
@property (nonatomic, assign) NSUInteger videoFrameBufferSizeMultiplier;

#pragma mark -

/*!
 *  Set whether or not to rotate video frames to match the orientation of the device.
 */
@property (nonatomic, assign) BOOL capturedVideoRotates;

/*!
 *  Set whether or not the video session should rotate to match the orientation of the device.
 */
@property (nonatomic, assign) BOOL videoPreviewRotates;


/*!
 *  Set the desired broadcast orientation for a broadcast session. See WZBroadcastOrientation
 *  for allowed values. Default is WZBroadcastOrientationSameAsDevice.
 */
@property (nonatomic, assign) WZBroadcastOrientation broadcastVideoOrientation;

#pragma mark -

/*!
 *  The desired number of audio channels
 */
@property (nonatomic, assign) NSUInteger audioChannels;


/*!
 *  The desired audio sample rate. Note that the actual sample rate
 *  might be different from the desired rate.
 */
@property (nonatomic, assign) NSUInteger audioSampleRate;

/*!
 *  The desired audio bitrate. Note that the actual bitrate
 *  might be different from the desired rate.
 */
@property (nonatomic, assign) NSUInteger audioBitrate;

#pragma mark -

/*!
 *  The video frame size, in CGSize format
 */
@property (nonatomic, readonly) CGSize frameSize;

/*!
 *  A human-readable string describing the video frame size
 */
@property (nonatomic, readonly, nonnull) NSString *frameSizeLabel;

#pragma mark - Public Instance Methods -

/*!
 *  Initialize a new WZMediaConfig with a given preset
 *
 *  @param preset The frame size preset
 *
 *  @return An instance of WZMediaConfig with the specified frame size and
 *  recommended bitrate for that frame size.
 */
- (nonnull instancetype) initWithPreset:(WZFrameSizePreset)preset;

/*!
 *  Sets the frame size of the receiver with that described by a WZFrameSizePreset,
 *  as well as the recommended bitrate for that frame size.
 *
 *  @param preset The frame size preset
 */
- (void) loadPreset:(WZFrameSizePreset)preset;

/*!
 *  Get the receiver's corresponding AVFoundation AVCaptureSessionPreset string
 *
 *  @return The corresponding AVFoundation AVCaptureSessionPreset string for this config.
 */
- (nullable NSString *) toAVCaptureSessionPreset;

/*!
 *  Get the receiver's closest corresponding AVFoundation AVCaptureSessionPreset string
 *
 *  @return The closest corresponding AVFoundation AVCaptureSessionPreset string.
 */
- (nonnull NSString *) toClosestAVCaptureSessionPreset;

#pragma mark -

/*!
 *  Get the receiver's corresponding WZFrameSizePreset
 *
 *  @return The corresponding WZFrameSizePreset
 */
- (WZFrameSizePreset) toPreset;

/*!
 *  Get the receiver's closest corresponding WZFrameSizePreset
 *
 *  @return The closest corresponding WZFrameSizePreset
 */
- (WZFrameSizePreset) toClosestPreset;

#pragma mark -

/*!
 *  Tests the reciever for equality to the given WZMediaConfig
 *
 *  @param other The other WZMediaConfig to test against
 *
 *  @return YES if both the receiver and given config are equal; otherwise NO
 */
- (BOOL) equals:(nonnull WZMediaConfig *)other;

/*!
 *  Determine whether the frame size for the receiver describes a portrait orientation
 *
 *  @return Yes if the receiver's frame size is portrait; otherwise NO
 */
- (BOOL) isPortrait;

/*!
 *  Determine whether the frame size for the receiver describes a landscape orientation
 *
 *  @return Yes if the receiver's frame size is landscape; otherwise NO
 */
- (BOOL) isLandscape;

/*!
 *  Copy the reciever's settings to the given WZMediaConfig
 *
 *  @param other The WZMediaConfig being copied to
 */
- (void) copyTo:(nonnull WZMediaConfig *)other;

@end
