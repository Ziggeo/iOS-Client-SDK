//
//  ZiggeoImages.h
//
//  Copyright (c) 2021 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
#import "ZiggeoConfig.h"
@import UIKit;


@interface ZiggeoImages : NSObject{
    Ziggeo* _application;
}

@property (weak) id<ZiggeoUploadDelegate> uploadDelegate;

- (id)initWithApplication:(Ziggeo*)application_;

- (NSString *)getImageUrl:(NSString *)imageToken;

- (void)getImages:(void (^)(NSArray* jsonArray, NSError* error))callback;

- (void)uploadImageWithFile:(UIImage *)imageFile;

- (void)uploadImageWithFile:(UIImage *)imageFile
                   Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                   Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
            ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;

- (void)uploadImageWithPath:(NSString *)path;

- (void)uploadImageWithPath:(NSString *)path
                   Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                   Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
            ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;

- (void)updateImageWithPath:(NSString *)path
                 ImageToken:(NSString *)imageToken
                   Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                   Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
            ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;

- (void)deleteImageByToken:(NSString *)imageToken
                  Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;

- (void)downloadImageWithToken:(NSString *)imageToken
                      Callback:(void (^)(NSString *filePath))callback;

- (void)cancelRequest;

@end
