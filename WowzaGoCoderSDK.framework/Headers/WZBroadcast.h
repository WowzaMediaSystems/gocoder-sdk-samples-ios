//
//  WZBroadcast.h
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

#import <Foundation/Foundation.h>
#import "WZStatusCallback.h"
#import "WZStreamConfig.h"
#import "WZBroadcastComponent.h"
#import "WZDataEvent.h"
#import "WZDataSink.h"

/*!
 @class WZBroadcast
 @discussion The WZBroadcast class is used to configure and control a live streaming broadcast. Under normal circumstances, you do not need to access this class directly unless you are extending the GoCoder SDK.
 

 */
@interface WZBroadcast : NSObject

#pragma mark - Properties

/*!
 *  The status of the broadcast
 */
@property (nonatomic, readonly, nonnull) WZStatus *status;

/*!
 *  A callback that will be invoked with streaming session status updates and errors.
 */
@property (nonatomic, unsafe_unretained, nullable) id<WZStatusCallback> statusCallback;

/*!
 *  An object that adopts the WZBroadcastComponent protocol that will be
 *  used as the video encoder for this broadcast session.
 */
@property (nonatomic, strong, nullable) id<WZBroadcastComponent> videoEncoder;

/*!
 *  An object that adopts the WZBroadcastComponent protocol that will be
 *  used as the audio encoder for this broadcast session.
 */
@property (nonatomic, strong, nullable) id<WZBroadcastComponent> audioEncoder;

/*!
 *  An object that adopts the WZBroadcastComponent protocol that will be
 *  used as the audio capture device for this broadcast session.
 */
@property (nonatomic, strong, nullable) id<WZBroadcastComponent> audioDevice;

/*!
 *  The stream metadata for the broadcasted stream
 */
@property (nonatomic, readonly, nullable) WZDataMap *metaData;

#pragma mark - Instance Methods

/*!
 *  Start a live streaming broadcast using the specified configuration
 *
 *  @param config A WZStreamConfig describing the broadcast settings
 *  @param statusCallback A callback that will be invoked with streaming session status updates and errors.
 *
 *  @return A WZStatus object
 */
- (nonnull WZStatus *) startBroadcast:(nonnull WZStreamConfig *)config statusCallback:(nullable id<WZStatusCallback>)statusCallback;

/*!
 *  Stop the active live streaming broadcast
 *
 *  @param statusCallback A callback that will be invoked with streaming session status updates and errors.
 *
 *  @return A WZStatus object
 */
- (nonnull WZStatus *) endBroadcast:(nullable id<WZStatusCallback>)statusCallback;

/*!
 *  Send user-defined metadata within the current broadcast stream.
 *
 *  @param scope A WZDataScope defining the scope of the event to be sent.
 *  @param eventName The name of the event to be sent.
 *  @param params The parameters for the event to be sent.
 *  @param callback The callback to be called with the result of a WZDataScopeModule call.
 *  Should be nil for WZDataScopeStream.
 *
 */
- (void) sendDataEvent:(WZDataScope)scope eventName:(nonnull NSString *)eventName params:(nonnull WZDataMap *)params callback:(nullable WZDataCallback)callback;

/*!
 *  Registers an object that conforms to the WZDataSink protocol.
 *  The WZDataSink protocol methods will be called when video encoding
 *  is active and a data event is received from the server.
 *
 *  @param sink An object conforming to the WZAudioEncoderSink protocol
 *  @param eventName The name of the data event the client wishes to listen for
 */
- (void) registerDataSink:(nonnull id<WZDataSink>)sink eventName:(nonnull NSString *)eventName;

/*!
 *  Unregisters an object that conforms to the WZDataSink protocol.
 *
 *  @param sink An object conforming to the WZDataSink protocol
 */
- (void) unregisterDataSink:(nonnull id<WZDataSink>)sink eventName:(nonnull NSString *)eventName;

@end
