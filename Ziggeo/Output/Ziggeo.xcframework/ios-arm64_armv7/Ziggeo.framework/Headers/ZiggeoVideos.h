//
//  ZiggeoVideos.h
//
//  Copyright (c) 2021 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
#import "ZiggeoConfig.h"
@import UIKit;


@interface ZiggeoVideos : NSObject{
    Ziggeo *_application;
}

@property (weak) id<ZiggeoUploadDelegate> uploadDelegate;

- (id)initWithApplication:(Ziggeo *)application_;

- (NSString *)getVideoUrlWithVideoToken:(NSString *)videoToken;

- (void)getVideos:(void (^)(NSArray *jsonArray, NSError *error))callback;

- (void)uploadVideoWithPath:(NSString *)path
                       Data:(NSDictionary *)data;

- (void)uploadVideoWithPath:(NSString *)path
                       Data:(NSDictionary *)data
                   Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                   Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
            ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;

- (void)updateVideoWithPath:(NSString *)path
                       Data:(NSDictionary *)data
                 VideoToken:(NSString *)videoToken
                StreamToken:(NSString *)streamToken
                   Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                   Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
            ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;

- (void)deleteVideoByToken:(NSString *)videoToken
               StreamToken:(NSString *)streamToken
                  Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;

- (void)downloadVideoWithToken:(NSString *)videoToken
                      Callback:(void (^)(NSString *filePath))callback;

- (void)getOriginalStreamDescriptionForVideoByToken:(NSString *)token
                                           Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;

- (void)getImageForVideoByToken:(NSString *)videoToken
                           Data:(NSDictionary *)params
                       Callback:(void (^)(UIImage *image, NSURLResponse *response, NSError *error))callback;

- (void)getImageForVideoByPath:(NSString*)path
                      Callback:(void (^)(UIImage* image, NSError* error))callback;

- (void)cancelRequest;

@end
