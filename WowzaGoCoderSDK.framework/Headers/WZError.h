//
//  WZError.h
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

#ifndef Header_h
#define Header_h

static NSString *const WowzaGoCoderSDKErrorDomain = @"com.wowza.gocoder.sdk";


/*!
 *  @typedef WZError
 *  @constant WZErrorNoError No error.
 *  @constant WZErrorInvalidHostAddress An invalid host address was specified.
 *  @constant WZErrorInvalidPortNumber An invalid port was specified.
 *  @constant WZErrorInvalidApplicationName An invalid live streaming application name was specified.
 *  @constant WZErrorInvalidStreamName An invalid live streaming stream name was specified.
 *  @constant WZErrorInvalidUsernameOrPassword An invalid live streaming user name or password was specified.
 *  @constant WZErrorConnectionError A general network connection error.
 *  @constant WZErrorInitializationError General initialization error.
 *  @constant WZErrorInternalError An internal error.
 *  @constant WZErrorInvalidSDKLicense The SDK license key was not recognized.
 *  @constant WZErrorExpiredSDKLicense The SDK license key has expired.
 *  @constant WZErrorUnknownError An unknown error.
 *  @discussion WZError constants.
 */
typedef NS_ENUM(NSUInteger, WZError) {
    WZErrorNoError = 0,
    WZErrorInvalidHostAddress,
    WZErrorInvalidPortNumber,
    WZErrorInvalidApplicationName,
    WZErrorInvalidStreamName,
    WZErrorInvalidUsernameOrPassword,
    WZErrorConnectionError,
    WZErrorInitializationError,
    WZErrorInternalError,
    WZErrorInvalidSDKLicense,
    WZErrorExpiredSDKLicense,
    WZErrorCameraAccessDenied,
    WZErrorMicrophoneAccessDenied,
    WZErrorMicrophoneInsufficientPriority,
    WZErrorUnknownError,
};

#endif /* Header_h */
