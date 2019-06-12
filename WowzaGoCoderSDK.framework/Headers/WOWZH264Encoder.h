//
//  WOWZH264Encoder.h
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

#import <Foundation/Foundation.h>
#import "WOWZBroadcastComponent.h"
#import "WOWZVideoEncoderSink.h"
#import "WOWZVideoSink.h"

@interface WOWZH264Encoder : NSObject <WOWZBroadcastComponent, WOWZVideoSink>

/*!
 *  The pixel format for the video frames being encoded. Default is kCVPixelFormatType_32BGRA.
 *  Clients shouldn't need to modify this property unless they are encoding their own samples
 *  of a different pixel format.
 */
@property (nonatomic, assign) OSType pixelFormat;

// Instance methods

/*!
 *  Registers an object that conforms to the WOWZVideoEncoderSink protocol.
 *  the WOWZVideoEncoderSink protocol methods will be called each time a video frame is encoded.
 *
 *  @param sink An object conforming to the WOWZVideoEncoderSink protocol
 */
- (void) registerSink:(nonnull id<WOWZVideoEncoderSink>)sink;

/*!
 *  Unregisters an object that conforms to the WOWZVideoEncoderSink protocol with WowzaGoCoder.
 *
 *  @param sink An object conforming to the WOWZVideoEncoderSink protocol
 */
- (void) unregisterSink:(nonnull id<WOWZVideoEncoderSink>)sink;

- (void) setLimitedBitRate:(NSUInteger) br;
- (void) setTargetBitRate:(NSUInteger) br;


@end
