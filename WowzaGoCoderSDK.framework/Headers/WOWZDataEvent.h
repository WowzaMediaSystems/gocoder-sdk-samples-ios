//
//  WOWZDataEvent.h
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
#import <CoreMedia/CoreMedia.h>
#import "WOWZData.h"


/*!
 *  @typedef WOWZDataScope
 *  @constant WOWZDataScopeModule Data events sent with a WOWZDataScopeModule scope will be mapped to an invocation of a public handler method contained within any active server module class having the same name as the event.
 *  @constant WOWZDataScopeStream Data events sent with a WOWZDataScopeStream scope will be delivered to each client subscribed to the stream.
 *  @discussion Identifiers for the various data scopes to which a data event can be targeted.
 */
typedef NS_ENUM(NSUInteger, WOWZDataScope) {
    WOWZDataScopeModule,
    WOWZDataScopeStream
};


/*!
 @class WOWZDataEvent
 @discussion The WOWZDataEvent class provides the top-level interface for encapsulating map, or list, of items that represent server metadata that's sent and received by GoCoder.
 */
@interface WOWZDataEvent : NSObject

/*!
 *  The name of the WOWZDataEvent.
 */
@property (nonatomic, strong, nullable) NSString *eventName;

/*!
 *  The WOWZDataMap that contains the event metadata. If this value is set, eventListParams should be nil.
 */
@property (nonatomic, strong, nullable) WOWZDataMap *eventMapParams;


/*!
 *  Initializes a WOWZDataEvent with a WOWZDataMap of event metadata.
 *
 *  @param name The name of the WOWZDataEvent.
 *  @param mapParams The map of event metadata to include in the WOWZDataEvent.
 *
 *  @return An instance of WOWZDataEvent.
 */
- (nonnull instancetype) initWithName:(nonnull NSString *)name mapParams:(nonnull WOWZDataMap *)mapParams;


@end


