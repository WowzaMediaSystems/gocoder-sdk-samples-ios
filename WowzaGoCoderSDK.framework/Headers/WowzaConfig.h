//
//  WowzaConfig.h
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
//

#import "WOWZStreamConfig.h"

#pragma mark WowzaConfig Class -

/*!
 @class WowzaConfig
 @discussion Applications use the top-level WowzaConfig class to configure various GoCoder SDK components.
 
 @code // Example:
 WowzaConfig *goCoderConfig = [[WowzaConfig alloc] initWithPreset:WOWZFrameSizePreset1280x720];
 goCoderConfig.hostAddress = @"live.streamingserver.com";
 goCoderConfig.applicationName = @"LiveStreamingApp";
 goCoderConfig.capturedVideoRotates = NO;
 */
@interface WowzaConfig : WOWZStreamConfig <NSMutableCopying, NSCopying, NSCoding>

#pragma mark - Constructors -

/*!
 *  Initializes a WowzaConfig instance with a video frame-size preset.
 *
 *  @param preset A WOWZFrameSizePreset.
 *
 *  @return An instance of WowzaConfig.
 */
- (nonnull instancetype) initWithPreset:(WOWZFrameSizePreset)preset;

#pragma mark - Public Instance Methods -

/*!
 *  Copies receiver to the specified WowzaConfig.
 *
 *  @param other The WowzaConfig object to copy to.
 */
- (void) copyTo:(nonnull WowzaConfig *)other;


@end


