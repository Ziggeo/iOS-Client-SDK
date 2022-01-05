//
//  ZiggeoAudios.h
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
@import UIKit;


@interface ZiggeoAudios : NSObject{
    Ziggeo *m_ziggeo;
}

- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo;

- (NSURLSessionTask *)index:(NSDictionary *)data
                   Callback:(void (^)(NSArray *jsonArray, NSError *error))callback;

- (NSURLSessionTask *)create:(NSString *)file_path
                        Data:(NSDictionary *)data
                    Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                    Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
             ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;

- (void)get:(NSString *)token Callback:(void (^)(NSString *filePath))callback;

- (NSString *)getAudioUrl:(NSString *)token;

- (NSURLSessionTask *)destroy:(NSString *)token
                     Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;

- (NSURLSessionTask *)update:(NSString *)token
                        Data:(NSDictionary *)data
                    Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response,  NSError *error))callback;

- (NSURLSessionTask *)update:(NSString *)token ModelInJson:(NSString *)modelInJson Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response,  NSError *error))callback;

@end
