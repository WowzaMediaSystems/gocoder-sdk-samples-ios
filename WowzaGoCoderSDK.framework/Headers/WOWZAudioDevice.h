//
//  WOWZAudioDevice.h
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
#import "WOWZBroadcastComponent.h"
#import "WOWZAudioSink.h"


/*!
 @class WOWZAudioDevice
 @discussion Use the WOWZAudioDevice class to record audio. Recorded audio samples are accessed
 by registering a WOWZAudioSink object with an instance of WOWZAudioDevice.

 */
@interface WOWZAudioDevice : NSObject <WOWZBroadcastComponent>

/*!
 *  The active audio broadcast is paused (muted).
 */
@property (nonatomic, assign) BOOL paused;

/*!
 *  Initializes a WOWZAudioDevice with default AVAudioSessionCategoryOptions.
 *
 */
- (nonnull instancetype) init;

/*!
 *  Initializes a WOWZAudioDevice with specified options.
 *
 *  @param options The AVAudioSessionCategoryOptions to use to initialize the AVSesssion.
 */
- (nonnull instancetype) initWithOptions:(AVAudioSessionCategoryOptions)options;

/*!
 *  Registers a WOWZAudioSink object.
 *  WOWZAudioSink protocol methods are called each time an audio sample is captured.
 *
 *  @param sink An object that conforms to the WOWZAudioSink protocol.
 */
- (void) registerSink:(nonnull id<WOWZAudioSink>)sink;

/*!
 *  Unregisters a WOWZAudioSink object.
 *
 *  @param sink An object that conforms to the WOWZAudioSink protocol.
 */
- (void) unregisterSink:(nonnull id<WOWZAudioSink>)sink;

+ (NSArray *_Nullable) supportedBitratesForSampleRateAndChannels:(Float64)sampleRate channels:(UInt32)numChannels;

@end
