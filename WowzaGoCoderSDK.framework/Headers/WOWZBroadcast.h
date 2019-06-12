//
//  WOWZBroadcast.h
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

#import <Foundation/Foundation.h>
#import "WOWZStatusCallback.h"
#import "WOWZStreamConfig.h"
#import "WOWZBroadcastComponent.h"
#import "WOWZDataEvent.h"
#import "WOWZDataSink.h"

/*!
 @class WOWZBroadcast
 @discussion Use the WOWZBroadcast class to configure and control live streaming broadcasts. Typically you only need to directly access this class when you're extending the GoCoder SDK.
 

 */
@interface WOWZBroadcast : NSObject

#pragma mark - Properties

/*!
 *  The status of the broadcast.
 */
@property (nonatomic, readonly, nonnull) WOWZStatus *status;

/*!
 *  The callback to be invoked with streaming session status updates and errors.
 */
@property (nonatomic, weak, nullable) id<WOWZStatusCallback> statusCallback;

/*!
 *  The WOWZBroadcastComponent object to use as the video encoder for the broadcast session.
 */
@property (nonatomic, strong, nullable) id<WOWZBroadcastComponent> videoEncoder;

/*!
 *  The WOWZBroadcastComponent object to use as the audio encoder for the broadcast session.
 */
@property (nonatomic, strong, nullable) id<WOWZBroadcastComponent> audioEncoder;

/*!
 *  The WOWZBroadcastComponent object to use as the audio-capture device for the broadcast session.
 */
@property (nonatomic, strong, nullable) id<WOWZBroadcastComponent> audioDevice;

/*!
 *  The stream metadata for the broadcasted stream.
 */
@property (nonatomic, readonly, nullable) WOWZDataMap *metaData;

#pragma mark - Instance Methods

/*!
 *  Starts a live streaming broadcast using the specified configuration.
 *
 *  @param config A WOWZStreamConfig that describes the broadcast settings.
 *  @param statusCallback The callback to be invoked with streaming session status updates and errors.
 *
 *  @return A WOWZStatus object.
 */
- (nonnull WOWZStatus *) startBroadcast:(nonnull WOWZStreamConfig *)config statusCallback:(nullable id<WOWZStatusCallback>)statusCallback;

/*!
 *  Ends the active live streaming broadcast.
 *
 *  @param statusCallback The callback to be invoked with streaming session status updates and errors.
 *
 *  @return A WOWZStatus object.
 */
- (nonnull WOWZStatus *) endBroadcast:(nullable id<WOWZStatusCallback>)statusCallback;

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
 *  Registers a WOWZDataSink object.
 *  WOWZDataSink protocol methods are called when video is being encoded and a data event is received from the server.
 *
 *  @param sink An object that conforms to the WOWZAudioEncoderSink protocol.
 *  @param eventName The name of the data event the client should listen for.
 */
- (void) registerDataSink:(nonnull id<WOWZDataSink>)sink eventName:(nonnull NSString *)eventName;

/*!
 *  Unregisters a WOWZDataSink object.
 *
 *  @param sink An object that conforms to the WOWZDataSink protocol.
 */
- (void) unregisterDataSink:(nonnull id<WOWZDataSink>)sink eventName:(nonnull NSString *)eventName;

/*!
 *  Sends a ping request to the server and returns the result of the specified callback.
 *
 *  @param statusCallback The callback to be invoked with the result of the request.
 *  For example, the responseTime property of the result parameters passed to the callback contains the response time, in milliseconds.
 * */
- (void) sendPingRequest:(nullable id<WOWZStatusCallback>)statusCallback;

@end
