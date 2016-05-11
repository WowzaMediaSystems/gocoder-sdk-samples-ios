//
//  WZStreamConfig.h
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

#import "WZMediaConfig.h"

/*!
 @class WZStreamConfig
 @discussion The WZStreamConfig class provides configuration properties for the streaming connection
 */
@interface WZStreamConfig : WZMediaConfig <NSMutableCopying, NSCopying, NSCoding>

#pragma mark - Properties -

/*!
 *  The fully-qualified connection URL for this config
 */
@property (nonatomic, strong, nullable) NSString *hostAddress;

/*!
 *  The server connection port number. Default is 1935.
 */
@property (nonatomic, assign) NSUInteger portNumber;

/*!
 *  The name of the live streaming application
 */
@property (nonatomic, strong, nullable) NSString *applicationName;

/*!
 *  The name of the live streaming stream
 */
@property (nonatomic, strong, nullable) NSString *streamName;

/*!
 *  The user name for Source Authentication
 */
@property (nonatomic, strong, nullable) NSString *username;

/*!
 *  The password for Source Authentication
 */
@property (nonatomic, strong, nullable) NSString *password;

#pragma mark - Public Instance Methods -

/*!
 *  Initializes a WZStreamConfig instance with a given WZFrameSizePreset
 *
 *  @param preset The WZFrameSizePreset for this config
 *
 *  @return An initialized WZStreamConfig instance
 */
- (nonnull instancetype) initWithPreset:(WZFrameSizePreset)preset;

/*!
 *  Validates that the minimum set of property values have been specified necessary to initiate a live streaming broadcast
 *
 *  @return nil if the minimum set of property values have been specified; otherwise, an NSError object describing
 *  the first encountered validation failure.
 */
- (nullable NSError *) validateForBroadcast;

/*!
 *  Copy the reciever's settings to the given WZStreamConfig
 *
 *  @param other The WZStreamConfig being copied to
 */
- (void) copyTo:(nonnull WZStreamConfig *)other;

@end
