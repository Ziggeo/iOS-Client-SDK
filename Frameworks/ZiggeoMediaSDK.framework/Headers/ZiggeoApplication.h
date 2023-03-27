//
//  ZiggeoApplication.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "FileInfoData.h"

@class ZiggeoConfig;
@class ZiggeoConnect;
@class ZiggeoCacheManager;
@class ZiggeoUploadingHandler;
@class ZiggeoVideos;
@class ZiggeoAudios;
@class ZiggeoImages;


typedef enum {
    Media_Type_Video,
    Media_Type_Audio,
    Media_Type_Image
} Media_Type;

typedef enum {
    BYTES_SENT,
    BYTES_TOTAL,
    FILE_NAME,
    PATH,
    QR,
    TOKEN,
//    ERROR,
    PERMISSIONS,
    SOUND_LEVEL,
    SECONDS_LEFT,
    MILLIS_PASSED,
    MILLIS,
    FILES,
    VALUE,
    MEDIA_TYPES,
    BLUR_EFFECT,
    CLIENT_AUTH,
    SERVER_AUTH,
    TAGS
} Ziggeo_Key_Type;

typedef enum {
    KEY_HIDE_RECORDER_CONTROLS,
    KEY_HIDE_PLAYER_CONTROLS
} Ziggeo_Theme_Key_Type;

static NSString *REAR_CAMERA = @"rearCamera";
static NSString *FRONT_CAMERA = @"frontCamera";
static NSString *HIGH_QUALITY = @"highQuality";
static NSString *MEDIUM_QUALITY = @"mediumQuality";
static NSString *LOW_QUALITY = @"lowQuality";
static NSString *ERR_UNKNOWN = @"ERR_UNKNOWN";
static NSString *ERR_DURATION_EXCEEDED = @"ERR_DURATION_EXCEEDED";
static NSString *ERR_FILE_DOES_NOT_EXIST = @"ERR_FILE_DOES_NOT_EXIST";
static NSString *ERR_PERMISSION_DENIED = @"ERR_PERMISSION_DENIED";
static NSString *ARG_DURATION = @"max_duration";
static NSString *ARG_MEDIA_TYPE = @"media_type";
static NSString *ENFORCE_DURATION = @"enforce_duration";
static NSString *CLOSE_AFTER_SUCCESS_FUL_SCAN = @"closeAfterSuccessfulScan";

static NSString *ZIGGEO_STATUS_EMPTY = @"EMPTY";
static NSString *ZIGGEO_STATUS_DELETED = @"DELETED";
static NSString *ZIGGEO_STATUS_VERIFIED = @"VERIFIED";
static NSString *ZIGGEO_STATUS_PROCESSING = @"PROCESSING";
static NSString *ZIGGEO_STATUS_FAILED = @"FAILED";
static NSString *ZIGGEO_STATUS_READY = @"READY";


// MARK: - ZiggeoHardwarePermissionDelegate
@protocol ZiggeoHardwarePermissionDelegate <NSObject>

@optional
- (void)checkCameraPermission:(BOOL)granted;
@optional
- (void)checkMicrophonePermission:(BOOL)granted;
@optional
- (void)checkPhotoLibraryPermission:(BOOL)granted;
@optional
- (void)checkHasCamera:(BOOL)hasCamera;
@optional
- (void)checkHasMicrophone:(BOOL)hasMicrophone;

@end

// MARK: - ZiggeoUploadingDelegate
@protocol ZiggeoUploadingDelegate <NSObject>

@optional
- (void)preparingToUploadWithPath:(NSString *)sourcePath;
@optional
- (void)failedToUploadWithPath:(NSString *)sourcePath;
@optional
- (void)uploadStartedWithPath:(NSString *)sourcePath
                        token:(NSString *)token
                  streamToken:(NSString *)streamToken
               backgroundTask:(NSURLSessionTask *)uploadingTask;
@optional
- (void)uploadProgressWithPath:(NSString *)sourcePath
                         token:(NSString *)token
                   streamToken:(NSString *)streamToken
                totalBytesSent:(int)bytesSent
      totalBytesExpectedToSend:(int)totalBytes;
@optional
- (void)uploadFinishedWithPath:(NSString *)sourcePath
                         token:(NSString *)token
                   streamToken:(NSString *)streamToken;
@optional
- (void)uploadVerifiedWithPath:(NSString *)sourcePath
                         token:(NSString *)token
                   streamToken:(NSString *)streamToken
                  withResponse:(NSURLResponse *)response
                         error:(NSError *)error
                          json:(NSDictionary *)json;
@optional
- (void)uploadProcessingWithPath:(NSString *)sourcePath
                           token:(NSString *)token
                     streamToken:(NSString *)streamToken;
@optional
- (void)uploadProcessedWithPath:(NSString *)sourcePath
                          token:(NSString *)token
                    streamToken:(NSString *)streamToken;
@optional
- (void)deleteWithToken:(NSString *)token
            streamToken:(NSString *)streamToken
           withResponse:(NSURLResponse *)response
                  error:(NSError *)error
                   json:(NSDictionary *)json;
@optional
- (void)cancelUploadByPath:(NSString *)sourcePath
                deleteFile:(BOOL)deleteFile;
@optional
- (void)cancelCurrentUpload:(BOOL)deleteFile;

@end


// MARK: - ZiggeoFileSelectorDelegate
@protocol ZiggeoFileSelectorDelegate <NSObject>

@optional
- (void)uploadSelected:(NSArray<NSString *> *)paths;
@optional
- (void)uploadCancelledByUser;

@end


// MARK: - ZiggeoRecorderDelegate
@protocol ZiggeoRecorderDelegate <NSObject>

@optional
- (void)recorderCountdown:(int)secondsLeft;
@optional
- (void)recorderReady;
@optional
- (void)recorderStarted;
@optional
- (void)recorderCurrentRecordedDurationSeconds:(double)seconds;
@optional
- (void)recorderPaused;
@optional
- (void)recorderStopped:(NSString *)path;
@optional
- (void)recorderRerecord;
@optional
- (void)recorderPlaying;
@optional
- (void)recorderManuallySubmitted;
@optional
- (void)streamingStarted;
@optional
- (void)streamingStopped;
@optional
- (void)recorderCancelledByUser;

@end

// MARK: - ZiggeoSensorDelegate
@protocol ZiggeoSensorDelegate <NSObject>

@optional
- (void)luxMeter:(double)luminousity;
@optional
- (void)audioMeter:(double)audioLevel;
@optional
- (void)faceDetected:(int)faceID rect:(CGRect)rect;

@end


// MARK: - ZiggeoPlayerDelegate
@protocol ZiggeoPlayerDelegate <NSObject>

@optional
- (void)playerPlaying;
@optional
- (void)playerPaused;
@optional
- (void)playerEnded;
@optional
- (void)playerSeek:(double)positionMillis;
@optional
- (void)playerReadyToPlay;
@optional
- (void)playerCancelledByUser;

@end


// MARK: - ZiggeoQRScannerDelegate
@protocol ZiggeoQRScannerDelegate <NSObject>

@optional
- (void)qrCodeScaned:(NSString *)qrCode;
@optional
- (void)qrCodeScanCancelledByUser;

@end


// MARK: - ZiggeoScreenRecorderDelegate
@protocol ZiggeoScreenRecorderDelegate <NSObject>

@end



@interface Ziggeo : NSObject {
    ZiggeoConfig *_configObj;
    ZiggeoConnect *_connectObj;
    ZiggeoCacheManager *_cacheManager;
    ZiggeoCacheManager *_playerCacheManager;
    ZiggeoUploadingHandler *_uploadingHandler;
    ZiggeoVideos *_videos;
    ZiggeoAudios *_audios;
    ZiggeoImages *_images;
    
    id<ZiggeoQRScannerDelegate> qrScannerDelegate;
    id<ZiggeoHardwarePermissionDelegate> hardwarePermissionDelegate;
    id<ZiggeoUploadingDelegate> uploadingDelegate;
    id<ZiggeoSensorDelegate> sensorDelegate;
    id<ZiggeoFileSelectorDelegate> fileSelectorDelegate;
    id<ZiggeoRecorderDelegate> recorderDelegate;
    id<ZiggeoPlayerDelegate> playerDelegate;
    id<ZiggeoScreenRecorderDelegate> screenRecorderDelegate;
}
    
@property (strong, nonatomic) NSString *token;
@property (nonatomic) bool enableDebugLogs;


- (id)init;
- (id)initWithToken:(NSString *)token;
- (UIViewController *)getParentViewController;
- (void)log:(NSString *)message;
- (void)logError:(NSString *)message;
- (void)setQRScannerDelegate:(id<ZiggeoQRScannerDelegate>)delegate;
- (id<ZiggeoQRScannerDelegate>)getQRScannerDelegate;
- (void)setHardwarePermissionDelegate:(id<ZiggeoHardwarePermissionDelegate>)delegate;
- (id<ZiggeoHardwarePermissionDelegate>)getHardwarePermissionDelegate;
- (void)setUploadingDelegate:(id<ZiggeoUploadingDelegate>)delegate;
- (id<ZiggeoUploadingDelegate>)getUploadingDelegate;
- (void)setFileSelectorDelegate:(id<ZiggeoFileSelectorDelegate>)delegate;
- (id<ZiggeoFileSelectorDelegate>)getFileSelectorDelegate;
- (void)setRecorderDelegate:(id<ZiggeoRecorderDelegate>)delegate;
- (id<ZiggeoRecorderDelegate>)getRecorderDelegate;
- (void)setSensorDelegate:(id<ZiggeoSensorDelegate>)delegate;
- (id<ZiggeoSensorDelegate>)getSensorDelegate;
- (void)setPlayerDelegate:(id<ZiggeoPlayerDelegate>)delegate;
- (id<ZiggeoPlayerDelegate>)getPlayerDelegate;
- (void)setScreenRecorderDelegate:(id<ZiggeoScreenRecorderDelegate>)delegate;
- (id<ZiggeoScreenRecorderDelegate>)getScreenRecorderDelegate;

- (ZiggeoConfig *)config;
- (ZiggeoCacheManager *)cacheManager;
- (ZiggeoCacheManager *)playerCacheManager;
- (ZiggeoConnect *)connect;
- (ZiggeoUploadingHandler *)uploadingHandler;
- (ZiggeoVideos *)videos;
- (ZiggeoAudios *)audios;
- (ZiggeoImages *)images;

- (NSDictionary *)extraArgsForRecorder;
- (NSDictionary *)themeArgsForRecorder;
//- (NSDictionary *)extraArgsForPlayer;
//- (NSDictionary *)themeArgsForPlayer;
- (NSDictionary *)uploadingConfig;

- (NSString *)ziggeoKeyTypeToString:(Ziggeo_Key_Type)keyType;
- (NSString *)ziggeoThemeKeyTypeToString:(Ziggeo_Theme_Key_Type)keyType;


// ContactUs
- (void)sendReport:(NSArray *)array;
- (void)sendEmailToSupport:(NSString *)subject messageBody:(NSString *)messageBody file:(FileInfoData *)file;
- (void)sendEmailToSupport;

// ZiggeoRecorder
- (void)setRecorderCacheConfig:(NSDictionary *)config;
- (void)setRecorderInterfaceConfig:(NSDictionary *)config;
- (void)setUploadingConfig:(NSDictionary *)config;
- (void)setLiveStreamingEnabled:(BOOL)enabled;
- (void)setAutostartRecordingAfter:(int)seconds;
- (void)setStartDelay:(int)seconds;
- (void)setBlurMode:(BOOL)enabled;
- (void)setExtraArgsForRecorder:(NSDictionary *)map;
- (void)setThemeArgsForRecorder:(NSDictionary *)map;
- (void)setCoverSelectorEnabled:(BOOL)enabled;
- (void)setMaxRecordingDuration:(int)seconds;
- (void)setVideoWidth:(int)width;
- (void)setVideoHeight:(int)height;
- (void)setVideoBitrate:(int)bitrate;
- (void)setAudioSampleRate:(int)sampleRate;
- (void)setAudioBitrate:(int)bitrate;
- (void)setCameraSwitchEnabled:(BOOL)enabled;
- (void)setSendImmediately:(BOOL)sendImmediately;
- (void)setQuality:(int)quality;
- (void)setCamera:(NSString *)facing;
- (void)trimVideo:(NSString *)videoUrl;

- (void)record;
- (void)playVideo:(NSArray *)tokens;
- (void)playFromUri:(NSArray *)path_or_urls;
- (void)startImageRecorder;
- (void)showImage:(NSArray *)tokens;
- (void)showImageWithPaths:(NSArray *)paths;
- (void)startAudioRecorder;
- (void)startAudioPlayer:(NSArray *)tokens;
- (void)startAudioPlayerWithPaths:(NSArray *)paths;

- (void)startScreenRecorderWithAppGroup:(NSString *)appGroup
                     preferredExtension:(nonnull NSString *)preferredExtension;

- (void)uploadFromPath:(NSString *)fileName
                  Data:(NSDictionary *)data
              Callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
              Progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
       ConfirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;
- (void)uploadFromFileSelector:(NSDictionary *)data;
- (void)cancelUpload:(NSString *)path :(bool)delete_file;
- (void)startQrScanner;
- (void)startQrScanner:(NSDictionary *)config;

- (void)setExtraArgsForPlayer:(NSDictionary *)map;
- (void)setThemeArgsForPlayer:(NSDictionary *)map;
- (void)setPlayerCacheConfig:(NSDictionary *)config;
- (void)setAdsURL:(NSString *)url;

@end
