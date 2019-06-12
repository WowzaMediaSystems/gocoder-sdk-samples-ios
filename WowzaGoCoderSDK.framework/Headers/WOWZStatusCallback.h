//
//  WOWZStatusCallback.h
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
#import "WOWZStatus.h"

/*!
 @protocol WOWZStatusCallback
 @discussion WOWZStatusCallback defines a protocol for the callback argument to the startStreaming API method used to monitor the status of a broadcast.
 */
@protocol WOWZStatusCallback <NSObject>

@required

/*!
 *  Called when an SDK component or process completes successfully.
 *
 *  @param status The WOWZStatus describing the success state (the 'state' value of the WZStatus).
 */
- (void) onWOWZStatus:(WOWZStatus *) status;

/*!
 *  Called when an SDK component or process encounters an error.
 *
 *  @param status The WOWZStatus describing the error (the 'error' value of the WOWZStatus).
 */
- (void) onWOWZError:(WOWZStatus *) status;

@optional
/*!
 *  Called when an SDK component or process wants to communicate an event.
 *
 *  @param status The WOWZStatus describing the event (the 'event' value of the WOWZStatus).
 */
- (void) onWOWZEvent:(WOWZStatus *) status;

@end
