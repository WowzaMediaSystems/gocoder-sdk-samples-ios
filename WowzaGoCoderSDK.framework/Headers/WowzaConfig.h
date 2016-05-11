//
//  WowzaConfig.h
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
//

#import "WZStreamConfig.h"

#pragma mark WowzaConfig Class -

/*!
 @class WowzaConfig
 @discussion WowzaConfig is the top level configuration class used by applications to configure the various SDK components.
 
 @code // Example:
 WowzaConfig *goCoderConfig = [[WowzaConfig alloc] initWithPreset:WZFrameSizePreset1280x720];
 goCoderConfig.hostAddress = @"live.streamingserver.com";
 goCoderConfig.applicationName = @"LiveStreamingApp";
 goCoderConfig.capturedVideoRotates = NO;
 */
@interface WowzaConfig : WZStreamConfig <NSMutableCopying, NSCopying, NSCoding>

#pragma mark - Constructors -

/*!
 *  Initialize a WowzaConfig with a video frame-size preset
 *
 *  @param preset a WZFrameSizePreset
 *
 *  @return an instance of WowzaConfig
 */
- (nonnull instancetype) initWithPreset:(WZFrameSizePreset)preset;

#pragma mark - Public Instance Methods -

/*!
 *  Copy receiver to given WowzaConfig
 *
 *  @param other WowzaConfig object being copied to
 */
- (void) copyTo:(nonnull WowzaConfig *)other;


@end


