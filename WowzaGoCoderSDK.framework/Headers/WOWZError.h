//
//  WOWZError.h
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

#ifndef Header_h
#define Header_h

static NSString *const WowzaGoCoderSDKErrorDomain = @"com.wowza.gocoder.sdk";


/*!
 *  @typedef WOWZError
 *  @constant WOWZErrorNoError No error.
 *  @constant WOWZErrorInvalidHostAddress An invalid host address was specified.
 *  @constant WOWZErrorInvalidPortNumber An invalid port was specified.
 *  @constant WOWZErrorInvalidApplicationName An invalid live streaming application name was specified.
 *  @constant WOWZErrorInvalidStreamName An invalid live streaming stream name was specified.
 *  @constant WOWZErrorInvalidUsernameOrPassword An invalid live streaming user name or password was specified.
 *  @constant WOWZErrorConnectionError A general network connection error.
 *  @constant WOWZErrorInitializationError General initialization error.
 *  @constant WOWZErrorInternalError An internal error.
 *  @constant WOWZErrorInvalidSDKLicense The SDK license key was not recognized.
 *  @constant WOWZErrorExpiredSDKLicense The SDK license key has expired.
 *  @constant WOWZErrorExpiredSDKLicense The SDK license key has expired.
 *  @constant WOWZErrorInvalidAudioConfiguration An invalid audio sample rate, bitrate, or channels value was specified.
 *  @discussion WOWZError constants.
 */
typedef NS_ENUM(NSUInteger, WOWZError) {
    WOWZErrorNoError = 0,
    WOWZErrorInvalidHostAddress,
    WOWZErrorInvalidPortNumber,
    WOWZErrorInvalidApplicationName,
    WOWZErrorInvalidStreamName,
    WOWZErrorInvalidUsernameOrPassword,
    WOWZErrorConnectionError,
    WOWZErrorInitializationError,
    WOWZErrorInternalError,
    WOWZErrorInvalidSDKLicense,
    WOWZErrorExpiredSDKLicense,
    WOWZErrorCameraAccessDenied,
    WOWZErrorMicrophoneAccessDenied,
    WOWZErrorMicrophoneInsufficientPriority,
    WOWZErrorInvalidAudioConfiguration,
    WOWZErrorUnknownError,
};

#endif /* Header_h */
