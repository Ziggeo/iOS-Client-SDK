//
//  ZiggeoImages.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
#import "ContentModel.h"
#import "Image.h"
@import UIKit;


@interface ZiggeoImages : NSObject{
    Ziggeo *m_ziggeo;
}

- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo;
- (NSURLSessionTask *)index:(NSDictionary *)data
                   callback:(void (^)(NSArray *jsonArray, NSError *error))callback;
- (NSURLSessionTask *)index:(NSDictionary *)data
             stringCallback:(void (^)(NSString *string, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)create:(NSString *)file_path
                        data:(NSDictionary *)data
                    callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                    progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
             confirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;
- (NSURLSessionTask *)get:(NSString *)token
                     data:(NSDictionary *)data
                 callback:(void (^)(Image *content, NSURLResponse *response, NSError *error))callback;
- (void)download:(NSString *)token
        callback:(void (^)(NSString *filePath))callback;
- (NSString *)getImageUrl:(NSString *)token;
- (NSURLSessionTask *)destroy:(NSString *)token
                     callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)update:(NSString *)token
                        data:(NSDictionary *)data
                    callback:(void (^)(Image *content, NSURLResponse *response,  NSError *error))callback;
- (NSURLSessionTask *)update:(Image *)model
                    callback:(void (^)(Image *content, NSURLResponse *response,  NSError *error))callback;

@end
