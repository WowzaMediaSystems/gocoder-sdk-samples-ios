//
//  WOWZPlayer.h
//  WOWZPlayer
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

#import <UIKit/UIKit.h>
#import "WowzaConfig.h"
#import "WOWZDataEvent.h"
#import "WOWZDataSink.h"
#import "WOWZStatusCallback.h"


/*!
 @class WOWZPlayer
 @discussion Use the WOWZPlayer class to play streams from Wowza Streaming Engine or Wowza Streaming Cloud over the WOWZ protocol, as well as to play ultra low latency streams from Wowza Streaming Cloud. WOWZPlayer decompresses audio and video, plays audio through the device speaker, and displays video frames in a UIView.
 */
@interface WOWZPlayer : NSObject

/*!
 *  @typedef WOWZPlayerViewGravityResizeAspect
 *  @constant WOWZPlayerViewGravityResizeAspect Preserve the video's aspect ratio and fit it within layer bounds.
 *  @constant WOWZPlayerViewGravityResizeAspectFill Preserve the video's aspect ratio and fill layer bounds.
 *  @discussion Describes how the video is displayed in the player's available screen area.
 */
typedef NS_ENUM(NSUInteger, WOWZPlayerViewGravity) {
    WOWZPlayerViewGravityResizeAspect = 0,
    WOWZPlayerViewGravityResizeAspectFill
};

/*!
 *  The gravity to use to display the video in the host view. Gravity describes
 *  how the video frame fills the available screen area.
 */
@property (nonatomic, assign) WOWZPlayerViewGravity playerViewGravity;

/*!
 *  The UIView to which the player should be added.
 */
@property (nonatomic, weak) UIView * _Nullable playerView;

/*!
A Boolean value that determines whether WOWZPlayer handles UIApplicationDidEnterBackgroundNotification notifications. The default value is YES. If set to YES, WOWZPlayer handles the notification and in response automatically stops the playback stream. If set to NO, WOWZPlayer does not handle UIApplicationDidEnterBackgroundNotification notifications. This lets the developer control stoppage of the playback stream in another way. IMPORTANT: If the value is set to NO and the developer does not control stoppage of the playback stream in another way, the playing state is likely to enter an undesirable condition at some point.
*/
@property (nonatomic, assign) BOOL shouldHandleBackgroundNotificationAndStopPlayer;


/*!
 *  The volume to play the audio. Specify a value between 0.0 (silent) and 1.0 (full volume);
 *  any value outside of this range will be ignored. The default is 1.0.
 */
@property (nonatomic, assign) Float32 volume;

/*!
 *  The sync offset to scrub video to sync. Specify a value between -1.0 and 3.0 seconds;
 *  any value outside of this range will be ignored. The default is 1.0.
 */
@property (nonatomic, assign) Float32 syncOffset;


/*!
 *  Mute or unmute the audio. The default is no, or unmuted.
 */
@property (nonatomic, assign) BOOL muted;

/*!
 *  The amount of time to buffer the video before playing. The default is 0 seconds; the maximum is 60 seconds.
 */
@property (nonatomic, assign) Float64 prerollDuration;

/*!
 *  The stream metadata for the stream that's playing.
 */
@property (nonatomic, readonly, nullable) WOWZDataMap *metaData;




/*!
 *  The timecode of the most recent frame displayed by the player, relative to the starting timecode.
 *  Returns kCMTimeInvalid if a stream isn't playing or if the player hasn't received any frames.
 */
@property (nonatomic, readonly) CMTime currentTime;


/*!
 *  The incoming bitrate during playback this is a combination of time of play calculated against length of total buffers incoming.
 */
@property (nonatomic, readonly) Float32 currentInjestBitrate;


/*!
 *  Play an Apple HLS stream as a fallback if the primary WOWZ-based conection is unsuccessful.
 *  Can be used with ultra low latency streams from Wowza Streaming Cloud; note, however, that Apple HLS streams experience greater latency than WebSocket streams.
 */
@property (nonatomic, assign) BOOL useHLSFallback;

//HLS
/*!
 *  The hlsPlayerItem.
 */
@property (nonatomic, strong) AVPlayerItem * _Nullable hlsPlayerItem;

/*!
 *  The hls AVPlayer from Apple.
 */
@property (nonatomic, strong) AVPlayer * _Nullable hlsPlayer;

/*!
 *  The hls AVPlayerLayer from Apple.
 */
@property (nonatomic, strong) AVPlayerLayer * _Nullable hlsVideoPlayerLayer;

/*!
 *
 * Access to the client callback incase the order of deinit/dealloc needs to be manually controlled on the delegate callback.
 *
 */

@property (nonatomic, weak) NSObject<WOWZStatusCallback> * _Nullable clientCallback;

/*!
 *
 */
@property (nonatomic, assign) BOOL captureLastRenderedFrame;

/*!
 *  Get the current playing state of the WOWZPlayer instance. 
 */
-(WOWZState) currentPlayState;

/*!
 *  Starts playing the stream.
 *
 *  @param config The WowzaConfig that specifes the host, port, app name, and stream name to play.
 *  @param statusCallback The callback to be invoked with playback session status updates and errors.
 *
 */
-(void) play:(nonnull WowzaConfig *)config callback:(nullable id<WOWZStatusCallback>)statusCallback;

/*!
 * Sets the current playing state of the WOWZPlayer instance to WOWZStateStopping and then stops playing the stream. This method is locked using &#064;synchronized(self). After playback is stopped, the current playing state is WOWZStateStopping.
 */
-(void) stop;

/*!
 *
 */
-(void) updateViewLayouts;

/*!
 *  Sets up the HLS fallback stream.
 *  Can be used with ultra low latency streams from Wowza Streaming Cloud; note, however, that Apple HLS streams experience greater latency than WebSocket streams.
 */
-(void)setupHLSWithView:(UIView *_Nullable)viewToAttachTo;

/*!
 *  Starts playing the HLS fallback stream. Note that Apple's AVPlayer is used to play HLS fallback streams. To handle certain playback events, such as unexpected stoppages, use AVPlayer and custom notifications.
 */
-(void) startHLSPlayback;

/*!
 *  Stops playing the HLS fallback stream. Note that Apple's AVPlayer is used to play HLS fallback streams. To handle certain playback events, such as unexpected stoppages, use AVPlayer and custom notifications.
 */
-(void) stopHLSPlayback;

/*!
 *  Pauses the HLS fallback stream. Note that Apple's AVPlayer is used to play HLS fallback streams. To handle certain playback events, such as unexpected stoppages, use AVPlayer and custom notifications.
 */
-(void) pauseHLSPlayback;

/*!
 * Resets the playback error count to zero.
 */
-(void) resetPlaybackErrorCount;

/*!
 * Gets the current playback error count - used for HLS fallback (2 errors is default then fallback).
 */
-(NSUInteger) currentPlaybackErrorCount;

-(UIImage *_Nullable) getLastRenderedImage;

/*!
 * Sets in a range from 1 - 4 the number of seconds of latency that the audio buffer will allow until it dumps and resets on most recent incoming audio frames.  It is recommended to leave this at the defaul of 3 as having some flexible time for samplerate cross conversion is good or else you may hear glitches in audio when the buffer is flushed because of max headroom reached.
 */
-(void) updateMaxLatencyInSecondsForAudio:(UInt32)numberOfSeconds;

/*!
 *  Registers a WOWZDataSink object with WOWZPlayer.
 *  WOWZDataSink protocol methods are called when the player
 *  is active and a data event is received from the server.
 *
 *  @param sink An object that conforms to the WOWZAudioEncoderSink protocol.
 *  @param eventName The name of the data event that the client should listen for.
 */
-(void) registerDataSink:(nonnull id<WOWZDataSink>)sink eventName:(nonnull NSString *)eventName;

/*!
 *  Unregisters a WOWZDataSink object from WOWZPlayer.
 *
 *  @param sink An object that conforms to the WOWZDataSink protocol.
 */
-(void) unregisterDataSink:(nonnull id<WOWZDataSink>)sink eventName:(nonnull NSString *)eventName;

@end
