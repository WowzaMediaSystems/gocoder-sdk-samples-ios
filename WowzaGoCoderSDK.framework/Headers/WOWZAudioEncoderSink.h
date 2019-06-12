//
//  WOWZAudioEncoderSink.h
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
 @protocol WOWZAudioEncoderSink
 @discussion WOWZAudioEncoderSink defines a protocol for callbacks that occur when audio samples are encoded.
 */
@protocol WOWZAudioEncoderSink <WOWZMediaSink>

@optional


/*!
 Called for each frame of encoded audio.
 @param data
 The sample's encoded audio data.
 */
- (void) audioSampleWasEncoded:(nullable CMSampleBufferRef)data;

/*!
 Called for each frame of encoded audio.
 @param data
 The audio sample data.
 @param size
 The size, in bytes, of the audio sample.
 @param time
 The audio sample time, represented in a CMTime structure.
 @param sampleRate
 The audio sample rate.
 */
- (void) audioFrameWasEncoded:(nonnull void *)data size:(uint32_t)size time:(CMTime)time sampleRate:(Float64)sampleRate;

@end
