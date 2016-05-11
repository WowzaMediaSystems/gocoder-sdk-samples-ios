//
//  WZCameraPreview
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

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "WZCamera.h"
#import "WowzaConfig.h"


#pragma mark WZCameraPreview Class
#pragma mark -

/*!
 @class WZCameraPreview
 @discussion The WZCameraPreview class wraps a camera and a preview for previewing the video captured from a camera device
 */
@interface WZCameraPreview : NSObject

/*!
*  @typedef WZCameraPreviewGravity
*  @constant WZCameraPreviewGravityResizeAspect Preserve aspect ratio; fit within layer bounds.
*  @constant WZCameraPreviewGravityResizeAspectFill Preserve aspect ratio; fill layer bounds.
*  @constant WZCameraPreviewGravityResize Stretch to fill layer bounds.
*  @discussion Describes how the video preview should fill the video preview frame.
*/

typedef NS_ENUM(NSUInteger, WZCameraPreviewGravity) {
    WZCameraPreviewGravityResizeAspect = 0,
    WZCameraPreviewGravityResizeAspectFill,
    WZCameraPreviewGravityResize
};


#pragma mark -
#pragma mark Public Class Methods
#pragma mark -

/*!
 *  The number of cameras available on this device
 *
 *  @return Count of the number of cameras available
 */
+ (NSInteger) numberOfDeviceCameras;

/*!
 *  An array of WZCamera objects available on this device
 *
 *  @return The array of WZCamera objects
 */
+ (nonnull NSArray<WZCamera *> *) deviceCameras;

#pragma mark -
#pragma mark Public Properties
#pragma mark -

/*!
 *  The active camera
 */
@property (nonatomic, nullable) WZCamera* camera;

/*!
 *  The active config for the camera
 */
@property (nonatomic, nonnull) WowzaConfig *config;


/*!
 *  The AV Foundation preview layer. Will be null until startPreview is called.
 */
@property (nonatomic, readonly, nullable) AVCaptureVideoPreviewLayer *previewLayer;

/*!
 *  The preview gravity to use for displaying the video preview; describes
 *  how the prview will fill the given view bounds
 */
@property (nonatomic, assign) WZCameraPreviewGravity previewGravity;

/*!
 *  The array of WZCamera objects available on this device
 */
@property (nonatomic, readonly, nullable) NSArray<WZCamera *> *cameras;

/*!
 *  Is video previewing currently active
 */
@property (nonatomic, readonly, getter=isPreviewActive) BOOL previewActive;

#pragma mark -
#pragma mark Constructors
#pragma mark -

- (nonnull instancetype) init __attribute__((unavailable("init is unavailable")));

/*!
 *  Initialize a WZCameraPreview object
 *
 *  @param containingView The view to which the preview layer will be added
 *  @param aConfig        The configuration settings for the camera and preview
 *
 *  @return An initialized WZCameraPreview object
 */
- (nonnull instancetype) initWithViewAndConfig:(nonnull UIView *)containingView config:(nonnull WowzaConfig *)aConfig;

#pragma mark -
#pragma mark Public Instance Methods
#pragma mark -

/*!
 *  Start previewing the video stream
 */
- (void) startPreview;

/*!
 *  Stop previewing the video stream
 */
- (void) stopPreview;


#pragma mark -

/*!
 *  Use to determine if there is another camera on the device and if so,
 *  does it support the given WZMediaConfig
 *
 *  @param config The WZMediaConfig for which to test the other camera's support
 *
 *  @return YES if the other camera supports the given WZMediaConfig, otherwise NO
 */
- (BOOL) isSwitchCameraAvailableForConfig:(nonnull WZMediaConfig *)config;

/*!
 *  Switch to the 'other' camera if there is another camara, and if the other
 *  camera supports the current config.
 *
 *  @return The camera switched to, or the current camera of the other camera either
 *  doesn't exist, or doesn't support the current config.
 */
- (nonnull WZCamera *) switchCamera;

/*!
 *  Get a reference to the camera not currently in use, if the device has more than one camera.
 *
 *  @return A reference to the camera not currently in use, or nil if there is only one camera.
 */
- (nullable WZCamera *) otherCamera;

@end
