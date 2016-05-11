//
//  WZAudioEncoderSink.h
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
 @protocol WZAudioEncoderSink
 @discussion WZAudioEncoderSink defines a protocol for callbacks that occur when audio frames are
 encoded
 */
@protocol WZAudioEncoderSink <WZMediaSink>

@optional


/*!
 Called for each frame of encoded audio produced by an audio encoder.
 @param data
 The frame's encoded audio data.
 */
- (void) audioSampleWasEncoded:(nullable CMSampleBufferRef)data;

/*!
 Called for each frame of encoded audio produced by an audio encoder.
 @param data
 The audio frame data.
 @param size
 The size, in bytes, of the audio frame data.
 @param time
 The audio frame time, represented in a CMTime structure
 @param sampleRate
 The audio sample rate
 */
- (void) audioFrameWasEncoded:(nonnull void *)data size:(uint32_t)size time:(CMTime)time sampleRate:(Float64)sampleRate;

@end
