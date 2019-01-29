//
//  WOWZAudioSink.h
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

#import "WOWZMediaSink.h"

/*!
 @protocol WOWZAudioSink
 @discussion WOWZAudioSink defines a protocol for callbacks that occur when audio samples are captured or audio levels change.
 */
@protocol WOWZAudioSink <WOWZMediaSink>

@optional

/*!
 Called for each recorded audio sample. The format of the data is uninteresting to the protocol adopter;
 use audioFrameWasCaptured only for timing information.
 To access raw audio data, use the audioPCMFrameWasCaptured protocol method.
 @param data
 The audio sample data.
 @param size
 The size, in bytes, of the captured sample.
 @param time
 The audio sample time, represented in a CMTime structure.
 @param sampleRate
 The audio sample rate.
 */
- (void) audioFrameWasCaptured:(nonnull void *)data size:(uint32_t)size time:(CMTime)time sampleRate:(Float64)sampleRate;

/*!
 Called for each recorded audio sample. Instructs the SDK to convert audio from PCM to AAC before broadcasting.
 Do NOT implement this protocol unless you specifically need the unencoded audio data.
 When audioPCMFrameWasCaptured is used, the audioFrameWasCaptured protocol method isn't called. However, if the audio converter can't convert from PCM to AAC,
 then the capture hardware will fall back to capturing AAC directly and the audioFrameWasCaptured protocol will be called instead.
 
 @param pcmASBD
 The AudioStreamBasicDescription of the PCM data.
 @param bufferList
 The AudioBufferList representation of the PCM data.
 @param time
 The audio sample time, represented in a CMTime structure.
 @param sampleRate
 The audio sample rate.
 */
- (void) audioPCMFrameWasCaptured:(nonnull const AudioStreamBasicDescription *)pcmASBD bufferList:(nonnull const AudioBufferList *)bufferList time:(CMTime)time sampleRate:(Float64)sampleRate;

/*!
 Tests whether the audio sink adopting this protocol can convert from the specified format description.
 It would be very unusual for a client to implement this protocol, which is implemented by the WOWZAACEncoder class.
 
 @param asbd
 The AudioStreamBasicDescription of the format being converted.
 @return True if the format can be converted; false otherwise.
 */
- (BOOL) canConvertStreamWithDescription:(nonnull const AudioStreamBasicDescription *)asbd;


/*!
 Called when the audio level value changes.
 @param level
 The audio level.
 */
- (void) audioLevelDidChange:(float)level;



@end

