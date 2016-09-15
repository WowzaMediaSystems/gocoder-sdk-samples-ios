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

typedef NS_ENUM(NSUInteger, WZData) {
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

@interface WZDataItem : NSObject

@property (nonatomic, assign, readonly) WZData type;

+ (nonnull instancetype) itemWithInteger:(NSInteger)value;
+ (nonnull instancetype) itemWithDouble:(double)value;
+ (nonnull instancetype) itemWithFloat:(float)value;
+ (nonnull instancetype) itemWithBool:(BOOL)value;
+ (nonnull instancetype) itemWithString:(nonnull NSString *)value;
+ (nonnull instancetype) itemWithDate:(nonnull NSDate *)value;

- (nonnull instancetype) init;

- (NSInteger) integerValue;
- (double) doubleValue;
- (float) floatValue;
- (BOOL) boolValue;
- (nullable NSString *)stringValue;
- (nullable NSDate *)dateValue;
- (nullable WZDataMap *)mapValue;
- (nullable WZDataList *)listValue;

@end

@interface WZDataMap : WZDataItem

@property (nonatomic, strong, readonly, nullable) NSMutableDictionary<NSString*, WZDataItem*> *data;

+ (nonnull instancetype) dataMapWithDictionary:(nonnull NSDictionary<NSString*, WZDataItem*> *)dictionary;

- (nonnull instancetype) init;
- (nonnull instancetype) initWithDictionary:(nonnull NSDictionary<NSString*, WZDataItem*> *)dictionary;

- (void) setInteger:(NSInteger)value forKey:(nonnull NSString *)key;
- (void) setDouble:(double)value forKey:(nonnull NSString *)key;
- (void) setFloat:(float)value forKey:(nonnull NSString *)key;
- (void) setBool:(BOOL)value forKey:(nonnull NSString *)key;
- (void) setString:(nullable NSString *)value forKey:(nonnull NSString *)key;
- (void) setDate:(nullable NSDate *)value forKey:(nonnull NSString *)key;

- (void) setItem:(nullable WZDataItem *)value forKey:(nonnull NSString *)key;

- (void) setMap:(nullable WZDataMap *)value forKey:(nonnull NSString *)key;
- (void) setList:(nullable WZDataList *)value forKey:(nonnull NSString *)key;

- (void) remove:(nonnull NSString *)key;

@end

@interface WZDataList : WZDataItem

@property (nonatomic, strong, readonly, nullable) NSMutableArray<WZDataItem *> *elements;

+ (nullable instancetype) dataListWithArray:(nonnull NSArray<WZDataItem *> *)array;
+ (NSUInteger) maximumSize;

- (nonnull instancetype) init;
- (nullable instancetype) initWithArray:(nonnull NSArray<WZDataItem *> *)array;

- (void) addInteger:(NSInteger)value;
- (void) addDouble:(double)value;
- (void) addFloat:(float)value;
- (void) addBool:(BOOL)value;
- (void) addString:(nonnull NSString *)value;
- (void) addDate:(nonnull NSDate *)value;

- (void) addItem:(nonnull WZDataItem *)value;

- (void) addMap:(nonnull WZDataMap *)value;
- (void) addList:(nonnull WZDataList *)list;


@end

