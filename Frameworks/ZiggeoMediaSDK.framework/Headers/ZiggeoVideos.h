//
//  ZiggeoVideos.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
#import "ContentModel.h"
@import UIKit;


@interface ZiggeoVideos : NSObject<NSFilePresenter> {
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

- (NSURLSessionTask *)get:(NSString *)token
                     Data:(NSDictionary *)data
                 Callback:(void (^)(ContentModel *content, NSURLResponse *response, NSError *error))callback;

- (void)download:(NSString *)token
        Callback:(void (^)(NSString *filePath))callback;

- (NSString *)getVideoUrl:(NSString *)token;

- (NSString *)getImageUrl:(NSString *)token;

- (NSURLSessionTask *)destroy:(NSString *)token
                     Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;

- (NSURLSessionTask *)update:(NSString *)token
                        Data:(NSDictionary *)data
                    Callback:(void (^)(ContentModel *content, NSURLResponse *response,  NSError *error))callback;

- (NSURLSessionTask *)update:(NSString *)token
                 ModelInJson:(NSString *)modelInJson
                    Callback:(void (^)(ContentModel *content, NSURLResponse *response,  NSError *error))callback;

- (void)startScreenRecorderWithAppGroup:(NSString *)appGroup
                     preferredExtension:(nonnull NSString *)preferredExtension;

- (void)setAppGroup:(NSString *)groupID;

@end
