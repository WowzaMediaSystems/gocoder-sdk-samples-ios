//
//  WOWZPlatformInfo.h
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
 @class WOWZPlatformInfo
 @discussion The WOWZPlatformInfo class provides basic information about the current device.
 */
@interface WOWZPlatformInfo : NSObject

/*!
 *  Gets the device model.
 *
 *  @return A description of the device model, as returned by the uname system call.
 */
+ (nonnull NSString *) model;

/*!
 *  Gets a description of the device model in a human-readable string.
 *
 *  @return The name and other information about the model as determined by compile-time knowledge of various iOS devices in existence.
 */
+ (nonnull NSString *) friendlyModel;

/*!
 *  Gets the version of iOS installed on the device.
 *
 *  @return The version of iOS installed on the device.
 */
+ (nonnull NSString *) iOSVersion;

/*!
 *  Gets the current application.
 *
 *  @return The name of the current application running on the device.
 */
+ (nonnull NSString *) applicationName;

/*!
 *  Gets all of the device's WOWZPlatformInfo in a human-readable string.
 *
 *  @return The device's model, friendlyModel, and iOSVersion information.
 */
+ (nonnull NSString *) string;

@end
