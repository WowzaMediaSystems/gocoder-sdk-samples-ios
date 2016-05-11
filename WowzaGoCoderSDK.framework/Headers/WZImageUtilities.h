//
//  WZImageUtility.h
//  WowzaBroadcaster
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
#import <CoreVideo/CoreVideo.h>


@interface WZImageUtilities : NSObject

/*!
 *  Converts a CVPixelBufferRef to a UIImage.
 *
 *  @param pixelBuffer The CVPixelBufferRef to be converted.
 *  @param destinationImageSize A CGSize describing the resulting UIImage size.
 *
 *  @return A UIImage object if conversion was successful, otherwise nil.
 */
+ (nullable UIImage *) imageFromCVPixelBuffer:(nonnull CVPixelBufferRef)pixelBuffer destinationImageSize:(CGSize)destinationImageSize;

/*!
 *  Converts a CVPixelBufferRef to a UIImage, applying a specified rotation value.
 *
 *  @param pixelBuffer The CVPixelBufferRef to be converted.
 *  @param destinationImageSize A CGSize describing the resulting UIImage size.
 *  @param rotationAngle The amount to rotate the result UIImage.
 *
 *  @return A UIImage object if conversion was successful, otherwise nil.
 */
+ (nullable UIImage *) imageFromCVPixelBuffer:(nonnull CVPixelBufferRef)pixelBuffer destinationImageSize:(CGSize)destinationImageSize rotationAngle:(NSInteger)rotationAngle;

@end