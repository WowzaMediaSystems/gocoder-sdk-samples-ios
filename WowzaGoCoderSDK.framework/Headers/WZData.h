//
//  WZData.h
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

@class WZDataMap;
@class WZDataList;


/*!
 *  @typedef WZDataType
 *  @constant WZDataTypeNull A Null value (NSNull)
 *  @constant WZDataTypeString A string (NSString).
 *  @constant WZDataTypeBoolean A boolean (BOOL).
 *  @constant WZDataTypeDate A date (NSDate).
 *  @constant WZDataTypeInteger An integer (NSInteger).
 *  @constant WZDataTypeFloat A float (Float).
 *  @constant WZDataTypeDouble A double (Double).
 *  @constant WZDataTypeMap A WZDataMap.
 *  @constant WZDataTypeList A WZDataList.
 *  @discussion The allowed types of a WZDataItem.
 */
typedef NS_ENUM(NSUInteger, WZDataType) {
    WZDataTypeNull,
    WZDataTypeString,
    WZDataTypeBoolean,
    WZDataTypeDate,
    WZDataTypeInteger,
    WZDataTypeFloat,
    WZDataTypeDouble,
    WZDataTypeMap,
    WZDataTypeList
};

/*!
 *  @typedef WZDataCallback
 *  @param result The result data returned from a server module function.
 *  @param isError whether the server module function returned an error.
 *  @discussion This is the callback that a client would provide when calling
 *  a Wowza server module function.
 */
typedef void (^WZDataCallback)( WZDataMap * _Nullable result, BOOL isError);

/*!
 @class WZDataItem
 @discussion The WZDataItem class provides an interface encapsulating the various data items that represent server metadata that is sent and received by GoCoder.
 */
@interface WZDataItem : NSObject

/*!
 *  The type of this data item.
 */
@property (nonatomic, assign, readonly) WZDataType type;

#pragma mark - Class Methods

/*!
 *  Creates a new WZDataItem of type WZDataTypeInteger
 *
 *  @param value the integer value with which to initialize the item
 *
 *  @return An instance of WZDataItem
 */
+ (nonnull instancetype) itemWithInteger:(NSInteger)value;

/*!
 *  Creates a new WZDataItem of type WZDataTypeDouble
 *
 *  @param value the double value with which to initialize the item
 *
 *  @return An instance of WZDataItem
 */
+ (nonnull instancetype) itemWithDouble:(double)value;

/*!
 *  Creates a new WZDataItem of type WZDataTypeFloat
 *
 *  @param value the float value with which to initialize the item
 *
 *  @return An instance of WZDataItem
 */
+ (nonnull instancetype) itemWithFloat:(float)value;

/*!
 *  Creates a new WZDataItem of type WZDataTypeBool
 *
 *  @param value the bool value with which to initialize the item
 *
 *  @return An instance of WZDataItem
 */
+ (nonnull instancetype) itemWithBool:(BOOL)value;

/*!
 *  Creates a new WZDataItem of type WZDataTypeString
 *
 *  @param value the string value with which to initialize the item
 *
 *  @return An instance of WZDataItem
 */
+ (nonnull instancetype) itemWithString:(nonnull NSString *)value;

/*!
 *  Creates a new WZDataItem of type WZDataTypeDate
 *
 *  @param value the date value with which to initialize the item
 *
 *  @return An instance of WZDataItem
 */
+ (nonnull instancetype) itemWithDate:(nonnull NSDate *)value;

#pragma mark - Instance Methods

/*!
 *  Initialize a WZDataItem
 *
 *  @return An instance of WZDataItem of type WZDataTypeNull
 */
- (nonnull instancetype) init;

/*!
 *  Get the integer value of the WZDataItem
 *
 *  @return the integer value of the WZDataItem, or 0 if the item is not of type WZDataTypeInteger
 */
- (NSInteger) integerValue;

/*!
 *  Get the double value of the WZDataItem
 *
 *  @return the double value of the WZDataItem, or 0 if the item is not of type WZDataTypeDouble
 */
- (double) doubleValue;

/*!
 *  Get the float value of the WZDataItem
 *
 *  @return the float value of the WZDataItem, or 0 if the item is not of type WZDataTypeFloat
 */
- (float) floatValue;

/*!
 *  Get the bool value of the WZDataItem
 *
 *  @return the bool value of the WZDataItem, or 0 if the item is not of type WZDataTypeBoolean
 */
- (BOOL) boolValue;

/*!
 *  Get the string value of the WZDataItem
 *
 *  @return the string value of the WZDataItem, or nil if the item is not of type WZDataTypeString
 */
- (nullable NSString *)stringValue;

/*!
 *  Get the date value of the WZDataItem
 *
 *  @return the date value of the WZDataItem, or nil if the item is not of type WZDataTypeDate
 */
- (nullable NSDate *)dateValue;

/*!
 *  Get the map value of the WZDataItem
 *
 *  @return the map value of the WZDataItem, or nil if the item is not of type WZDataTypeMap
 */
- (nullable WZDataMap *)mapValue;

/*!
 *  Get the list value of the WZDataItem
 *
 *  @return the list value of the WZDataItem, or nil if the item is not of type WZDataTypeList
 */
- (nullable WZDataList *)listValue;

@end



/*!
 @class WZDataMap
 @discussion The WZDataMap class provides an interface encapsulating a map (or dictionary) of items that represent server metadata that is sent and received by GoCoder.
 */
@interface WZDataMap : WZDataItem

/*!
 *  The underlying NSMutableDictionary that stores the items in the map.
 */
@property (nonatomic, strong, readonly, nullable) NSMutableDictionary<NSString*, WZDataItem*> *data;

#pragma mark - Class Methods

/*!
 *  Creates a new WZDataMap and copies the items in dictionary to it's internal data map
 *
 *  @param dictionary the dictionary of WZDataItems that the caller wishes to initialize the WZDataMap with.
 *
 *  @return An instance of WZDataMap
 */
+ (nonnull instancetype) dataMapWithDictionary:(nonnull NSDictionary<NSString*, WZDataItem*> *)dictionary;


#pragma mark - Instance Methods

/*!
 *  Initialize a new WZDataMap with no items
 *
 *  @return An instance of WZDataMap
 */
- (nonnull instancetype) init;

/*!
 *  Initialize a new WZDataMap and copies the items in dictionary to it's internal data map
 *
 *  @param dictionary the dictionary of WZDataItems that the caller wishes to initialize the WZDataMap with.
 *
 *  @return An instance of WZDataMap
 */
- (nonnull instancetype) initWithDictionary:(nonnull NSDictionary<NSString*, WZDataItem*> *)dictionary;

/*!
 *  Add a integer (which will be converted to a WZDataItem) with given key to the internal map
 *
 *  @param value the integer value to add
 *  @param key the unique key for the new integer value
 */
- (void) setInteger:(NSInteger)value forKey:(nonnull NSString *)key;

/*!
 *  Add a double (which will be converted to a WZDataItem) with given key to the internal map
 *
 *  @param value the double value to add
 *  @param key the unique key for the new double value
 */
- (void) setDouble:(double)value forKey:(nonnull NSString *)key;

/*!
 *  Add a float (which will be converted to a WZDataItem) with given key to the internal map
 *
 *  @param value the float value to add
 *  @param key the unique key for the new float value
 */
- (void) setFloat:(float)value forKey:(nonnull NSString *)key;

/*!
 *  Add a bool (which will be converted to a WZDataItem) with given key to the internal map
 *
 *  @param value the bool value to add
 *  @param key the unique key for the new bool value
 */
- (void) setBool:(BOOL)value forKey:(nonnull NSString *)key;

/*!
 *  Add a string (which will be converted to a WZDataItem) with given key to the internal map
 *
 *  @param value the string value to add
 *  @param key the unique key for the new string value
 */
- (void) setString:(nullable NSString *)value forKey:(nonnull NSString *)key;

/*!
 *  Add a date (which will be converted to a WZDataItem) with given key to the internal map
 *
 *  @param value the date value to add
 *  @param key the unique key for the new date value
 */
- (void) setDate:(nullable NSDate *)value forKey:(nonnull NSString *)key;

/*!
 *  Add a WZDataItem with given key to the internal map
 *
 *  @param value the WZDataItem value to add
 *  @param key the unique key for the new WZDataItem value
 */
- (void) setItem:(nullable WZDataItem *)value forKey:(nonnull NSString *)key;

/*!
 *  Add a WZDataMap with given key to the internal map
 *
 *  @param value the WZDataMap value to add
 *  @param key the unique key for the new WZDataMap value
 */
- (void) setMap:(nullable WZDataMap *)value forKey:(nonnull NSString *)key;

/*!
 *  Add a WZDataList with given key to the internal map
 *
 *  @param value the WZDataList value to add
 *  @param key the unique key for the new WZDataList value
 */
- (void) setList:(nullable WZDataList *)value forKey:(nonnull NSString *)key;

/*!
 *  Remove an item from the internal map
 *
 *  @param key the key value to be removed
 */
- (void) remove:(nonnull NSString *)key;

@end

/*!
 @class WZDataList
 @discussion The WZDataList class provides an interface encapsulating a list (or array) of items that represent server metadata that is sent and received by GoCoder.
 */
@interface WZDataList : WZDataItem

/*!
 *  The underlying NSMutableArray that stores the items in the list.
 */
@property (nonatomic, strong, readonly, nullable) NSMutableArray<WZDataItem *> *elements;

#pragma mark - Class Methods

/*!
 *  Creates a new WZDataList and copies the items in array to it's internal list
 *
 *  @param array the array of WZDataItems that the caller wishes to initialize the WZDataList with.
 *
 *  @return An instance of WZDataList
 */
+ (nullable instancetype) dataListWithArray:(nonnull NSArray<WZDataItem *> *)array;

/*!
 *  Get the maximum size (number of elements) allowed in a WZDataList
 *
 *  @return an NSUInteger expressing the maximum size (number of elements) allowed in a WZDataList
 */
+ (NSUInteger) maximumSize;


#pragma mark - Instance Methods

/*!
 *  Initialize a new WZDataList with no elements
 *
 *  @return An instance of WZDataList
 */
- (nonnull instancetype) init;

/*!
 *  Initialize a new WZDataList and copy the items in array to it's internal list
 *
 *  @param array the array of WZDataItems that the caller wishes to initialize the WZDataList with.
 *
 *  @return An instance of WZDataList
 */
- (nullable instancetype) initWithArray:(nonnull NSArray<WZDataItem *> *)array;

/*!
 *  Add a integer (which will be converted to a WZDataItem) to the internal list
 *
 *  @param value the integer value to add
 */
- (void) addInteger:(NSInteger)value;

/*!
 *  Add a double (which will be converted to a WZDataItem) to the internal list
 *
 *  @param value the double value to add
 */
- (void) addDouble:(double)value;

/*!
 *  Add a float (which will be converted to a WZDataItem) to the internal list
 *
 *  @param value the float value to add
 */
- (void) addFloat:(float)value;

/*!
 *  Add a bool (which will be converted to a WZDataItem) to the internal list
 *
 *  @param value the bool value to add
 */
- (void) addBool:(BOOL)value;

/*!
 *  Add a string (which will be converted to a WZDataItem) to the internal list
 *
 *  @param value the string value to add
 */
- (void) addString:(nonnull NSString *)value;

/*!
 *  Add a date (which will be converted to a WZDataItem) to the internal list
 *
 *  @param value the date value to add
 */
- (void) addDate:(nonnull NSDate *)value;

/*!
 *  Add a WZDataItem to the internal list
 *
 *  @param value the WZDataItem value to add
 */
- (void) addItem:(nonnull WZDataItem *)value;

/*!
 *  Add a WZDataMap to the internal list
 *
 *  @param value the WZDataMap value to add
 */
- (void) addMap:(nonnull WZDataMap *)value;

/*!
 *  Add a WZDataList to the internal list
 *
 *  @param value the WZDataList value to add
 */
- (void) addList:(nonnull WZDataList *)value;


@end

