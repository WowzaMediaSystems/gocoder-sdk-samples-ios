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
 *  @param event A WZDataEvent object containing the event data and the event name.
 *
 *  @return A WZStatus object
 */
- (nonnull WZStatus *) sendDataEvent:(nonnull WZDataEvent *)event;

@end
