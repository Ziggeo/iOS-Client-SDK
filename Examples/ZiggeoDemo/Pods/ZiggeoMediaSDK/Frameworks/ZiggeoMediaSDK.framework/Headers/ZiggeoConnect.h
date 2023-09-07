//
//  ZiggeoConnect.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"

@interface ZiggeoConnect : NSObject

@property (nonatomic) NSString * serverAuthToken;
@property (nonatomic) NSString * clientAuthToken;

- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo;
- (NSURLSessionTask *)requestWithMethod:(NSString *)method
                                   path:(NSString *)path
                                   data:(NSDictionary*)data
                               callback:(void (^)(NSData *data, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask*)backgroundUploadWithPath:(NSString*)path
                                         data:(NSDictionary*)data
                                   identifier:(NSString*)identifier
                                         file:(NSString*)file
                                     callback:(void (^)(NSData *data, NSURLResponse *response, NSError *error))callback
                                     progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress;
- (NSURLSessionTask *)uploadFileWithPath:(NSString *)url
                             parameters:(NSDictionary *)parameters
                             identifier:(NSString *)identifier
                               filePath:(NSString *)filePath
                               fileName:(NSString *)fileName
                               mimeType:(NSString *)mimeType
                          fileExtension:(NSString *)fileExtension
                               callback:(void (^)(NSData *data, NSURLResponse *response, NSError *error))callback
                               progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress;
- (NSURLSessionTask *)requestStringWithMethod:(NSString *)method
                                        path:(NSString *)path
                                        data:(NSDictionary*)data
                                    callback:(void (^)(NSString *string, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)requestJSONWithMethod:(NSString *)method
                                      path:(NSString *)path
                                      data:(NSDictionary*)data
                                  callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)requestJSONArrayWithMethod:(NSString *)method
                                           path:(NSString *)path
                                           data:(NSDictionary*)data
                                       callback:(void (^)(NSArray *jsonArray, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)getWithPath:(NSString *)path
                            data:(NSDictionary*)data
                        callback:(void (^)(NSData *data, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)getStringWithPath:(NSString *)path
                                  data:(NSDictionary*)data
                              callback:(void (^)(NSString *string, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)getJsonWithPath:(NSString *)path
                                data:(NSDictionary*)data
                            callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)getJsonArrayWithPath:(NSString *)path
                                     data:(NSDictionary*)data
                                 callback:(void (^)(NSArray *jsonArray, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)postWithPath:(NSString *)path
                             data:(NSDictionary*)data
                         callback:(void (^)(NSData *data, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)postRawDataWithPath:(NSString *)path
                                    data:(NSData*)data
                                  params:(NSDictionary*)params
                                callback:(void (^)(NSData *data, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)postJsonWithPath:(NSString *)path
                                 data:(NSDictionary*)data
                             callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)deleteWithPath:(NSString *)path
                               data:(NSDictionary*)data
                           callback:(void (^)(NSData *data, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)deleteJsonWithPath:(NSString *)path
                                   data:(NSDictionary*)data
                               callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback;
- (NSURLSessionTask *)addSessionData:(NSDictionary*)data
                               path:(NSString *)path
                           callback:(NSURLSessionTask* (^)(NSDictionary* dataWithSessionData))callback;
- (void)appWakeupSignalTaskComplete:(NSString *)sessionID;

@end
