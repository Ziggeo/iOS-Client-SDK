//
//  ZiggeoApi.h
//
//  Copyright (c) 2021 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
@import UIKit;


@protocol ZiggeoApiDelegate <NSObject>

- (void)preparingToUploadWithPath:(NSString*)sourcePath;
- (void)preparingToUploadWithPath:(NSString*)sourcePath token:(NSString*)token;
- (void)uploadStartedWithPath:(NSString*)sourcePath token:(NSString*)token backgroundTask:(NSURLSessionTask*)uploadingTask;
- (void)uploadProgressForPath:(NSString*)sourcePath token:(NSString*)token totalBytesSent:(int)bytesSent totalBytesExpectedToSend:(int)totalBytes;
- (void)uploadCompletedForPath:(NSString*)sourcePath token:(NSString*)token withResponse:(NSURLResponse*)response error:(NSError*)error json:(NSDictionary*)json;

@end


@interface ZiggeoApiHelper : NSObject{
    Ziggeo* _application;
}

@property (weak) id<ZiggeoApiDelegate> delegate;

- (id)initWithApplication:(Ziggeo*)application_;

//MARK: Videos
- (NSURLSessionTask *)getZiggeoVideos:(void (^)(NSArray* jsonArray, NSError* error))callback;

//MARK: - Audios
- (NSURLSessionTask *)getZiggeoAudios:(void (^)(NSArray* jsonArray, NSError* error))callback;
- (NSURLSessionTask *)uploadAudioWithPath:(NSString *)path
                                 Callback:(void (^)(NSDictionary* jsonObject, NSURLResponse* response, NSError* error))callback
                                 Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
                          ConfirmCallback:(void (^)(NSDictionary* jsonObject, NSURLResponse* response, NSError* error))confirmCallback;
- (NSString*)getURLForAudioToken:(NSString*)audioToken;

//MARK: Images
- (NSURLSessionTask *)getZiggeoImages:(void (^)(NSArray* jsonArray, NSError* error))callback;
- (NSURLSessionTask *)uploadImageWithPath:(NSString *)path
                                 Callback:(void (^)(NSDictionary* jsonObject, NSURLResponse* response, NSError* error))callback
                                 Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
                          ConfirmCallback:(void (^)(NSDictionary* jsonObject, NSURLResponse* response, NSError* error))confirmCallback;
- (NSString*)getURLForImageToken:(NSString*)imageToken;

@end
