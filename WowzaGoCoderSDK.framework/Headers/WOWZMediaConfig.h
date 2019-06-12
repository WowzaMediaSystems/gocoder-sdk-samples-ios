//
//  WOWZMediaConfig.h
//  WowzaGoCoderSDK
//
//  © 2007 – 2019 Wowza Media Systems, LLC. All rights reserved.
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
 @class WOWZMediaConfig
 @discussion The WOWZMediaConfig class provides configuration properties for capturing and encoding audio and video.
 */
@interface WOWZMediaConfig : NSObject <NSMutableCopying, NSCopying, NSCoding>

/*!
 *  @typedef WOWZFrameSizePreset
 *  @constant WOWZFrameSizePreset352x288 352x288 pixels.
 *  @constant WOWZFrameSizePreset640x480 640x480 pixels.
 *  @constant WOWZFrameSizePreset1280x720 1280x720 pixels, or 720p.
 *  @constant WOWZFrameSizePreset1920x1080 1920x1080 pixels, or 1080p.
 *  @constant WOWZFrameSizePreset3840x2160 3840x2160 pixels, or UHD 4K.
 *  @constant WOWZFrameSizePresetCount Count of known frame sizes.
 *  @discussion Standard frame sizes for the broadcasted video. (Note that not all devices and cameras support all frame sizes.)
 */
typedef NS_ENUM(NSUInteger, WOWZFrameSizePreset) {
    WOWZFrameSizePreset352x288,
    WOWZFrameSizePreset640x480,
    WOWZFrameSizePreset1280x720,
    WOWZFrameSizePreset1920x1080,
    WOWZFrameSizePreset3840x2160,
    WOWZFrameSizePresetCount
};

/*!
 *  @typedef WOWZBroadcastOrientation
 *  @constant WOWZBroadcastOrientationSameAsDevice Use the orientation of the device when the broadcast starts.
 *  @constant WOWZBroadcastOrientationAlwaysLandscapeLeft Always broadcast in landscape left orientation (this maintains a left orientation for the person viewing the video on the device as the device is rotated).
 *  @constant WOWZBroadcastOrientationAlwaysPortrait Always broadcast in portrait orientation.
 *  @constant WOWZBroadcastOrientationAlwaysLandscapeRight Always broadcast in landscape right orientation.
 *  @constant WOWZBroadcastOrientationPortraitUpsideDown Always broadcast in portrait orientation and rotated 180 degrees.
 *  @discussion Orientation options for the broadcasted video.
 */
typedef NS_ENUM(NSUInteger, WOWZBroadcastOrientation) {
    WOWZBroadcastOrientationSameAsDevice,
    WOWZBroadcastOrientationAlwaysLandscapeLeft,
    WOWZBroadcastOrientationAlwaysPortrait,
    WOWZBroadcastOrientationAlwaysLandscapeRight,
    WOWZBroadcastOrientationAlwaysPortraitUpsideDown
};

/*!
 *  @typedef WOWZBroadcastScaleMode
 *  @constant WOWZBroadcastScaleModeAspectFit Scale captured frames down to fit within the broadcast frame.
 *  @constant WOWZBroadcastScaleModeAspectFill Scale captured frames up to fill the broadcast frame.
 *  @discussion Adjustments for captured frames that don't match the specified broadcast frame size.
 */
typedef NS_ENUM(NSUInteger, WOWZBroadcastScaleMode) {
    WOWZBroadcastScaleModeAspectFit,
    WOWZBroadcastScaleModeAspectFill
};

/*!
 *  @typedef WOWZAudioChannels
 *  @constant WOWZAudioChannelsMono Mono, or one channel.
 *  @constant WOWZAudioChannels Stereo, or two channels.
 *  @discussion The number of audio channels to use. (Note that not all devices support all audio-channel counts.)
 */
typedef NS_ENUM(NSUInteger, WOWZAudioChannels) {
    WOWZAudioChannelsMono     = 1,
    WOWZAudioChannelsStereo   = 2
};
    
/*!
 *  @typedef WOWZVideoRenderMethod
 *  @constant WOWZVideoRenderMethodAuto If the playback device supports Apple's Metal framework, render the playback
 *  video using the WOWZVideoRenderMethodMetal_sRGB method. Otherwise, render the playback video using the
 *  WOWZVideoRenderMethodOpenGL method. WOWZVideoRenderMethodAuto is the default.
 *  @constant WOWZVideoRenderMethodMetal If the playback device supports Apple's Metal framework, render the playback
 *  video using Apple's Metal framework. Otherwise, render the playback video using the WOWZVideoRenderMethodOpenGL method.
 *  Because using the Metal framework consumes less energy and GPU cycles, it's the preferred method for playing
 *  Ultra Low Latency streams. The WOWZVideoRenderMethodMetal method also uses the default Metal color space, which results
 *  in more saturated colors than either the WOWZVideoRenderMethodMetal_sRGB method or the WOWZVideoRenderMethodOpenGL method.
 *  @constant WOWZVideoRenderMethodMetal_sRGB If the playback device supports Apple's Metal framework, render the playback
 *  video using the Metal framework and assuming the video frames are in the sRGB color space. Otherwise, render the playback
 *  video using the WOWZVideoRenderMethodOpenGL method. Because using the Metal framework consumes less energy and GPU cycles,
 *  it's the preferred method for playing Ultra Low Latency streams. The WOWZVideoRenderMethodMetal_sRGB method is also
 *  more visually consistent with the colors rendered by the WOWZVideoRenderMethodOpenGL method, which results in less saturated
 *  colors than the WOWZVideoRenderMethodMetal method.
 *  @constant WOWZVideoRenderMethodOpenGL Use OpenGL APIs to render the playback video.
 *  @discussion Video rendering methods available for drawing video frames for GoCoder SDK-based playback.
 */
typedef NS_ENUM(NSUInteger, WOWZVideoRenderMethod) {
    WOWZVideoRenderMethodAuto       = 1,
    WOWZVideoRenderMethodMetal      = 2,
    WOWZVideoRenderMethodMetal_sRGB = 3,
    WOWZVideoRenderMethodOpenGL     = 4
};


#pragma mark - Public Class Methods -

/*!
 *  Converts a WOWZFrameSizePreset to an AVFoundation AVCaptureSessionPreset string.
 *
 *  @param wzPreset The WOWZFrameSizePreset to convert.
 *
 *  @return The AVFoundation AVCaptureSessionPreset string that corresponds to the specified WOWZFrameSizePreset.
 */
+ (nullable NSString *) AVCaptureSessionPresetFromPreset:(WOWZFrameSizePreset)wzPreset;

/*!
 *  Converts a WOWZFrameSizePreset to a corresponding CGSize.
 *
 *  @param preset The WOWZFrameSizePreset to convert.
 *
 *  @return The CGSize that corresponds to the specified WOWZFrameSizePreset.
 */
+ (CGSize) CGSizeFromPreset:(WOWZFrameSizePreset)preset;

/*!
 *  Returns the AVFoundation AVCaptureSessionPreset string that most closely matches the specified width.
 *
 *  @param width The width of the video capture.
 *
 *  @return The AVFoundation AVCaptureSessionPreset string that most closely matches the specified width.
 */
+ (nullable NSString *) closestAVCaptureSessionPresetByWidth:(NSUInteger)width;

#pragma mark -

/*!
 *  Returns an array of NSNumber values for each WOWZFrameSizePreset.
 *
 *  @return The array of NSNumber values.
 */
+ (nonnull NSArray *) presets;

/*!
 *  Returns an array of WOWZMediaConfig objects for each WOWZFrameSizePreset.
 *
 *  @return The array of WOWZMediaConfig objects.
 */
+ (nonnull NSArray *) presetConfigs;


#pragma mark - Properties -

/*!
 *  Allow video for the configuration. If true, enables video for the broadcast or playback configuration; if false, disables video and video channels in the stream aren't decoded.
 */
@property (nonatomic, assign) BOOL videoEnabled;

/*!
 *  Allow audio for the configuration. If true, enables audio for the broadcast or playback configuration; if false, disables audio and audio channels in the stream aren't decoded.
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
 *  The frame rate for the configuration. Note that the actual frame rate might be reduced if network bandwidth is insufficient for the specified frame rate.
 */
@property (nonatomic, assign) NSUInteger videoFrameRate;

/*!
 *  The keyframe interval.
 */
@property (nonatomic, assign) NSUInteger videoKeyFrameInterval;

/*!
 *  The video bitrate to use. Note that the actual bitrate might be reduced if network bandwidth is insufficient for the specified bitrate.
 */
@property (nonatomic, assign) NSUInteger videoBitrate;

/*!
 *  The factor by which to scale the bitrate in low-bandwidth conditions.
 *  Valid values are 0.0 to 1.0; all other values are ignored.
 *  Specifying 0.0 instructs the encoder to choose the best value; specifying 1.0 tells it to never throttle the bitrate.
 *  The default is 0.75.
 */
@property (nonatomic, assign) Float32 videoBitrateLowBandwidthScalingFactor;

/*!
 *  The value by which to multiply the frame rate to determine the number of
 *  frames to buffer before the encoder starts to throttle bitrate and/or frame rate.
 *  For example, if the frame rate is 30 and the videoFrameBufferSizeMultiplier is 5,
 *  the encoder will buffer 150 (5 x 30) frames before throttling.
 *  Specifying 0 instructs the encoder to choose the best value.
 *  The default is 4.
 */
@property (nonatomic, assign) NSUInteger videoFrameBufferSizeMultiplier;

/*!
 *  The number of frames to skip when the encoder can't keep up with the broadcaster.
 *  In poor networks conditions the encoder will continue to send frames to the broadcaster but will skip frames to conserve bandwidth.
 *  The maximum number of frames that can be skipped equals the keyframe interval minus one.
 *  For example, setting the skip count to 29 with a keyframe interval of 30 will produce a keyframe-only stream;
 *  setting to 1 will never skip frames. The default is 2, which skips every other frame.
 */
@property (nonatomic, assign) NSUInteger videoFrameRateLowBandwidthSkipCount;
    
/*!
 *  The video rendering method to use when drawing video frames. See WOWZVideoRenderMethod for supported values.
 *  The default is WOWZVideoRenderMethodAuto.
 */
@property (nonatomic, assign) WOWZVideoRenderMethod videoRenderingMethod;

#pragma mark -

/*!
 *  Set the video to rotate to match the orientation of the device.
 */
@property (nonatomic, assign) BOOL capturedVideoRotates;

/*!
 *  Set the preview video session to rotate to match the orientation of the device.
 */
@property (nonatomic, assign) BOOL videoPreviewRotates;


/*!
 *  Set the broadcast orientation for a broadcast session.
 *  See WOWZBroadcastOrientation for supported values. The default is WOWZBroadcastOrientationSameAsDevice.
 */
@property (nonatomic, assign) WOWZBroadcastOrientation broadcastVideoOrientation;


/*!
 *  Set the scale mode for captured frames that don't fit the specified broadcast frame size. 
 *  See WOWZBroadcastScaleMode for supported values. The default is WOWZBroadcastScaleModeAspectFit.
 */
@property (nonatomic, assign) WOWZBroadcastScaleMode broadcastScaleMode;

/*!
 *  Set the front-facing camera to mirror captured video. The default is yes.
 */
@property (nonatomic, assign) BOOL mirrorFrontCamera;

/*!
 *  Allow fallback to Apple HLS if the primary WOWZ connection is unsuccessful. The default is no.
 *  Can be used with ultra low latency streams from Wowza Streaming Cloud; note, however, that Apple HLS streams experience greater latency than WebSocket streams.
 */
@property (nonatomic, assign) BOOL allowHLSPlayback;

/*!
 *  The Apple HLS playback URL to use to play the stream as a fallback if the primary WOWZ connection is unsuccessful.
 *  Can be used with ultra low latency streams from Wowza Streaming Cloud; note, however, that Apple HLS streams experience greater latency than WebSocket streams.
 */
    @property (nonatomic, assign) NSString * _Nullable hlsURL;

#pragma mark -

/*!
 *  Enable broadcasting when the app is in the background. If enabled, the host
 *  application must support the audio background mode (this is set in your app target's Capabilities tab,
 *  in the Background Modes section). When enabled, the app will continue to record
 *  and broadcast the live audio stream. Since the camera can't capture in the background on iOS, however, a
 *  blank or frozen video frame will appear while the app is in the background.
 *  The default is no.
 */
@property (nonatomic, assign) BOOL backgroundBroadcastEnabled;

#pragma mark -

/*!
 *  The number of audio channels.
 */
@property (nonatomic, assign) NSUInteger audioChannels;


/*!
 *  The audio sample rate. (Note that the actual sample rate
 *  may differ from the specified rate.) Specify 0
 *  to have WowzaGoCoder select the optimal sample rate based on the
 *  current hardware capabilities. The default is 0.
 */
@property (nonatomic, assign) NSUInteger audioSampleRate;

/*!
 *  The audio bitrate. (Note that the actual bitrate
 *  may differ from the specified rate.) Specify 0
 *  to have WowzaGoCoder select the optimal bitrate based on the
 *  current hardware capabilities. The default is 0.
 */
@property (nonatomic, assign) NSUInteger audioBitrate;

#pragma mark -

/*!
 *  The video frame size, in CGSize format.
 */
@property (nonatomic, readonly) CGSize frameSize;

/*!
 *  A human-readable string that describes the video frame size.
 */
@property (nonatomic, readonly, nonnull) NSString *frameSizeLabel;

#pragma mark - Public Instance Methods -

/*!
 *  Initializes a new WOWZMediaConfig with a specified frame-size and bitrate preset.
 *
 *  @param preset The frame-size preset.
 *
 *  @return An instance of WOWZMediaConfig with the specified frame size and recommended bitrate for that frame size.
 */
- (nonnull instancetype) initWithPreset:(WOWZFrameSizePreset)preset;

/*!
 *  Sets the frame size and recommended bitrate of the receiver to the specified a WOWZFrameSizePreset.
 *
 *  @param preset The preset to use.
 */
- (void) loadPreset:(WOWZFrameSizePreset)preset;

/*!
 *  Gets the receiver's corresponding AVFoundation AVCaptureSessionPreset string.
 *
 *  @return The corresponding AVFoundation AVCaptureSessionPreset string for this config.
 */
- (nullable NSString *) toAVCaptureSessionPreset;

/*!
 *  Gets the receiver's closest corresponding AVFoundation AVCaptureSessionPreset string.
 *
 *  @return The closest corresponding AVFoundation AVCaptureSessionPreset string.
 */
- (nonnull NSString *) toClosestAVCaptureSessionPreset;

#pragma mark -

/*!
 *  Gets the receiver's corresponding WOWZFrameSizePreset.
 *
 *  @return The corresponding WOWZFrameSizePreset.
 */
- (WOWZFrameSizePreset) toPreset;

/*!
 *  Gets the receiver's closest corresponding WOWZFrameSizePreset.
 *
 *  @return The closest corresponding WOWZFrameSizePreset.
 */
- (WOWZFrameSizePreset) toClosestPreset;

#pragma mark -

/*!
 *  Tests the receiver for equality to the specified WOWZMediaConfig.
 *
 *  @param other The WOWZMediaConfig to test.
 *
 *  @return Yes if the receiver and specified config are equal; no otherwise.
 */
- (BOOL) equals:(nonnull WOWZMediaConfig *)other;

/*!
 *  Determines whether the receiver's frame orientation is portrait.
 *
 *  @return Yes if the receiver's frame orientation is portrait; no otherwise.
 */
- (BOOL) isPortrait;

/*!
 *  Determines whether the receiver's frame orientation is landscape.
 *
 *  @return Yes if the receiver's frame size is landscape; no otherwise.
 */
- (BOOL) isLandscape;

/*!
 *  Copies the receiver's settings to the specified WOWZMediaConfig.
 *
 *  @param other The WOWZMediaConfig being copied to.
 */
- (void) copyTo:(nonnull WOWZMediaConfig *)other;

@end
