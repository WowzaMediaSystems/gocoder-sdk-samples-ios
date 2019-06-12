//
//  WOWZStatus.h
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

/*!
 @discussion WOWZStatusNewBitrateKey is the entry in the WOWZStatus class data dictionary for the new bitrate value, represented as an NSNumber.
 */
extern NSString * __nonnull const WOWZStatusNewBitrateKey;

/*!
 @discussion WOWZStatusPreviousBitrateKey is the entry in the WOWZStatus class data dictionary for the previous bitrate value, represented as an NSNumber.
 */
extern NSString * __nonnull const  WOWZStatusPreviousBitrateKey;

/*!
 @class WOWZStatus
 @discussion WOWZStatus is a thread-safe class for working with SDK component state and error properties.
 Client applications typically don't have any need for creating a WOWZStatus object.
 */
@interface WOWZStatus : NSObject <NSMutableCopying, NSCopying>

/*!
 *  @typedef WOWZState
 *  @constant WOWZStateIdle The broadcasting component or session is idle.
 *  @constant WZStateStarting The broadcasting component or session is starting.
 *  @constant WOWZStateRunning The broadcasting component or session is broadcasting.
 *  @constant WOWZStateStopping The broadcasting component or session is shutting down.
 *  @constant WOWZStateBuffering The broadcasting component or session is buffering.
 *  @constant WOWZStateReady The broadcasting component or session is ready or has been initialized.
 *  @discussion A collection of constants that describe the state of the broadcasting component or session.
 */
typedef NS_ENUM(NSUInteger, WOWZState) {
    WOWZStateIdle = 0,
    WOWZStateStarting,
    WOWZStateRunning,
    WOWZStateStopping,
    WOWZStateBuffering,
    WOWZStateReady
};

/*!
 *  @typedef WOWZEvent
 *  @constant WOWZEventNone No event.
 *  @constant WOWZEventLowBandwidth If network bandwidth is insufficient for the specified video-broadcast settings, the encoder may attempt to compensate by sending a reduced bitrate or frame rate.
 *  @constant WOWZEventBitrateReduced Sent when the encoder reduces the stream bitrate to compensate for low-bandwidth conditions. Changing the bitrate adds WOWZStatusNewBitrateKey and WOWZStatusPreviousBitrateKey,
 *  represented as NSNumber values, to the WOWZStatus class data dictionary.
 *  @constant WOWZEventBitrateIncreased Sent when the encoder increases the bitrate after having previously reduced it. The bitrate will never
 *  increase beyond the original bitrate specified in the configuration settings for the streaming session. Changing the bitrate adds WOWZStatusNewBitrateKey and WOWZStatusPreviousBitrateKey,
 *  represented as NSNumber values, to the WOWZStatus class data dictionary.
 *  @constant WOWZEventEncoderPaused Sent when the encoder stops sending frames and waits for queued frames to catch up. Typically, the encoder pauses while it's reducing the bitrate to compensate for constrained network bandwidth.
 *  @constant WOWZEventEncoderResumed Sent when a previously paused encoder resumes.
 *  @discussion A collection of constants that describe the component event.
 */
typedef NS_ENUM(NSUInteger, WOWZEvent) {
    WOWZEventNone = 0,
    WOWZEventLowBandwidth,
    WOWZEventBitrateReduced,
    WOWZEventBitrateIncreased,
    WOWZEventEncoderPaused,
    WOWZEventEncoderResumed
};

#pragma mark - Properties

/*!
 *  The state of the broadcast session.
 */
@property (nonatomic) WOWZState state;

/*!
 *  The event used by the broadcast session.
 */
@property (nonatomic) WOWZEvent event;

/*!
 *  The last error reported by the broadcast session.
 */
@property (nonatomic, strong, nullable) NSError * error;

/*!
 *  Data related to the status. May be null.
 */
@property (nonatomic, strong, nullable) NSDictionary * data;

#pragma mark - Class Methods

/*!
 *  Returns a WOWZStatus object with a specified state.
 *
 *  @param aState The state to use to initialize the object.
 *
 *  @return An initialized WOWZStatus object.
 */
+ (nonnull instancetype) statusWithState:(WOWZState)aState;

/*!
 *  Returns a WOWZStatus object with a specified state and error.
 *
 *  @param aState The state to use to initialize the object.
 *  @param aError The error to use to initialize the object.
 *
 *  @return An initialized WOWZStatus object.
 */
+ (nonnull instancetype) statusWithStateAndError:(WOWZState)aState aError:(nonnull NSError *)aError;

/*!
 *  Returns a WOWZStatus object with a specified event.
 *
 *  @param event The WOWZEvent to use to initialize the object.
 *
 *  @return An initialized WOWZStatus object.
 */
+ (nonnull instancetype) statusWithEvent:(WOWZEvent)event;

/*!
 *  Returns a WOWZStatus object with a specified state and event.
 *
 *  @param aState The state to use to initialize the object.
 *  @param event The WOWZEvent to use to initialize the object.
 *
 *  @return An initialized WOWZStatus object.
 */
+ (nonnull instancetype) statusWithState:(WOWZState)aState event:(WOWZEvent)event;

#pragma mark - Instance Methods

/*!
 *  Initializes a WOWZStatus object with a specified state.
 *
 *  @param aState The state to use to initialize the object.
 *
 *  @return An initialized WOWZStatus object.
 */
- (nonnull instancetype) initWithState:(WOWZState)aState;

/*!
 *  Initializes a WOWZStatus object with a specified state and error.
 *
 *  @param aState The state to use to initialize the object.
 *  @param aError The error to use to initialize the object.
 *
 *  @return An initialized WOWZStatus object.
 */
- (nonnull instancetype) initWithStateAndError:(WOWZState)aState aError:(nonnull NSError *)aError;

/*!
 *  Initializes a WOWZStatus object with a specified event.
 *
 *  @param event The WOWZEvent to use to initialize the object.
 *
 *  @return An initialized WOWZStatus object.
 */
- (nonnull instancetype) initWithEvent:(WOWZEvent)event;

/*!
 *  Initializes a WOWZStatus object with a specified state and event.
 *
 *  @param aState The state to use to initialize the object.
 *  @param event The WOWZEvent to use to initialize the object.
 *
 *  @return An initialized WZStatus object.
 */
- (nonnull instancetype) initWithState:(WOWZState)aState event:(WOWZEvent)event;

/*!
 *  Reinitializes a WOWZStatus object, clearing all errors, events, and data values and setting the state to WOWZStateIdle.
 */
- (void) resetStatus;

/*!
 *  Reinitializes a WOWZStatus object, clearing all errors, events, and data values and setting the state to the specified value.
 *
 *  @param aState The state to use to initialize the object.
 */
- (void) resetStatusWithState:(WOWZState)aState;

/*!
 *  See if the state equals WOWZStateIdle.
 *
 *  @return True if the state is WOWZStateIdle; false otherwise.
 */
@property (readonly, nonatomic) BOOL isIdle;

/*!
 *  See if the state equals WOWZStateStarting.
 *`
 *  @return True if the state is WOWZStateStarting; false otherwise.
 */
@property (readonly, nonatomic) BOOL isStarting;

/*!
 *  See if the state equals WOWZStateReady.
 *
 *  @return True if the state is WOWZStateReady; false otherwise.
 */
@property (readonly, nonatomic) BOOL isReady;

/*!
 *  See if the state equals WOWZStateRunning.
 *
 *  @return True if the state is WOWZStateRunning; false otherwise.
 */
@property (readonly, nonatomic) BOOL isRunning;

/*!
 *  See if the state equals WOWZStateStopping.
 *
 *  @return True if the state is WOWZStateStopping; false otherwise.
 */
@property (readonly, nonatomic) BOOL isStopping;

/*!
 *  See if the error is non-null.
 *
 *  @return True if the error is non-null; false otherwise.
 */
@property (readonly, nonatomic) BOOL hasError;

@end
