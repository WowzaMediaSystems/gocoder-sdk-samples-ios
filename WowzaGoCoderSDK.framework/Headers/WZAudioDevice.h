//
//  WZAudioDevice.h
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
#import "WZBroadcastComponent.h"
#import "WZAudioSink.h"


/*!
 @class WZAudioDevice
 @discussion WZAudioDevice is used to recored audio. Recorded audio frames
 get be accessed by registering a WZAudioSink-conformant object with an instance
 of WZAudioDevice.

 */
@interface WZAudioDevice : NSObject <WZBroadcastComponent>

/*!
 *  Pause (mute) a running audio broadcast.
 */
@property (nonatomic, assign) BOOL paused;

/*!
 *  Initialize a WZAudioDevice with default AVAudioSessionCategoryOptions.
 *
 */
- (nonnull instancetype) init;

/*!
 *  Initialize a WZAudioDevice with specified options.
 *
 *  @param options The AVAudioSessionCategoryOptions to initialize the AVSesssion with
 */
- (nonnull instancetype) initWithOptions:(AVAudioSessionCategoryOptions)options;

/*!
 *  Registers an object that conforms to the WZAudioSink protocol.
 *  the WZAudioSink protocol methods will be called each time an audio frame is captured.
 *
 *  @param sink An object conforming to the WZAudioSink protocol
 */
- (void) registerSink:(nonnull id<WZAudioSink>)sink;

/*!
 *  Unregisters an object that conforms to the WZAudioSink protocol.
 *
 *  @param sink An object conforming to the WZAudioSink protocol
 */
- (void) unregisterSink:(nonnull id<WZAudioSink>)sink;

@end
