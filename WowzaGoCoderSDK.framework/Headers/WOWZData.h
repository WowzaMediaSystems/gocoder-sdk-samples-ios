//
//  WOWZData.h
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

@class WOWZDataMap;
@class WOWZDataList;


/*!
 *  @typedef WOWZDataType
 *  @constant WOWZDataTypeNull A null value (NSNull).
 *  @constant WOWZDataTypeString A string (NSString).
 *  @constant WOWZDataTypeBoolean A Boolean (BOOL).
 *  @constant WOWZDataTypeDate A date (NSDate).
 *  @constant WOWZDataTypeInteger An integer (NSInteger).
 *  @constant WOWZDataTypeFloat A float (Float).
 *  @constant WOWZDataTypeDouble A double (Double).
 *  @constant WOWZDataTypeMap A WOWZDataMap.
 *  @constant WOWZDataTypeList A WOWZDataList.
 *  @discussion A collection of constants that represent the supported types of a WOWZDataItem.
 */
typedef NS_ENUM(NSUInteger, WOWZDataType) {
    WOWZDataTypeNull,
    WOWZDataTypeString,
    WOWZDataTypeBoolean,
    WOWZDataTypeDate,
    WOWZDataTypeInteger,
    WOWZDataTypeFloat,
    WOWZDataTypeDouble,
    WOWZDataTypeMap,
    WOWZDataTypeList
};

/*!
 *  @typedef WOWZDataCallback
 *  @param result The data returned from a Wowza Streaming Engine server module function.
 *  @param isError Indicates whether the server module function returned an error.
 *  @discussion The callback that a client provides when calling a Wowza Streaming Engine server module function.
 */
typedef void (^WOWZDataCallback)( WOWZDataMap * _Nullable result, BOOL isError);

/*!
 @class WOWZDataItem
 @discussion The WOWZDataItem class provides an interface for data items that represent server metadata that's sent and received by GoCoder.
 */
@interface WOWZDataItem : NSObject <NSMutableCopying, NSCopying, NSCoding>

/*!
 *  The data item's type.
 */
@property (nonatomic, assign, readonly) WOWZDataType type;

#pragma mark - Class Methods

/*!
 *  Creates a WOWZDataItem whose type is WOWZDataTypeInteger.
 *
 *  @param value The integer value to use to initialize the item.
 *
 *  @return An instance of WOWZDataItem.
 */
+ (nonnull instancetype) itemWithInteger:(NSInteger)value;

/*!
 *  Creates a WOWZDataItem whose type is WOWZDataTypeDouble.
 *
 *  @param value The double value to use to initialize the item.
 *
 *  @return An instance of WOWZDataItem.
 */
+ (nonnull instancetype) itemWithDouble:(double)value;

/*!
 *  Creates a WOWZDataItem whose type is WOWZDataTypeFloat.
 *
 *  @param value The float value to use to initialize the item.
 *
 *  @return An instance of WOWZDataItem.
 */
+ (nonnull instancetype) itemWithFloat:(float)value;

/*!
 *  Creates a WOWZDataItem whose type is WOWZDataTypeBool.
 *
 *  @param value The Boolean value to use to initialize the item.
 *
 *  @return An instance of WOWZDataItem.
 */
+ (nonnull instancetype) itemWithBool:(BOOL)value;

/*!
 *  Creates a WOWZDataItem whose type is WOWZDataTypeString.
 *
 *  @param value The string value to use to initialize the item.
 *
 *  @return An instance of WOWZDataItem.
 */
+ (nonnull instancetype) itemWithString:(nonnull NSString *)value;

/*!
 *  Creates a WOWZDataItem whose type is WOWZDataTypeDate.
 *
 *  @param value The date value to use to initialize the item.
 *
 *  @return An instance of WOWZDataItem.
 */
+ (nonnull instancetype) itemWithDate:(nonnull NSDate *)value;

#pragma mark - Instance Methods

/*!
 *  Initializes a WOWZDataItem.
 *
 *  @return An instance of WOWZDataItem of the type WOWZDataTypeNull.
 */
- (nonnull instancetype) init;

/*!
 *  Gets the integer value of the WOWZDataItem.
 *
 *  @return The integer value of the WOWZDataItem, or 0 if the item isn't of the type WOWZDataTypeInteger.
 */
- (NSInteger) integerValue;

/*!
 *  Gets the double value of the WOWZDataItem.
 *
 *  @return The double value of the WOWZDataItem, or 0 if the item isn't of the type WOWZDataTypeDouble.
 */
- (double) doubleValue;

/*!
 *  Gets the float value of the WOWZDataItem.
 *
 *  @return The float value of the WOWZDataItem, or 0 if the item isn't of the type WOWZDataTypeFloat.
 */
- (float) floatValue;

/*!
 *  Gets the Boolean value of the WOWZDataItem.
 *
 *  @return The Boolean value of the WOWZDataItem, or 0 if the item isn't of the type WOWZDataTypeBoolean.
 */
- (BOOL) boolValue;

/*!
 *  Gets the string value of the WOWZDataItem.
 *
 *  @return The string value of the WOWZDataItem, or nil if the item isn't of the type WOWZDataTypeString.
 */
- (nullable NSString *)stringValue;

/*!
 *  Gets the date value of the WOWZDataItem.
 *
 *  @return The date value of the WOWZDataItem, or nil if the item isn't of the type WOWZDataTypeDate.
 */
- (nullable NSDate *)dateValue;

/*!
 *  Gets the map value of the WOWZDataItem.
 *
 *  @return The map value of the WOWZDataItem, or nil if the item isn't of the type WOWZDataTypeMap.
 */
- (nullable WOWZDataMap *)mapValue;

/*!
 *  Gets the list value of the WOWZDataItem.
 *
 *  @return The list value of the WOWZDataItem, or nil if the item isn't of the type WOWZDataTypeList.
 */
- (nullable WOWZDataList *)listValue;

@end



/*!
 @class WOWZDataMap
 @discussion The WOWZDataMap class provides an interface for a map or dictionary of items that represent server metadata that's sent and received by GoCoder.
 */
@interface WOWZDataMap : WOWZDataItem

/*!
 *  The underlying NSMutableDictionary that stores the items in the map.
 */
@property (nonatomic, strong, readonly, nullable) NSMutableDictionary<NSString*, WOWZDataItem*> *data;

#pragma mark - Class Methods

/*!
 *  Creates a WOWZDataMap that copies the items in the specified dictionary to its internal data map.
 *
 *  @param dictionary The dictionary of WOWZDataItems that the caller should use to initialize the WOWZDataMap.
 *
 *  @return An instance of WOWZDataMap.
 */
+ (nonnull instancetype) dataMapWithDictionary:(nonnull NSDictionary<NSString*, WOWZDataItem*> *)dictionary;


#pragma mark - Instance Methods

/*!
 *  Initializes an empty WOWZDataMap.
 *
 *  @return An instance of an empty WOWZDataMap.
 */
- (nonnull instancetype) init;

/*!
 *  Initializes a WOWZDataMap that copies the items in the specified dictionary to its internal data map.
 *
 *  @param dictionary The dictionary of WOWZDataItems that the caller should use to initialize the WOWZDataMap.
 *
 *  @return An instance of WOWZDataMap.
 */
- (nonnull instancetype) initWithDictionary:(nonnull NSDictionary<NSString*, WOWZDataItem*> *)dictionary;

/*!
 *  Adds an integer, which will be converted to a WOWZDataItem, with the specified key to the internal map.
 *
 *  @param value The integer value to add.
 *  @param key The unique key for the new integer value.
 */
- (void) setInteger:(NSInteger)value forKey:(nonnull NSString *)key;

/*!
 *  Adds a double, which will be converted to a WOWZDataItem, with the specified key to the internal map.
 *
 *  @param value The double value to add.
 *  @param key The unique key for the new double value.
 */
- (void) setDouble:(double)value forKey:(nonnull NSString *)key;

/*!
 *  Adds a float, which will be converted to a WOWZDataItem, with the specified key to the internal map.
 *
 *  @param value The float value to add.
 *  @param key The unique key for the new float value.
 */
- (void) setFloat:(float)value forKey:(nonnull NSString *)key;

/*!
 *  Adds a Boolean, which will be converted to a WOWZDataItem, with the specified key to the internal map.
 *
 *  @param value The Boolean value to add.
 *  @param key The unique key for the new Boolean value.
 */
- (void) setBool:(BOOL)value forKey:(nonnull NSString *)key;

/*!
 *  Adds a string, which will be converted to a WOWZDataItem, with the specified key to the internal map.
 *
 *  @param value The string value to add.
 *  @param key The unique key for the new string value.
 */
- (void) setString:(nullable NSString *)value forKey:(nonnull NSString *)key;

/*!
 *  Adds a date, which will be converted to a WOWZDataItem, with the specified key to the internal map.
 *
 *  @param value The date value to add.
 *  @param key The unique key for the new date value.
 */
- (void) setDate:(nullable NSDate *)value forKey:(nonnull NSString *)key;

/*!
 *  Adds a WOWZDataItem with the specified key to the internal map.
 *
 *  @param value The WOWZDataItem value to add.
 *  @param key The unique key for the new WOWZDataItem value.
 */
- (void) setItem:(nullable WOWZDataItem *)value forKey:(nonnull NSString *)key;

/*!
 *  Adds a WOWZDataMap with the specified key to the internal map.
 *
 *  @param value The WOWZDataMap value to add.
 *  @param key The unique key for the new WOWZDataMap value.
 */
- (void) setMap:(nullable WOWZDataMap *)value forKey:(nonnull NSString *)key;

/*!
 *  Adds a WOWZDataList with the specified key to the internal map.
 *
 *  @param value The WOWZDataList value to add.
 *  @param key The unique key for the new WOWZDataList value.
 */
- (void) setList:(nullable WOWZDataList *)value forKey:(nonnull NSString *)key;

/*!
 *  Removes an item from the internal map.
 *
 *  @param key The key value to remove.
 */
- (void) remove:(nonnull NSString *)key;

@end

/*!
 @class WOWZDataList
 @discussion The WOWZDataList class provides an interface for a list or an array of items that represent server metadata that's sent and received by GoCoder.
 */
@interface WOWZDataList : WOWZDataItem

/*!
 *  The underlying NSMutableArray that stores the items in the list.
 */
@property (nonatomic, strong, readonly, nullable) NSMutableArray<WOWZDataItem *> *elements;

#pragma mark - Class Methods

/*!
 *  Creates a WOWZDataList that copies items from the specified array to its internal list.
 *
 *  @param array The array of WOWZDataItems that the caller should use to initialize the WOWZDataList.
 *
 *  @return An instance of WOWZDataList with the specified array of items.
 */
+ (nullable instancetype) dataListWithArray:(nonnull NSArray<WOWZDataItem *> *)array;

/*!
 *  Gets the maximum number of elements allowed in a WOWZDataList.
 *
 *  @return An NSUInteger that expresses the total number of elements allowed in a WOWZDataList.
 */
+ (NSUInteger) maximumSize;


#pragma mark - Instance Methods

/*!
 *  Initializes an empty WOWZDataList.
 *
 *  @return An instance of an empty WOWZDataList.
 */
- (nonnull instancetype) init;

/*!
 *  Initializes a WOWZDataList that copies items from the specified array to its internal list.
 *
 *  @param array The array of WOWZDataItems the caller should use to initialize the WOWZDataList.
 *
 *  @return An instance of WOWZDataList with the specified array of items.
 */
- (nullable instancetype) initWithArray:(nonnull NSArray<WOWZDataItem *> *)array;

/*!
 *  Adds an integer, which will be converted to a WOWZDataItem, to the internal list.
 *
 *  @param value The integer value to add.
 */
- (void) addInteger:(NSInteger)value;

/*!
 *  Adds a double, which will be converted to a WOWZDataItem, to the internal list.
 *
 *  @param value The double value to add.
 */
- (void) addDouble:(double)value;

/*!
 *  Adds a float, which will be converted to a WOWZDataItem, to the internal list.
 *
 *  @param value The float value to add.
 */
- (void) addFloat:(float)value;

/*!
 *  Adds a Boolean, which will be converted to a WOWZDataItem, to the internal list.
 *
 *  @param value The Boolean value to add.
 */
- (void) addBool:(BOOL)value;

/*!
 *  Adds a string, which will be converted to a WOWZDataItem, to the internal list.
 *
 *  @param value The string value to add.
 */
- (void) addString:(nonnull NSString *)value;

/*!
 *  Adds a date, which will be converted to a WOWZDataItem, to the internal list.
 *
 *  @param value The date value to add.
 */
- (void) addDate:(nonnull NSDate *)value;

/*!
 *  Adds a WOWZDataItem to the internal list.
 *
 *  @param value The WOWZDataItem value to add.
 */
- (void) addItem:(nonnull WOWZDataItem *)value;

/*!
 *  Adds a WOWZDataMap to the internal list.
 *
 *  @param value The WOWZDataMap value to add.
 */
- (void) addMap:(nonnull WOWZDataMap *)value;

/*!
 *  Adds a WOWZDataList to the internal list.
 *
 *  @param value The WOWZDataList value to add.
 */
- (void) addList:(nonnull WOWZDataList *)value;


@end

