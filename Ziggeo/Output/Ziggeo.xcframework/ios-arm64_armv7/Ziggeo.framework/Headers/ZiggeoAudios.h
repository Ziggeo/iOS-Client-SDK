//
//  ZiggeoAudios.h
//
//  Copyright (c) 2021 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
#import "ZiggeoVideos.h"
@import UIKit;


@interface ZiggeoAudios : NSObject{
    Ziggeo *_application;
}

@property (weak) id<ZiggeoUploadDelegate> uploadDelegate;

- (id)initWithApplication:(Ziggeo *)application_;

- (NSString *)getAudioUrl:(NSString *)audioToken;

- (void)getAudios:(void (^)(NSArray *jsonArray, NSError *error))callback;

- (void)uploadAudioWithPath:(NSString *)path;

- (void)uploadAudioWithPath:(NSString *)path
                   Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                   Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
            ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;

- (void)updateAudioWithPath:(NSString *)path
                 AudioToken:(NSString *)audioToken
                   Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                   Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
            ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;

- (void)deleteAudioByToken:(NSString *)audioToken
                  Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;

- (void)downloadAudioWithToken:(NSString *)audioToken
                      Callback:(void (^)(NSString *filePath))callback;

@end
