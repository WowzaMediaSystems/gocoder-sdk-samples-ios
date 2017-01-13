//
//  WZPlayer.h
//  WZPlayer
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

#import <UIKit/UIKit.h>
#import "WowzaConfig.h"
#import "WZDataEvent.h"
#import "WZDataSink.h"
#import "WZStatusCallback.h"


/*!
 @class WZPlayer
 @discussion WZPlayer is a class used for playing a WOWZ stream from Engine or Cloud. WZPlayer handles decompressing audio and video, playing audio through the device speaker and displaying video frames in a UIView.
 */
@interface WZPlayer : NSObject

/*!
 *  @typedef WZPlayerViewGravityResizeAspect
 *  @constant WZPlayerViewGravityResizeAspect Preserve aspect ratio; fit within layer bounds.
 *  @constant WZPlayerViewGravityResizeAspectFill Preserve aspect ratio; fill layer bounds.
 *  @constant WZPlayerViewGravityResize Stretch to fill layer bounds.
 *  @discussion Describes how the video in the player view should fill the view frame.
 */
typedef NS_ENUM(NSUInteger, WZPlayerViewGravity) {
    WZPlayerViewGravityResizeAspect = 0,
    WZPlayerViewGravityResizeAspectFill,
    WZPlayerViewGravityResize
};

/*!
 *  The gravity to use for displaying the video in the host view; describes
 *  how the prview will fill the given view bounds
 */
@property (nonatomic, assign) WZPlayerViewGravity playerViewGravity;

/*!
 *  The UIView to which the video player will be added.
 */
@property (nonatomic, unsafe_unretained, nonnull) UIView *playerView;

/*!
 *  The current play state of the WZPlayer instance.
 */
@property (nonatomic, assign, readonly) BOOL playing;

/*!
 *  The volume at which to play the audio. Allowed values are 0.0 (silent) to 1.0 (full volume).
 *  Any value outside this range is ignored. Default is 1.0.
 */
@property (nonatomic, assign) Float32 volume;

/*!
 *  Mute/unmute audio. Default is NO.
 */
@property (nonatomic, assign) BOOL muted;

/*!
 *  The amount of time to pre-roll (buffer) the video before playing. The default is 0.
 *  readonly for now since this feature is not ready to demo.
 */
@property (nonatomic, assign) Float64 prerollDuration;

/*!
 *  Whether to attempt to sync audio and video by adjusting the video framerate.
 *  Default value is NO. Setting this to YES may cause the video to appear accelerated or
 *  slow depending on where and when compensation is needed.
 */
@property (nonatomic, assign) BOOL avSyncUsesFrameRateAdjustment;

/*!
 *  The stream metadata for an actively playing stream
 */
@property (nonatomic, readonly, nullable) WZDataMap *metaData;


/*!
 *  The timecode of the most recent frame displayed by the player, relative to the starting timecode.
    Returns kCMTimeInvalid if the player is not currently playing, or if no frames have yet been received.
 */
@property (nonatomic, readonly) CMTime currentTime;

/*!
 *  Start playing the video stream.
 *
 *  @param config The WowzaConfig specifying the host, port, app name and stream name to play
 *  @param statusCallback A callback that will be invoked with playback session status updates and errors.
 *
 */
- (void) play:(nonnull WowzaConfig *)config callback:(nullable id<WZStatusCallback>)statusCallback;

/*!
 *  Stop playing the video stream
 */
- (void) stop;


/*!
 *  Registers an object that conforms to the WZDataSink protocol with WZPlayer.
 *  The WZDataSink protocol methods will be called when video player
 *  is active and a data event is received from the server.
 *
 *  @param sink An object conforming to the WZAudioEncoderSink protocol
 *  @param eventName The name of the data event the client wishes to listen for
 */
- (void) registerDataSink:(nonnull id<WZDataSink>)sink eventName:(nonnull NSString *)eventName;

/*!
 *  Unregisters an object that conforms to the WZDataSink protocol with WZPlayer.
 *
 *  @param sink An object conforming to the WZDataSink protocol
 */
- (void) unregisterDataSink:(nonnull id<WZDataSink>)sink eventName:(nonnull NSString *)eventName;

@end
