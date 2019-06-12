//
//  WOWZLogger.h
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
#import "WowzaGoCoder.h"

/*!
 *  @class WOWZLogger
 *  @discussion The WOWZLogger class is the
 */
@interface WOWZLogger : NSObject


/*!
 *  @typedef WowzaGoCoderLogOutput
 *  @constant WowzaGoCoderLogOutputConsole Logs will be sent to the console.
 *  @constant WowzaGoCoderLogOutputFile Logs will be saved to the device.
 *  @constant WowzaGoCoderLogOutputAll Logs will be sent to the console and saved to the device.
 *  @discussion Settings for the log output perference for the GoCoder SDK.
 */
typedef NS_ENUM(NSUInteger,WowzaGoCoderLogOutput) {
    WowzaGoCoderLogOutputConsole = 0,
    WowzaGoCoderLogOutputFile,
    WowzaGoCoderLogOutputAll,
};


/*!
 *  Sends a message to the logger.
 *
 *  @param message Message sent to the logger.
 */
+(void) log:(nonnull NSString *)message;



/*!
 *  Sets the SDK log level for which flags to send to the output.
 *  Default: WowzaGoCoderLogLevelDefault
 *
 *  @param level The log level to use.
 */
+(void) setLogLevel:(WowzaGoCoderLogLevel)level;

/*!
 *  Sets the SDK log output preference.
 *  Default: WowzaGoCoderLogOutputConsole
 *
 *  @param output The log output destination to use.
 */
+(void) setLogOutput:(WowzaGoCoderLogOutput)output;

/*!
 *  Flush logs to disk.
 *  The SDK flushes all cached logs to disk.
 *
 */
+(void) flushLog;

/*!
 *  Delete all logs stored on the device.
 *  The SDK does not periodically delete any logs that have been created.
 *
 */
+(void) deleteLogFiles;

/*!
 *  Sets the maximum size the log file on the device disk can reach. The default is 10MB. Once the maximum size
 *  is reached, the contents of the log file are deleted and new log messages are stored using the same file until
 *  the end of the current 24-hour period. A new file is created each day using the current NSDate. Log files are
 *  stored on the device disk until deleted using deleteLogFiles. Log files are saved as readable .html files with
 *  the following naming convention: [applicationName]_[yyyy-mm-dd].html
 *
 *  @param bytes Maximum size in bytes. Size must be equal or greater than 1MB and not exceed 20MB. [ 1MB = 1*(1024*1024) ]
 */
+(void) setMaximumLogfileSize:(NSInteger)bytes;

/*!
 *  Returns the maximum file size in bytes.
 *
 *  @return  Maximum file size in bytes.
 */
+(NSInteger) getMaximumLogfileSize;


/*!
 *  Sets the threshold the log buffer must meet before log data is written to the device disk. Using a very low threshold may impact performance because of write operations.
 *  Default: 2MB
 *
 *  @param bytes Threshold size in bytes. Size must be greater or equal to 1MB and not exceed 20MB. [ 1MB = 1*(1024*1024) ]
 */
+(void) setFileThreshold:(NSInteger)bytes;

/*!
 *  Returns the size of the buffer threshold in bytes.
 *
 *  @return  Size of buffer in bytes.
 */
+(NSInteger) getFileThreshold;


@end
