//
//  ZiggeoUploadingHandler.h
//
//  Copyright (c) 2021 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ZiggeoApplication.h"

@interface ZiggeoUploadingHandler : NSObject

- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo;

- (NSURLSessionTask *)getListWithType:(Media_Type)type
                                 data:(NSDictionary *)data
                             callback:(void (^)(NSArray *jsonArray, NSError *error))callback;

- (NSURLSessionTask *)uploadWithType:(Media_Type)type
                                Path:(NSString *)path
                                Data:(NSDictionary *)data;

- (NSURLSessionTask *)uploadWithType:(Media_Type)type
                                Path:(NSString *)path
                                Data:(NSDictionary *)data
                            Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                            Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
                     ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;

- (NSURLSessionTask *)uploadUrlWithType:(Media_Type)type
                                   Path:(NSString *)path
                                   Data:(NSDictionary *)data
                               Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                               Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
                        ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;

- (NSURLSessionTask *)updateWithType:(Media_Type)type
                               Token:(NSString *)token
                         StreamToken:(NSString *)streamToken
                                Data:(NSDictionary *)data
                            Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;

- (NSURLSessionTask *)deleteWithType:(Media_Type)type
                               Token:(NSString *)token
                            Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;

- (void)downloadWithType:(Media_Type)type
                   Token:(NSString *)token
                Callback:(void (^)(NSString *filePath))callback;

- (void)uploadCompletedWithType:(Media_Type)type
                           Path:(NSString *)path
                          token:(NSString *)token
                    streamToken:(NSString *)streamToken
              confirmJsonObject:(NSDictionary *)confirmJsonObject
                confirmResponse:(NSURLResponse *)confirmResponse
                   confirmError:(NSError *)confirmError;

- (void)cancelUpload:(NSString *)path :(bool)delete_file;

- (void)getOriginalStreamDescriptionForVideoByToken:(NSString *)token
                                           Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;

@end
