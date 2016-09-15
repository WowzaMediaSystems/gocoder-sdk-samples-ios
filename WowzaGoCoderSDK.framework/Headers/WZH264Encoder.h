//
//  WZH264Encoder.h
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
#import "WZVideoEncoderSink.h"
#import "WZVideoSink.h"

@interface WZH264Encoder : NSObject <WZBroadcastComponent, WZVideoSink>

/*!
 *  The pixel format for the video frames being encoded. Default is kCVPixelFormatType_32BGRA.
 *  Clients shouldn't need to modify this property unless they are encoding their own samples
 *  of a different pixel format.
 */
@property (nonatomic, assign) OSType pixelFormat;

// Instance methods

/*!
 *  Registers an object that conforms to the WZVideoEncoderSink protocol.
 *  the WZVideoEncoderSink protocol methods will be called each time a video frame is encoded.
 *
 *  @param sink An object conforming to the WZVideoEncoderSink protocol
 */
- (void) registerSink:(nonnull id<WZVideoEncoderSink>)sink;

/*!
 *  Unregisters an object that conforms to the WZVideoEncoderSink protocol with WowzaGoCoder.
 *
 *  @param sink An object conforming to the WZVideoEncoderSink protocol
 */
- (void) unregisterSink:(nonnull id<WZVideoEncoderSink>)sink;


@end
