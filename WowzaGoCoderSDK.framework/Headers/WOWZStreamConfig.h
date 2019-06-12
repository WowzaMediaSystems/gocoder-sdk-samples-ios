//
//  WOWZStreamConfig.h
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

#import "WOWZMediaConfig.h"
#import "WOWZData.h"

/*!
 @class WOWZStreamConfig
 @discussion The WOWZStreamConfig class provides configuration properties for the streaming connection.
 */
@interface WOWZStreamConfig : WOWZMediaConfig <NSMutableCopying, NSCopying, NSCoding>

#pragma mark - Properties -

/*!
 *  The fully qualified connection URL for the config.
 */
@property (nonatomic, strong, nullable) NSString *hostAddress;

/*!
 *  The port number for the server connection. The default is 1935.
 */
@property (nonatomic, assign) NSUInteger portNumber;

/*!
 *  The name of the live-streaming application.
 */
@property (nonatomic, strong, nullable) NSString *applicationName;

/*!
 *  The name of the live stream.
 */
@property (nonatomic, strong, nullable) NSString *streamName;

/*!
 *  The user name for source authentication.
 */
@property (nonatomic, strong, nullable) NSString *username;

/*!
 *  The password for source authentication.
 */
@property (nonatomic, strong, nullable) NSString *password;
/*!
 *  The connection parameters passed as the query string at connection.
 */
@property (nonatomic, strong, nullable) WOWZDataMap *connectionParameters;


#pragma mark - Public Instance Methods -

/*!
 *  Initializes a WOWZStreamConfig instance with a specified WOWZFrameSizePreset.
 *
 *  @param preset The WOWZFrameSizePreset for the config.
 *
 *  @return An initialized WOWZStreamConfig instance.
 */
- (nonnull instancetype) initWithPreset:(WOWZFrameSizePreset)preset;

/*!
 *  Validates that the minimum set of property values has been specified to initiate a live-stream broadcast.
 *
 *  @return Nil if the minimum set of values has been specified; otherwise, an NSError object that describes the first validation failure.
 */
- (nullable NSError *) validateForBroadcast;

/*!
 *  Copies the receiver's settings to the specified WOWZStreamConfig.
 *
 *  @param other The WOWZStreamConfig to copy to.
 */
- (void) copyTo:(nonnull WOWZStreamConfig *)other;

@end
