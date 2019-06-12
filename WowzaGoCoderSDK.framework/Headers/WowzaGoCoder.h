//
//  WowzaGoCoder.h
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

#import <UIKit/UIKit.h>
#import "WowzaConfig.h"
#import "WOWZStatusCallback.h"
#import "WOWZVideoSink.h"
#import "WOWZAudioSink.h"
#import "WOWZVideoEncoderSink.h"
#import "WOWZAudioEncoderSink.h"
#import "WOWZDataEvent.h"
#import "WOWZDataSink.h"

@class WOWZCameraPreview;

/*!
 *  @class WowzaGoCoder
 *  @discussion The WowzaGoCoder class is the primary API interface for the GoCoder SDK. It provides methods for configuring and controlling devices and streaming live video.
 */
@interface WowzaGoCoder : NSObject <WOWZStatusCallback>



/*!
 *  @typedef WowzaGoCoderCapturePermission
 *  @constant WowzaGoCoderCapturePermissionAuthorized Access to a particular capture device has been authorized by the user.
 *  @constant WowzaGoCoderCapturePermissionDenied Access to a particular capture device has been denied by the user.
 *  @constant WowzaGoCoderCapturePermissionNotDetermined Access to a particular capture device has yet to be determined.
 *  @discussion Permissions for either an audio- or video-capture device.
 */
typedef NS_ENUM(NSUInteger, WowzaGoCoderCapturePermission) {
    WowzaGoCoderCapturePermissionAuthorized,
    WowzaGoCoderCapturePermissionDenied,
    WowzaGoCoderCapturePermissionNotDetermined
};

/*!
 *  @typedef WowzaGoCoderPermissionType
 *  @constant WowzaGoCoderPermissionTypeCamera The device camera permission type.
 *  @constant WowzaGoCoderPermissionTypeMicrophone The device microphone permission type.
 *  @discussion The permission types that are available in the SDK.
 */
typedef NS_ENUM(NSUInteger, WowzaGoCoderPermissionType) {
    WowzaGoCoderPermissionTypeCamera,
    WowzaGoCoderPermissionTypeMicrophone
};

/*!
 *  @typedef WOWZPermissionBlock A callback block that's used with requestCameraPermission and requestMicrophonePermission.
 */
typedef void (^WOWZPermissionBlock)(WowzaGoCoderCapturePermission permission);



// Class methods
/*!
 *  Registers and validates the GoCoder SDK license key.
 *
 *  @param licenseKey The license key.
 *
 *  @return Nil if no error, or an NSError that describes the license validation error.
 */
+ (nullable NSError *) registerLicenseKey:(nonnull NSString *)licenseKey;

/*!
 *  Requests explicit permission to use the device's camera or microphone.
 *
 *  @param type The WowzaGoCoderPermissionType for which permission is being requested.
 *  @param response The WOWZPermissionBlock to be executed after the user responds to the
 *  the device-access request.
 */
+ (void) requestPermissionForType:(WowzaGoCoderPermissionType)type response:(nullable WOWZPermissionBlock)response;

/*!
 *  Gets the permission status for the specified WowzaGoCoderPermissionType.
 *
 *  @param type The WowzaGoCoderPermissionType to query.
 */
+ (WowzaGoCoderCapturePermission) permissionForType:(WowzaGoCoderPermissionType)type;


/*!
 Gets the WowzaGoCoder shared instance.
 @result
    An instance of the top-level GoCoder SDK API interface, or nil if licensing failed.
 */
+ (nullable instancetype) sharedInstance;

// Properties

/*!
 *  The audio, video, and stream configuration settings.
 */
@property (nonatomic, nonnull, copy) WowzaConfig *config;


/*!
 *  The view to use for the camera preview.
 */
@property (nonatomic, nullable) UIView *cameraView;

/*!
 *  The WOWZCameraPreview object created when the cameraView is set.
 */
@property (nonatomic, nullable, readonly) WOWZCameraPreview *cameraPreview;


/*!
 @property status
 @discussion The status of the current live streaming session.
 */
@property (nonatomic, nonnull, readonly) WOWZStatus *status;



/*!
 *  The muted state of the audio encoder.
 */
@property (nonatomic, assign, getter=isAudioMuted) BOOL audioMuted;

/*!
 *  The AVAudioSessionCategoryOptions to use when streaming with audio. The default is AVAudioSessionCategoryOptionAllowBluetooth.
 *  This property must be set before starting a preview session.
 */
@property (nonatomic, assign) AVAudioSessionCategoryOptions audioSessionOptions;

/*!
 *  True if a live stream is broadcasting; false otherwise.
 */
@property (nonatomic, readonly) BOOL isStreaming;

/*!
 *  The stream metadata for the broadcasted stream.
 */
@property (nonatomic, readonly, nullable) WOWZDataMap *metaData;

// Instance methods
+ (nonnull instancetype) alloc __attribute__((unavailable("alloc not available, call the sharedInstance class method instead")));
- (nonnull instancetype) init __attribute__((unavailable("init not available, call the sharedInstance class method instead")));
+ (nonnull instancetype) new __attribute__((unavailable("new not available, call the sharedInstance class method instead")));
- (nonnull instancetype) copy __attribute__((unavailable("copy not available, call the sharedInstance class method instead")));



/*!
 *  Starts a live streaming session with a specified status callback.
 *
 *  @param statusCallback The callback to be invoked with streaming session status updates and errors.
 */
- (void) startStreaming:(nullable id<WOWZStatusCallback>)statusCallback;

/*!
 *  Starts a live streaming session with a specified status callback and configuration settings.
 *
 *  @param statusCallback The callback to be invoked with streaming session status updates and errors.
 *  @param aConfig The configuration settings for the live streaming session.
 */
- (void) startStreamingWithConfig:(nullable id<WOWZStatusCallback>)statusCallback config:(nonnull WowzaConfig *)aConfig;

/*!
 *  Starts a live streaming session with a specified status callback and WOWZFrameSizePreset preset.
 *
 *  @param statusCallback The callback to be invoked with streaming session status updates and errors.
 *  @param aPreset The WOWZFrameSizePreset for the live streaming session.
 */
- (void) startStreamingWithPreset:(nullable id<WOWZStatusCallback>)statusCallback preset:(WOWZFrameSizePreset)aPreset;

/*!
 *  Ends the active streaming session.
 *
 *  @param statusCallback The callback to be invoked with streaming session status updates and errors.
 */
- (void) endStreaming:(nullable id<WOWZStatusCallback>)statusCallback;

/*!
 *  Sends user-defined metadata with the current broadcast stream.
 *
 *  @param scope A WOWZDataScope defining the scope of the event to be sent.
 *  @param eventName The name of the event to be sent.
 *  @param params The parameters for the event to be sent.
 *  @param callback The callback to be invoked with the result of a WOWZDataScopeModule call. Should be nil for WOWZDataScopeStream.
 *
 */
- (void) sendDataEvent:(WOWZDataScope)scope eventName:(nonnull NSString *)eventName params:(nonnull WOWZDataMap *)params callback:(nullable WOWZDataCallback)callback;

/*!
 *  Sends a ping request to the server and returns the result of the specified callback.
 *
 *  @param callback The callback to be invoked with the result of the request.
 *  For example, the responseTime property of the result parameters passed to the callback contains the response time, in milliseconds.
 * */
- (void) sendPingRequest:(nonnull WOWZDataCallback)callback;

/*!
 *  Updates the broadcast to use a lower-bitrate encoding during limited network conditions.
 *
 *  @param bitrate The bitrate the broadcast should use in limited bandwidth conditions.
 * */
- (void) updateEncoderLimitedBitrate:(NSInteger)bitrate;

/*!
 *  Updates the broadcast to use the target bitrate encoding during normal network conditions.
 *
 *  @param bitrate The bitrate the broadcast should use under normal network conditions.
 * */
- (void) updateEncoderTargetBitrate:(NSInteger)bitrate;

/*!
 *  The current broadcasting actual bitrate across the socket.
 * This value is also available for listening to with NSNotifcationCenter.
 * notification name:WOWZBroadcastBitrateNetworkThroughputUpdate
 * , note.userInfo key: broadcastThroughputBitrate, value is Float64
 * */
- (Float64) getCurrentBroadcastingNetworkBitrateThroughput;

#pragma mark -

/*!
 *  Registers a WOWZVideoSink object with WowzaGoCoder.
 *  WOWZVideoSink protocol methods are called when video is being encoded.
 *
 *  @param sink An object that conforms to the WOWZVideoSink protocol.
 */
- (void) registerVideoSink:(nonnull id<WOWZVideoSink>)sink;

/*!
 *  Unregisters a WOWZVideoSink object from WowzaGoCoder.
 *
 *  @param sink An object that conforms to the WOWZVideoSink protocol.
 */
- (void) unregisterVideoSink:(nonnull id<WOWZVideoSink>)sink;

/*!
 *  Registers a WOWZAudioSink object with WowzaGoCoder.
 *  WOWZAudioSink protocol methods are called when audio is being captured and/or encoded.
 *
 *  @param sink An object that conforms to the WOWZAudioSink protocol.
 */
- (void) registerAudioSink:(nonnull id<WOWZAudioSink>)sink;

/*!
 *  Unregisters a WOWZAudioSink object from WowzaGoCoder.
 *
 *  @param sink An object that conforms to the WOWZAudioSink protocol.
 */
- (void) unregisterAudioSink:(nonnull id<WOWZAudioSink>)sink;

/*!
 *  Registers a WOWZVideoEncoderSink object with WowzaGoCoder.
 *  WOWZVideoEncoderSink protocol methods are called when video is actively encoding.
 *
 *  @param sink An object that conforms to the WOWZVideoEncoderSink protocol.
 */
- (void) registerVideoEncoderSink:(nonnull id<WOWZVideoEncoderSink>)sink;

/*!
 *  Unregisters a WOWZVideoEncoderSink object from WowzaGoCoder.
 *
 *  @param sink An object that conforms to the WOWZVideoEncoderSink protocol.
 */
- (void) unregisterVideoEncoderSink:(nonnull id<WOWZVideoEncoderSink>)sink;

/*!
 *  Registers a WOWZAudioEncoderSink object with WowzaGoCoder.
 *  WOWZAudioEncoderSink protocol methods are called when audio is being captured and/or encoded.
 *
 *  @param sink An object that conforms to the WOWZAudioEncoderSink protocol.
 */
- (void) registerAudioEncoderSink:(nonnull id<WOWZAudioEncoderSink>)sink;

/*!
 *  Unregisters a WOWZAudioEncoderSink object from WowzaGoCoder.
 *
 *  @param sink An object that conforms to the WOWZAudioEncoderSink protocol.
 */
- (void) unregisterAudioEncoderSink:(nonnull id<WOWZAudioEncoderSink>)sink;

/*!
 *  Registers a WOWZDataSink object with WowzaGoCoder.
 *  WOWZDataSink protocol methods are called when video is being encoded and a data event is received from the server.
 *
 *  @param sink An object that conforms to the WOWZAudioEncoderSink protocol.
 *  @param eventName The name of the data event the client should listen for.
 */
- (void) registerDataSink:(nonnull id<WOWZDataSink>)sink eventName:(nonnull NSString *)eventName;

/*!
 *  Unregisters a WOWZDataSink object from WowzaGoCoder.
 *
 *  @param sink An object that conforms to the WOWZDataSink protocol.
 */
- (void) unregisterDataSink:(nonnull id<WOWZDataSink>)sink eventName:(nonnull NSString *)eventName;



/*!
 *  @typedef WowzaGoCoderLogLevel
 *  @constant WowzaGoCoderLogLevelError Generate only error logging.
 *  @constant WowzaGoCoderLogLevelDefault Generate minimal log statements from the SDK.
 *  @constant WowzaGoCoderLogLevelVerbose Generate detailed log statements from the SDK.
 *  @constant WowzaGoCoderLogLevelOff Disable logging.
 *  @discussion Settings for the log level for the GoCoder SDK.
 */
typedef NS_ENUM(NSUInteger,WowzaGoCoderLogLevel) {
    WowzaGoCoderLogLevelOff = 0,
    WowzaGoCoderLogLevelError = 1,
    WowzaGoCoderLogLevelDefault = 1,
    WowzaGoCoderLogLevelVerbose = 2,
};

/*!
*  Sets the SDK log level.
*
*  @param level The log level to use.
*/
+ (void) setLogLevel:(WowzaGoCoderLogLevel)level;


/*!
 *  Deprecated
 *
 *  No longer used.
 *
 *  @typedef WowzaGoCoderNetworkLogLevel
 *  @constant WowzaGoCoderNetworkLogLevelVerbose Output all log messages.
 *  @constant WowzaGoCoderNetworkLogLevelDebug Log debug, informational, warning, and error messsges.
 *  @constant WowzaGoCoderNetworkLogLevelInfo Log informational, warning, and error messsges.
 *  @constant WowzaGoCoderNetworkLogLevelWarn Log warning and error messages.
 *  @constant WowzaGoCoderNetworkLogLevelError Log error messages.
 *  @discussion Settings for the network log level for the GoCoder SDK.
 */
typedef NS_ENUM(NSUInteger,WowzaGoCoderNetworkLogLevel) {
    WowzaGoCoderNetworkLogLevelVerbose  = 1,
    WowzaGoCoderNetworkLogLevelDebug    = 2,
    WowzaGoCoderNetworkLogLevelInfo     = 3,
    WowzaGoCoderNetworkLogLevelWarn     = 4,
    WowzaGoCoderNetworkLogLevelError    = 5
} __deprecated_msg("use WowzaGoCoderLogLevel instead");


/*!
 *  Deprecated
 *
 *  No longer used.
 *
 *  Sets the SDK network layer log level.
 *
 *  @param level The network layer log level to use.
 */
+ (void) setNetworkLogLevel:(WowzaGoCoderNetworkLogLevel)level;


@end
