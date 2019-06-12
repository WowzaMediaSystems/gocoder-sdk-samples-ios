//
//  WOWZBroadcastComponent.h
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

#import "WOWZStatus.h"
#import "WOWZStreamConfig.h"
#import "WOWZMediaSink.h"

/*!
 @protocol WOWZBroadcastComponent
 @discussion The WOWZBroadcastComponent interface defines the methods that are implemented by classes developed as broadcast components with instances registered with the WZBroadcast class.
 */
@protocol WOWZBroadcastComponent <NSObject>

@required

/*!
 *  Gets the status of the broadcast component.
 *
 *  @return A WOWZStatus object.
 */
- (nonnull WOWZStatus *) getStatus;

/**
 *  Initializes each component of a broadcast.
 *
 *  @param config The stream configuration settings for the broadcast session.
 *
 *  @return A WOWZStatus object.
 */
- (nonnull WOWZStatus *) prepareForBroadcast:(nonnull WOWZStreamConfig *)config;

/*!
 *  Begins a live stream for a broadcast component.
 *
 *  @return A WOWZStatus object.
 */
- (nonnull WOWZStatus *) startBroadcasting;

/*!
 *  Ends a live stream for a broadcast component.
 *
 *  @return A WOWZStatus object.
 */
- (nonnull WOWZStatus *) stopBroadcasting;

@optional

/*!
 *  Registers an object that conforms to a WOWZMediaSink protocol.
 *
 *  @param sink An object that conforms to the WOWZMediaSink protocol.
 */
- (void) registerSink:(nonnull id<WOWZMediaSink>)sink;

/*!
 *  Unregisters an object that conforms to a WOWZMediaSink protocol.
 *
 *  @param sink An object that conforms to the WOWZMediaSink protocol.
 */
- (void) unregisterSink:(nonnull id<WOWZMediaSink>)sink;

@end
