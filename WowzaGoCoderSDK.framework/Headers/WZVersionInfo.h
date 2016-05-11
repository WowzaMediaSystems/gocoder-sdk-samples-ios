//
//  WZVersionInfo.h
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

#import <Foundation/Foundation.h>

/*!
 @class WZVersionInfo
 @discussion The WZVersionInfo class provides access to GoCoder SDK version information.
 */
@interface WZVersionInfo : NSObject

/*!
 *  The major version number
 *
 *  @return The major component of the SDK version string; e.g.: 1 if the version is "1.2.3.456"
 */
+ (NSUInteger) majorVersion;

/*!
 *  The minor version number
 *
 *  @return The minor component of the SDK version string; e.g.: 2 if the version is "1.2.3.456"
 */
+ (NSUInteger) minorVersion;

/*!
 *  The revision number
 *
 *  @return The revision component of the SDK version string; e.g.: 3 if the version is "1.2.3.456"
 */
+ (NSUInteger) revision;

/*!
 *  The build number
 *
 *  @return The build number component of the SDK version string; e.g.: 456 if the version is "1.2.3.456"
 */
+ (NSUInteger) buildNumber;

/*!
 *  The short version string
 *
 *  @return The short version string as an NSString; e.g.: "1.2.3" if the version is "1.2.3.456"
 */
+ (nonnull NSString *) string;

/*!
 *  The long version string
 *
 *  @return The long version string as an NSString; e.g.: "1.2.3.456" if the version is "1.2.3.456"
 */
+ (nonnull NSString *) verboseString;

@end
