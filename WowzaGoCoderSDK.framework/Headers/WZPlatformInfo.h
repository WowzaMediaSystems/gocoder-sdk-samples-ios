//
//  WZPlatformInfo.h
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
 @class WZPlatformInfo
 @discussion WZPlatformInfo provides some basic information about the current device.
 */
@interface WZPlatformInfo : NSObject

/*!
 *  Device model
 *
 *  @return A string describing the device model, as returned by 'uname'
 */
+ (nonnull NSString *) model;

/*!
 *  A more human-readable device model description.
 *
 *  @return The model name as returned by model, along with other information about that model
 *  that can be determined by compile-time knowledge of various iOS devices in existence.
 */
+ (nonnull NSString *) friendlyModel;

/*!
 *  The version of iOS installed on the device
 *
 *  @return A string describing the version of iOS
 */
+ (nonnull NSString *) iOSVersion;

/*!
 *  All the WZPlatformInfo information returned in a human-readable string
 *
 *  @return A string representation of all the WZPlatformInfo information
 */
+ (nonnull NSString *) string;

@end
