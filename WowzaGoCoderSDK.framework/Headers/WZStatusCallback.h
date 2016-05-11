//
//  WZStatusCallback.h
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
#import "WZStatus.h"

/*!
 @protocol WZStatusCallback
 @discussion WZStatusCallback defines a protocol for the callback argument to the startStreaming API method used to monitor the status of a broadcast.
 */
@protocol WZStatusCallback <NSObject>

@required

/*!
 *  Required protocol method that will be called when a SDK component or process completes successfully
 *
 *  @param status The WZStatus describing the success state (the 'state' value of the WZStatus).
 */
- (void) onWZStatus:(WZStatus *) status;

/*!
 *  Required protocol method that will be called when a SDK component or process encounters an error
 *
 *  @param status The WZStatus describing the error (the 'error' value of the WZStatus).
 */
- (void) onWZError:(WZStatus *) status;

@optional
/*!
 *  Optional protocol method that will be called when a SDK component or process wants to
 *  communicate an event.
 *
 *  @param status The WZStatus describing the event (the 'event' value of the WZStatus).
 */
- (void) onWZEvent:(WZStatus *) status;

@end
