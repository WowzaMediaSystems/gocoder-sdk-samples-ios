//
//  WZAACEncoder.h
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

#import <Foundation/Foundation.h>
#import "WZBroadcastComponent.h"
#import "WZAudioEncoderSink.h"
#import "WZAudioSink.h"

@interface WZAACEncoder : NSObject <WZBroadcastComponent, WZAudioSink>

// Instance methods

/*!
 *  Registers an object that conforms to the WZAudioEncoderSink protocol.
 *  the WZAudioEncoderSink protocol methods will be called each time an audio frame is encoded.
 *
 *  @param sink An object conforming to the WZAudioEncoderSink protocol
 */
- (void) registerSink:(nonnull id<WZAudioEncoderSink>)sink;

/*!
 *  Unregisters an object that conforms to the WZAudioEncoderSink protocol.
 *
 *  @param sink An object conforming to the WZAudioEncoderSink protocol
 */
- (void) unregisterSink:(nonnull id<WZAudioEncoderSink>)sink;


@end
