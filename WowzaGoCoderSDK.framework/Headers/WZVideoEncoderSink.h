//
//  WZVideoEncoderSink.h
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
 @protocol WZVideoEncoderSink
 @discussion WZVideoEncoderSink defines a protocol for callbacks that occur when video frames are
 encoded
 */
@protocol WZVideoEncoderSink <WZMediaSink>

@required

/*!
 Called for each frame of video that was encoded by a video encoder.
 @param data
 The frame's encoded image data.
 */
- (void) videoFrameWasEncoded:(nonnull CMSampleBufferRef)data;


@optional

/*!
 DEPRECATED: Use the WZStatusCallback's onWZEvent events WZEventBitrateReduced and WZEventBitrateIncreased instead
 Called when the sink bitrate is reduced due to inability to keep up with encoded frames.
 @param newBitrate
 The new (updated) bitrate.
 @param previousBitrate
 The previous bitrate.
 */
- (void) videoBitrateDidChange:(NSUInteger)newBitrate previousBitrate:(NSUInteger)previousBitrate __attribute__((deprecated));

@end
