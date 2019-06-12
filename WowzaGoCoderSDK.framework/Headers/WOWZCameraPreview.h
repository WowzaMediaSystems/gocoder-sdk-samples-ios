//
//  WOWZCameraPreview
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

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "WOWZCamera.h"
#import "WowzaConfig.h"


#pragma mark WOWZCameraPreview Class
#pragma mark -

/*!
 @class WOWZCameraPreview
 @discussion The WOWZCameraPreview class allows you to preview video captured from a camera device.
 */
@interface WOWZCameraPreview : NSObject

/*!
*  @typedef WOWZCameraPreviewGravity
*  @constant WOWZCameraPreviewGravityResizeAspect Preserve aspect ratio; fit within layer bounds.
*  @constant WOWZCameraPreviewGravityResizeAspectFill Preserve aspect ratio; fill layer bounds.
*  @constant WOWZCameraPreviewGravityResize Stretch to fill layer bounds.
*  @discussion Describes how the video should fill the preview frame.
*/

typedef NS_ENUM(NSUInteger, WOWZCameraPreviewGravity) {
    WOWZCameraPreviewGravityResizeAspect = 0,
    WOWZCameraPreviewGravityResizeAspectFill,
    WOWZCameraPreviewGravityResize
};


#pragma mark -
#pragma mark Public Class Methods
#pragma mark -

/*!
 *  Gets the number of cameras available on the device.
 *
 *  @return The number of cameras available.
 */
+ (NSInteger) numberOfDeviceCameras;

/*!
 *  Gets an array of the WOWZCamera objects available on the device.
 *
 *  @return The array of WOWZCamera objects.
 */
+ (nonnull NSArray<WOWZCamera *> *) deviceCameras;

#pragma mark -
#pragma mark Public Properties
#pragma mark -

/*!
 *  The active camera.
 */
@property (nonatomic, nullable) WOWZCamera* camera;

/*!
 *  The active config for the camera.
 */
@property (nonatomic, nonnull) WowzaConfig *config;


/*!
 *  The AV Foundation preview layer. Null until startPreview is called.
 */
@property (nonatomic, readonly, nullable) AVCaptureVideoPreviewLayer *previewLayer;

/*!
 *  The preview gravity to use to display the video preview.
 *  Preview gravity describes how the video should fill the available screen area.
 */
@property (nonatomic, assign) WOWZCameraPreviewGravity previewGravity;

/*!
 *  The array of WOWZCamera objects available on the device.
 */
@property (nonatomic, readonly, nullable) NSArray<WOWZCamera *> *cameras;

/*!
 *  Indicates whether a video is actively previewing.
 */
@property (nonatomic, readonly, getter=isPreviewActive) BOOL previewActive;

#pragma mark -
#pragma mark Constructors
#pragma mark -

- (nonnull instancetype) init __attribute__((unavailable("init is unavailable")));

/*!
 *  Initializes a WOWZCameraPreview object.
 *
 *  @param containingView The view to which the preview layer will be added.
 *  @param aConfig The configuration settings for the camera and the preview.
 *
 *  @return An initialized WOWZCameraPreview object.
 */
- (nonnull instancetype) initWithViewAndConfig:(nonnull UIView *)containingView config:(nonnull WowzaConfig *)aConfig;

#pragma mark -
#pragma mark Public Instance Methods
#pragma mark -

/*!
 *  Starts previewing the video stream.
 */
- (void) startPreview;

/*!
 *  Stops previewing the video stream.
 */
- (void) stopPreview;


#pragma mark -

/*!
 *  Indicates whether another camera is available on the device and whether
 *  that camera supports the specified WOWZMediaConfig.
 *
 *  @param config The WOWZMediaConfig to test for support by the other camera.
 *
 *  @return Yes if the device has another camera that supports the specified WOWZMediaConfig, no otherwise.
 */
- (BOOL) isSwitchCameraAvailableForConfig:(nonnull WOWZMediaConfig *)config;

/*!
 *  Switches to the device's other camera.
 *
 *  @return The device's other camera, if it exists and supports the current config; otherwise, the same camera.
 */
- (nonnull WOWZCamera *) switchCamera;

/*!
 *  Gets a reference to the camera not currently in use, if the device has more than one camera.
 *
 *  @return The reference to the camera not in use, or nil if there's only one camera.
 */
- (nullable WOWZCamera *) otherCamera;

@end
