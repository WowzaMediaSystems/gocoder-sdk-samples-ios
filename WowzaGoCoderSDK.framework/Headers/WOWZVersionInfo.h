//
//  WOWZVersionInfo.h
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

#import <Foundation/Foundation.h>

/*!
 @class WOWZVersionInfo
 @discussion The WOWZVersionInfo class returns aspects of the GoCoder SDK version number as NSString classes.
 */
@interface WOWZVersionInfo : NSObject

/*!
 *  Gets the major version number.
 *
 *  @return The major component of the SDK version. If the version is 1.2.3.456, for example, the major component is 1.
 */
+ (NSUInteger) majorVersion;

/*!
 *  Gets the minor version number.
 *
 *  @return The minor component of the SDK version. If the version is 1.2.3.456, for example, the minor component is 2.
 */
+ (NSUInteger) minorVersion;

/*!
 *  Gets the revision number.
 *
 *  @return The revision component of the SDK version. If the version is 1.2.3.456, for example, the revision component is 3.
 */
+ (NSUInteger) revision;

/*!
 *  Gets the build number.
 *
 *  @return The build number component of the SDK version. If the version is 1.2.3.456, for example, the build number component is 456.
 */
+ (NSUInteger) buildNumber;

/*!
 *  Gets the short version.
 *
 *  @return The major, minor, and revision components of the SDK version. If the version is 1.2.3.456, for example, the short version is 1.2.3.
 */
+ (nonnull NSString *) string;

/*!
 *  Gets the long version.
 *
 *  @return The complete SDK version. If the version is 1.2.3.456, for example, the long version is 1.2.3.456.
 */
+ (nonnull NSString *) verboseString;

@end
