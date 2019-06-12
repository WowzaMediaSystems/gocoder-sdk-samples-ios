//
//  WOWZCamera
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

#import <AVFoundation/AVFoundation.h>
#import "WowzaConfig.h"

/*!
 @class WOWZCamera
 @discussion Use the WOWZCamera class to access and control camera devices. To view a list of all cameras, however, use the cameras property in the WOWZCameraPreview class.
 */
@interface WOWZCamera : NSObject


/*!
*  @typedef WOWZCameraDirection
*  @constant WOWZCameraDirectionBack The back-facing camera.
*  @constant WOWZCameraDirectionFront The front-facing camera.
*  @discussion A camera direction, either front or back.
*/
typedef NS_ENUM(NSUInteger, WOWZCameraDirection) {
    WOWZCameraDirectionBack = 0,
    WOWZCameraDirectionFront
};

/*!
 *  @typedef WOWZCameraFocusMode
 *  @constant WOWZCameraFocusModeLocked The camera focus is locked at the lens's current position.
 *  @constant WOWZCameraFocusModeAuto The camera will autofocus, then switch to WOWZCameraFocusModeLocked.
 *  @constant WOWZCameraFocusModeContinuous The camera will continually adjust focus as needed.
 *  @discussion A camera focus mode.
 */
typedef NS_ENUM(NSUInteger, WOWZCameraFocusMode) {
    WOWZCameraFocusModeLocked = 0,
    WOWZCameraFocusModeAuto,
    WOWZCameraFocusModeContinuous
};

/*!
 *  @typedef WOWZCameraExposureMode
 *  @constant WOWZCameraExposureModeLocked The camera exposure is locked at its current value.
 *  @constant WOWZCameraExposureModeAuto The camera will automatically adjust exposure once, and then switch to WOWZCameraExposureModeLocked.
 *  @constant WOWZCameraExposureModeContinuous The camera will continually adjust exposure as needed.
 *  @discussion A camera exposure mode.
 */

typedef NS_ENUM(NSUInteger, WOWZCameraExposureMode) {
    WOWZCameraExposureModeLocked = 0,
    WOWZCameraExposureModeAuto,
    WOWZCameraExposureModeContinuous
};

/*!
 *  A unique identifier for the camera.
 */
@property (readonly) NSUInteger cameraId;

/*!
 *  The facing direction of the camera.
 */
@property (readonly) WOWZCameraDirection direction;

/*!
 *  The AVCaptureDevice represented by this camera.
 */
@property (nonatomic, readonly, nonnull) AVCaptureDevice *iOSCaptureDevice;

/*!
 *  The supported frame sizes for the camera, expressed as an array of CGSize values.
 */
@property (nonatomic, nonnull, readonly) NSArray<NSValue *> *frameSizes;

/*!
 *  The supported WOWZMediaConfigs for the camera.
 */
@property (nonatomic, nonnull, readonly) NSArray<WOWZMediaConfig *> *supportedPresetConfigs;

/*!
 *  Indicates whether the camera has a flash.
 */
@property (nonatomic, readonly) BOOL hasTorch;

/*!
 *  Turns the camera's flash on or off.
 */
@property (nonatomic, getter=isTorchOn) BOOL torchOn;

/*!
 *  The camera's focus mode.
 */
@property (nonatomic) WOWZCameraFocusMode focusMode;

/*!
 *  The camera's exposure mode.
 */
@property (nonatomic) WOWZCameraExposureMode exposureMode;


#pragma mark - Instance Methods

/*!
 *  Initializes a WOWZCamera from a specified AVCaptureDevice.
 *
 *  @param captureDevice The AVCaptureDevice.
 *
 *  @return An instance of WOWZCamera.
 */
- (nonnull instancetype) initWithCaptureDevice:(nonnull AVCaptureDevice *)captureDevice;

- (nonnull instancetype) init __attribute__((unavailable("initWithCaptureDevice must be used")));

/*!
 *  Indicates whether the camera supports the specified frame width.
 *
 *  @param width The width of the frame.
 *
 *  @return Yes if the camera supports the width, no otherwise.
 */
- (BOOL) supportsWidth:(NSUInteger)width;

/*!
 *  Indicates whether the camera supports the specified focus mode.
 *
 *  @param mode The focus mode.
 *
 *  @return Yes if the camera supports the focus mode, no otherwise.
 */
- (BOOL) supportsFocusMode:(WOWZCameraFocusMode)mode;

/*!
 *  Indicates whether the camera supports the specified exposure mode.
 *
 *  @param mode The exposure mode.
 *
 *  @return Yes if the camera supports the exposure mode, no otherwise.
 */
- (BOOL) supportsExposureMode:(WOWZCameraExposureMode)mode;

/*!
 *  Indicates whether the back-facing camera is being used.
 *
 *  @return Yes if this is the back-facing camera, no otherwise.
 */
- (BOOL) isBack;

/*!
 *  Indicates whether the front-facing camera is being used.
 *
 *  @return Yes if this is the front-facing camera, no otherwise.
 */
- (BOOL) isFront;

/*!
 *  Sets the camera's focus mode based on a specified point of interest.
 *
 *  @param focusMode The focus mode.
 *  @param point The point of interest, expressed as (x,y) coordinates where
 *  (0,0) indicates the camera should focus at the top-left corner of the frame and
 *  (1,1) indicates that the camera should focus at the bottom-right corner.
 */
- (void) setFocusMode:(WOWZCameraFocusMode)focusMode focusPoint:(CGPoint)point;

/*!
 *  Sets the camera's exposure mode based on a specified point of interest.
 *
 *  @param exposureMode The exposure mode.
 *  @param point The point of interest, expressed as (x,y) coordinates where
 *  (0,0) defines the top-left corner of the camera frame as the reference point for the exposure and
 *  (1,1) defines the bottom-right corner of the frame as the reference point.
 */
- (void) setExposureMode:(WOWZCameraExposureMode)exposureMode exposurePoint:(CGPoint)point;

@end
