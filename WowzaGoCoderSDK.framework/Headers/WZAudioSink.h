//
//  WZAudioSink.h
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
 @protocol WZAudioSink
 @discussion WZAudioSink defines a protocol for callbacks that occur when audio frames are
 captured, or audio level changes.
 */
@protocol WZAudioSink <WZMediaSink>

@optional

/*!
 Called for each frame of audio recorded by an audio device. The format of the data is uninteresting
 to the protocol adopter; this protocol should be used for timing information only. If you wish to access
 raw audio data, please implement the audioPCMFrameWasCaptured protocol method instead of this one.
 @param data
 The audio frame data.
 @param size
 The size, in bytes, of the captured frame
 @param time
 The audio frame time, represented in a CMTime structure
 @param sampleRate
 The audio sample rate
 */
- (void) audioFrameWasCaptured:(nonnull void *)data size:(uint32_t)size time:(CMTime)time sampleRate:(Float64)sampleRate;

/*!
 Called for each frame of audio recorded by an audio device. Clients implementing this protocol should be aware
 that doing so causes the SDK to go through a PCM to AAC audio conversion process before broadcasting. Thus, please
 DO NOT IMPLEMENT THIS PROTOCOL UNLESS YOU HAVE A SPECIFIC NEED FOR THE UN-ENCODED AUDIO DATA. If you implement this
 protocol, the audioFrameWasCaptured protocol method will never be called.
 
 Note that implementing this protocol doesn't guarentee that it will be called. If the audio converter is unable for any
 reason to convert from PCM to AAC, then the capture hardware will fall back to capturing AAC directly; in which case
 the audioFrameWasCaptured protocol above will be called instead.
 
 @param pcmASBD
 The AudioStreamBasicDescription of the PCM data
 @param bufferList
 The AudioBufferList representation of the PCM data.
 @param time
 The audio frame time, represented in a CMTime structure
 @param sampleRate
 The audio sample rate
 */
- (void) audioPCMFrameWasCaptured:(nonnull const AudioStreamBasicDescription *)pcmASBD bufferList:(nonnull const AudioBufferList *)bufferList time:(CMTime)time sampleRate:(Float64)sampleRate;

/*!
 Test whether or not the audio sink adopting this protocol can convert from the specified format description. It would be very
 unusual for a client to implement this protocol; it is implemented by the WZAACEncoder class.
 
 @param asbd
 The AudioStreamBasicDescription of the format being converted from
 @return True if the format can be converted from; otherwise false
 */
- (BOOL) canConvertStreamWithDescription:(nonnull const AudioStreamBasicDescription *)asbd;


/*!
 Called whenever the audio level value changes.
 @param level
 The current level value.
 */
- (void) audioLevelDidChange:(float)level;



@end

