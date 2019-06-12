//
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
#import "WowzaConfig.h"
#import <UIKit/UIKit.h>

@protocol WSCTokenProcessorDelegate <NSObject>

@required

- (void)WSCTokenProcessorFailed:(NSString *)failedMessage;
- (void)WSCTokenProcessorSucceeded:(NSString *)state;

@end

@interface WSCTokenProcessor : NSObject 
{
    NSURLConnection *tokenConnection;
    NSURLConnection *transcoderConnection;
    NSString *longToken;
    NSString *shortToken;
    NSString *endpointURL;
    NSMutableData *finalData;
    bool isQA;
		WowzaConfig *config;
}

@property (nonatomic, weak) id <WSCTokenProcessorDelegate> delegate;

- (void) populateProfile:(WowzaConfig *)config fromWSCToken:(NSString *)token;
- (void) getLongToken;
- (void) getTranscoder;
- (void) updateBroadcastProfile:(NSDictionary *)transcoderData;


- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data;
- (BOOL)isULLStreamTargetEnabled:(NSDictionary*) transcoderData;
- (void)connectionDidFinishLoading:(NSURLConnection *)connection;
- (void)connection:(NSURLConnection *)connection willSendRequestForAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge;
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error;

@end




