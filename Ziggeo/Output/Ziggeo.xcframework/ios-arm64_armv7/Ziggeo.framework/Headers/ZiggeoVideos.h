//
//  ZiggeoVideos.h
//
//  Copyright (c) 2021 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
@import UIKit;


@protocol ZiggeoUploadDelegate <NSObject>

@optional
- (void)preparingToUploadWithPath:(NSString *)sourcePath;
@optional
- (void)preparingToUploadWithPath:(NSString *)sourcePath token:(NSString *)token streamToken:(NSString *)streamToken;
@optional
- (void)failedToUploadWithPath:(NSString *)sourcePath;
@optional
- (void)uploadStartedWithPath:(NSString *)sourcePath token:(NSString *)token streamToken:(NSString *)streamToken backgroundTask:(NSURLSessionTask *)uploadingTask;
@optional
- (void)uploadProgressForPath:(NSString *)sourcePath token:(NSString *)token streamToken:(NSString *)streamToken totalBytesSent:(int)bytesSent totalBytesExpectedToSend:(int)totalBytes;
@optional
- (void)uploadCompletedForPath:(NSString *)sourcePath token:(NSString *)token streamToken:(NSString *)streamToken withResponse:(NSURLResponse *)response error:(NSError *)error json:(NSDictionary *)json;
@optional
- (void)deleteWithToken:(NSString *)token streamToken:(NSString *)streamToken withResponse:(NSURLResponse *)response error:(NSError *)error json:(NSDictionary *)json;

@end



@interface ZiggeoVideos : NSObject{
    Ziggeo *_application;
}

@property (weak) id<ZiggeoUploadDelegate> uploadDelegate;

- (id)initWithApplication:(Ziggeo *)application_;

- (NSString *)getVideoUrlWithVideoToken:(NSString *)videoToken;

- (void)getVideos:(void (^)(NSArray *jsonArray, NSError *error))callback;

- (void)uploadVideoWithPath:(NSString *)path;

- (void)uploadVideoWithPath:(NSString *)path
                   Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                   Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
            ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;

- (void)updateVideoWithPath:(NSString *)path
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

@end
