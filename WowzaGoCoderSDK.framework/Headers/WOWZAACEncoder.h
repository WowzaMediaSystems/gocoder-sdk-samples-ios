//
//  WOWZAACEncoder.h
//  WowzaGoCoderSDK
//
//  © 2007 – 2019 Wowza Media Systems, LLC. All rights
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
#import "WOWZBroadcastComponent.h"
#import "WOWZAudioEncoderSink.h"
#import "WOWZAudioSink.h"

@interface WOWZAACEncoder : NSObject <WOWZBroadcastComponent, WOWZAudioSink>

// Instance methods

/*!
 *  Registers an object that conforms to the WOWZAudioEncoderSink protocol.
 *  the WOWZAudioEncoderSink protocol methods will be called each time an audio frame is encoded.
 *
 *  @param sink An object conforming to the WOWZAudioEncoderSink protocol
 */
- (void) registerSink:(nonnull id<WOWZAudioEncoderSink>)sink;

/*!
 *  Unregisters an object that conforms to the WOWZAudioEncoderSink protocol.
 *
 *  @param sink An object conforming to the WOWZAudioEncoderSink protocol
 */
- (void) unregisterSink:(nonnull id<WOWZAudioEncoderSink>)sink;


@end
