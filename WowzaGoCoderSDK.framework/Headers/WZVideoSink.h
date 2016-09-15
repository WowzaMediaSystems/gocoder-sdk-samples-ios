//
//  WZVideoSink.h
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

#import "WZMediaSink.h"

/*!
 @protocol WZVideoSink
 @discussion WZVideoSink defines a protocol for callbacks that occur when video frames are
 captured
 */
@protocol WZVideoSink <WZMediaSink>

@required

/*!
 *  Called for each frame of unencoded video produced by a video producer.
 *
 *  @param imageBuffer
 *  The image data. Pixel format should be kCVPixelFormatType_32BGRA
 *
 *  @param framePresentationTime
 *  The relative presentation time for this frame. Implementers of this protocol should
 *  handle the case where framePresentationTime is kCMTimeInvalid. In such cases, the protocol
 *  implementer shoud infer the presentation time based on the time that the frame is delivered.
 *  The WZH264Encoder works this way.
 *
 *  @param frameDuration
 *  The duration time for this frame. Use kCMTimeInvalid for default duration.
 */
- (void) videoFrameWasCaptured:(nonnull CVImageBufferRef)imageBuffer framePresentationTime:(CMTime)framePresentationTime frameDuration:(CMTime)frameDuration;



@optional

/*!
 *  Called when an interruption in the active video capture session begins. On iOS, this
 *  typically happens when the application exits the foreground. When video
 *  capture is interrupted, broadcasting is suspended; the SDK will attempt to re-start the broadcast
 *  when interruption ends, unless the client application has stopped the broadcast. Client
 *  applications should implement the 'applicationWillResignActive' and/or 'applicationDidEnterBackground'
 *  UIApplicationDelegate methods and stop the broadcast accordingly. iOS does not allow the camera
 *  to continue capturing frames when the application is in the background.
 */
- (void) videoCaptureInterruptionStarted;

/*!
 *  Called when an interruption in the active video capture session ends. On iOS, this
 *  typically happens when the application exits and then re-enters the foreground. When video
 *  capture is interrupted, broadcasting is suspended; the SDK will attempt to re-start the broadcast
 *  when interruption ends, unless the client application has stopped the broadcast. Client
 *  applications should implement the 'applicationWillResignActive' and/or 'applicationDidEnterBackground'
 *  UIApplicationDelegate methods and stop the broadcast accordingly. iOS does not allow the camera
 *  to continue capturing frames when the application is in the background.
 */
- (void) videoCaptureInterruptionEnded;

/*!
 *  Called when the video capture queue is set internally by the capture device.
 *  Clients that wish to synchronize operations on this queue may make use
 *  of this queue if non-null.
 */
- (void) videoCaptureUsingQueue:(nullable dispatch_queue_t)queue;

@end
