//
//  ZiggeoConfig.h
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MobileCoreServices/MobileCoreServices.h>
#import <AVFoundation/AVFoundation.h>
#import <Photos/Photos.h>
@import UIKit;


@protocol ZiggeoRecorderDelegate <NSObject>

@optional
- (void)luxMeter:(double)luminousity;
@optional
- (void)audioMeter:(double)audioLevel;
@optional
- (void)faceDetected:(int)faceID rect:(CGRect)rect;

@optional
- (void)ziggeoRecorderReady;
@optional
- (void)ziggeoRecorderCanceled;
@optional
- (void)ziggeoRecorderStarted;
@optional
- (void)ziggeoRecorderStopped:(NSString *)path;
@optional
- (void)ziggeoRecorderCurrentRecordedDurationSeconds:(double)seconds;
@optional
- (void)ziggeoRecorderPlaying;
@optional
- (void)ziggeoRecorderPaused;
@optional
- (void)ziggeoRecorderRerecord;
@optional
- (void)ziggeoRecorderManuallySubmitted;

@optional
- (void)ziggeoStreamingStarted;
@optional
- (void)ziggeoStreamingStopped;

@end


@protocol ZiggeoUploadDelegate <NSObject>

@optional
- (void)preparingToUploadWithPath:(NSString *)sourcePath;
@optional
- (void)failedToUploadWithPath:(NSString *)sourcePath;
@optional
- (void)uploadStartedWithPath:(NSString *)sourcePath token:(NSString *)token streamToken:(NSString *)streamToken backgroundTask:(NSURLSessionTask *)uploadingTask;
@optional
- (void)uploadProgressForPath:(NSString *)sourcePath token:(NSString *)token streamToken:(NSString *)streamToken totalBytesSent:(int)bytesSent totalBytesExpectedToSend:(int)totalBytes;
@optional
- (void)uploadFinishedForPath:(NSString *)sourcePath token:(NSString *)token streamToken:(NSString *)streamToken;
@optional
- (void)uploadVerifiedWithPath:(NSString *)sourcePath token:(NSString *)token streamToken:(NSString *)streamToken withResponse:(NSURLResponse *)response error:(NSError *)error json:(NSDictionary *)json;
@optional
- (void)uploadProcessingWithPath:(NSString *)sourcePath token:(NSString *)token streamToken:(NSString *)streamToken;
@optional
- (void)uploadProcessedWithPath:(NSString *)sourcePath token:(NSString *)token streamToken:(NSString *)streamToken;
@optional
- (void)deleteWithToken:(NSString *)token streamToken:(NSString *)streamToken withResponse:(NSURLResponse *)response error:(NSError *)error json:(NSDictionary *)json;
@end


@protocol ZiggeoPlayerDelegate <NSObject>

@optional
- (void)ziggeoPlayerPlaying;
@optional
- (void)ziggeoPlayerPaused;
@optional
- (void)ziggeoPlayerEnded;
@optional
- (void)ziggeoPlayerSeek:(double)positionMillis;
@optional
- (void)ziggeoPlayerReadyToPlay;

@end



@interface ZiggeoConfig : NSObject

@property (strong, nonatomic) NSString *server_api_url;
@property (strong, nonatomic) NSString *dev_server_api_url;
@property (strong, nonatomic) NSString *file_server_url;
@property (strong, nonatomic) NSString *cdn_api_url;
@property (strong, nonatomic) NSString *wowza_url;

@property (nonatomic) uint64_t cache_size;
@property (nonatomic) uint64_t player_cache_size;
@property (strong, nonatomic) NSString *cache_root;
@property (strong, nonatomic) NSString *player_cache_root;

- (id)initWithToken:(NSString *)token;
- (void)setRecorderCacheConfig:(NSDictionary *)recorderCacheConfig;
- (void)setPlayerCacheConfig:(NSDictionary *)config;

@end
