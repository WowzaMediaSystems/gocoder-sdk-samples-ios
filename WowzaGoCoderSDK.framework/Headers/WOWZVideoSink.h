//
//  WOWZVideoSink.h
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

#import "WOWZMediaSink.h"

/*!
 @protocol WOWZVideoSink
 @discussion WOWZVideoSink defines a protocol for callbacks that occur when video frames are captured.
 */
@protocol WOWZVideoSink <WOWZMediaSink>

@required

/*!
 *  Called for each frame of unencoded video.
 *
 *  @param imageBuffer
 *  The image data. Pixel format should be kCVPixelFormatType_32BGRA.
 *
 *  @param framePresentationTime
 *  The relative presentation time for this frame. Use when frameDuration is kCMTimeInvalid. The protocol
 *  implementer should infer the presentation time based on the time that the frame is delivered.
 *  The WOWZH264Encoder works this way.
 *
 *  @param frameDuration
 *  The duration of the frame. Use kCMTimeInvalid for default duration.
 */
- (void) videoFrameWasCaptured:(nonnull CVImageBufferRef)imageBuffer framePresentationTime:(CMTime)framePresentationTime frameDuration:(CMTime)frameDuration;



@optional

/*!
 *  Called at the beginning of an interruption to an active video-capture session, which typically occurs when the application exits the foreground.
 *  iOS doesn't allow the camera to capture frames when the application is in the background, so when the application transitions out of the foreground, broadcasting is suspended.
 *  The SDK will attempt to restart the broadcast when the interruption ends (when the application returns to the foreground), unless the client application has stopped the broadcast.
 *  Client applications should implement Apple's applicationWillResignActive and/or applicationDidEnterBackground methods in the
 *  UIApplicationDelegate protocol and stop the broadcast accordingly.
  */
- (void) videoCaptureInterruptionStarted;

/*!
 *  Called at the end of an interruption to an active video-capture session, which typically occurs when the application returns to the foreground after being in the background.
 *  iOS doesn't allow the camera to capture frames when the application is in the background, so when the application transitions out of the foreground, broadcasting is suspended.
 *  The SDK will attempt to restart the broadcast when the interruption ends (when the application returns to the foreground), unless the client application has stopped the broadcast.
 *  Client applications should implement Apple's applicationWillResignActive and/or applicationDidEnterBackground methods in the
 *  UIApplicationDelegate protocol and stop the broadcast accordingly.
 */
- (void) videoCaptureInterruptionEnded;

/*!
 *  Called when the capture device internally sets the video-capture queue.
 *  Clients can synchronize operations on this queue if it's non-null.
 */
- (void) videoCaptureUsingQueue:(nullable dispatch_queue_t)queue;

@end
