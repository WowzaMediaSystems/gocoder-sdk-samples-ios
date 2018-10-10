//
//  WSCTokenProcessor.h
//  GoCoder
//
//  Created by Barry Owen on 2/9/15.
//  © 2015 – 2018 Wowza Media Systems, LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "WowzaConfig.h"
#import <UIKit/UIKit.h>


// Wowza Cloud API Key

//#if TESTING
#define             QA_WSC_API_TRANSCODER_URL          @"https://api-qa.cloud.wowza.com/api/v1/token/transcoders/"
#define             QA_WSC_API_KEANU_STREAM_TARGET_URL @"https://api-qa.cloud.wowza.com/api/v2/token/stream_targets/"
#define             QA_WSC_API_KEY                     @"TQ8tzMv7CJxTGtewponWcygMBK99nlQhMgV11mU9I5mlc4Ar0OmJYHLQv8Ab335c"
//#else
#define             WSC_API_TRANSCODER_URL          @"https://api.cloud.wowza.com/api/v1/token/transcoders/"
#define             WSC_API_KEANU_STREAM_TARGET_URL @"https://api.cloud.wowza.com/api/v2/token/stream_targets/"
#define             WSC_API_KEY                     @"AO6vpvI1KAQEcfiQdPtF62uYuiQZqmExYA4LKkNCaJ5ae09B4r9St1DdyHgEQFA8"
//#endif

/*
host = api.cloud.wowza.com
api-key=M1sB9y6HdV96rQtBbci7FMNgjxThcNZvvzGJwAMs2cHtH4pvFvXruOsEe5Pw352c
if code is 7 chars and ends in q
host = api-qa.cloud.wowza.com
api-key =TQ8tzMv7CJxTGtewponWcygMBK99nlQhMgV11mU9I5mlc4Ar0OmJYHLQv8Ab335c
if code is  7 chars and ends in s
host = api-staging.cloud.wowza.com
api-key = A6vjuplTCyzirY0wQSRn11cIsEeajwi9dBmcxrGWLKQ9QGAHtratPk6H4NLR54Xq
*/

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

@property (nonatomic, unsafe_unretained) id <WSCTokenProcessorDelegate> delegate;

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




