//
//  WZBroadcastComponent.h
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

#import "WZStatus.h"
#import "WZStreamConfig.h"
#import "WZMediaSink.h"

/*!
 @protocol WZBroadcastComponent
 @discussion The WZBroadcastComponent interface defines the methods that must be implemented by classes developed as broadcast components with instances registered with an instance of the WZBroadcast class.
 */
@protocol WZBroadcastComponent <NSObject>

@required

/*!
 *  Returns the status of this broadcast component
 *
 *  @return A WZStatus object
 */
- (nonnull WZStatus *) getStatus;

/**
 *  This method is called to initialize each component of a broadcast.
 *
 *  @param config The stream configuration settings for the broadcast session.
 *
 *  @return A WZStatus object
 */
- (nonnull WZStatus *) prepareForBroadcast:(nonnull WZStreamConfig *)config;

/*!
 *  This method is called on each broadcast component to begin a live streaming broadcast.
 *
 *  @return A WZStatus object
 */
- (nonnull WZStatus *) startBroadcasting;

/*!
 *  This method is called on each broadcast component to end a live streaming broadcast.
 *
 *  @return A WZStatus object
 */
- (nonnull WZStatus *) stopBroadcasting;

@optional

/*!
 *  Register an object that conforms to a WZMediaSink protocol
 *
 *  @param sink An object that conforms to the WZMediaSink protocol
 */
- (void) registerSink:(nonnull id<WZMediaSink>)sink;

/*!
 *  Unregister an object that conforms to a WZMediaSink protocol
 *
 *  @param sink An object that conforms to the WZMediaSink protocol
 */
- (void) unregisterSink:(nonnull id<WZMediaSink>)sink;

@end