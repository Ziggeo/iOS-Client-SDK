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
                   callback:(void (^)(NSArray *jsonArray, NSError *error))callback;
- (NSURLSessionTask *)create:(NSString *)file_path
                        data:(NSDictionary *)data
                    callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                    progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
             confirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;
- (NSURLSessionTask *)get:(NSString *)token
                     data:(NSDictionary *)data
                 callback:(void (^)(ContentModel *content, NSURLResponse *response, NSError *error))callback;
- (void)download:(NSString *)token
        callback:(void (^)(NSString *filePath))callback;
- (NSString *)getVideoUrl:(NSString *)token;
- (NSString *)getImageUrl:(NSString *)token;
- (NSURLSessionTask*)attachVideoWithVideoToken:(NSString*)videoToken
                                   streamToken:(NSString*)streamToken
                                          data:(NSDictionary*)data
                                          file:(NSString*)fileName
                                      callback:(void (^)(NSDictionary* jsonObject, NSURLResponse* response, NSError* error))callback
                                      progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress;
- (NSURLSessionTask*)createVideoWithData:(NSDictionary*)data
                                    file:(NSString*)fileName
                                   cover:(UIImage*)cover
                                callback:(void (^)(NSDictionary* jsonObject, NSURLResponse* response, NSError* error))callback
                                progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress;
- (NSURLSessionTask *)rerecordVideoWithToken:(NSString*)videoToken
                                        file:(NSString*)fileName
                                        data:(NSDictionary*)data
                                    callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
                                    progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress;
- (NSURLSessionTask*)createEmptyVideoWithData:(NSDictionary*)data
                                     callback:(void (^)(NSDictionary* jsonObject, NSURLResponse* response, NSError* error))callback;
- (NSURLSessionTask*)createLiveVideoWithData:(NSDictionary*)data
                                    callback:(void (^)(NSDictionary* jsonObject, NSURLResponse* response, NSError* error))callback;
- (NSURLSessionTask*)recorderSubmitWithVideoToken:(NSString*)videoToken
                                      streamToken:(NSString*)streamToken
                                             data:(NSDictionary*)data
                                         callback:(void (^)(NSDictionary* jsonObject, NSURLResponse* response, NSError* error))callback;
- (NSURLSessionTask *)destroy:(NSString *)token
                  streamToken:(NSString*)streamToken
                     callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)update:(NSString *)token
                        data:(NSDictionary *)data
                    callback:(void (^)(ContentModel *content, NSURLResponse *response,  NSError *error))callback;
- (NSURLSessionTask *)update:(NSString *)token
                 modelInJson:(NSString *)modelInJson
                    callback:(void (^)(ContentModel *content, NSURLResponse *response,  NSError *error))callback;
- (void)startScreenRecorderWithAppGroup:(NSString *)appGroup
                     preferredExtension:(nonnull NSString *)preferredExtension;
- (void)setAppGroup:(NSString *)groupID;

@end
