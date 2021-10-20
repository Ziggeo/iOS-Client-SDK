//
//  ZiggeoUploadingHandler.h
//
//  Copyright (c) 2021 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ZiggeoApplication.h"

@interface ZiggeoUploadingHandler : NSObject

- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo;
- (void)getListWithType:(Media_Type)type
                   data:(NSDictionary *)data
               callback:(void (^)(NSArray *jsonArray, NSError *error))callback;
- (void)uploadWithType:(Media_Type)type
                  Path:(NSString *)path
                  Data:(NSDictionary *)data;
- (void)uploadWithType:(Media_Type)type
                  Path:(NSString *)path
                  Data:(NSDictionary *)data
              Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
              Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
       ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;
- (void)uploadUrlWithType:(Media_Type)type
                    Path:(NSString *)path
                     Data:(NSDictionary *)data
                 Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                 Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
          ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;
- (void)updateWithType:(Media_Type)type
                 Token:(NSString *)token
                  Path:(NSString *)path
              Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
              Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
       ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;
- (void)deleteWithType:(Media_Type)type
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
- (void)cancelRequest;
- (void)getOriginalStreamDescriptionForVideoByToken:(NSString *)token
                                           Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;

@end
