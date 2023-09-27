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
@class RecordingInfo;
@class UploadingConfig;
@class PlayerConfig;
@class QrScannerConfig;
@class FileSelectorConfig;
@class CacheConfig;
@class RecorderConfig;
@class AspectRatio;


static int VIDEO = 0x01;
static int AUDIO = 0x02;
static int IMAGE = 0x05;

static long UPDATE_DELAY = 1000L;

static int HIGH_VOLUME = 1;
static int MIDDLE_VOLUME = 2;
static int LOW_VOLUME = 3;

static long DEFAULT_SYNC_INTERVAL = 2 * 60 * 60 * 1000; // 2 hours

static int UPLOADING_ERROR_ACTION_CONTINUE_UPLOADING_MEDIA = 551;
static int UPLOADING_ERROR_ACTION_RELOAD_MEDIA = 552;
static int UPLOADING_ERROR_ACTION_ERROR_NOTIFICATION = 553;
static int UPLOADING_ERROR_ACTION_DELETE_MEDIA = 554;

static int DEFAULT_START_DELAY = 3; // seconds
static int DEFAULT_AUDIO_BITRATE = 64 * 1024; // 64KB
static int DEFAULT_AUDIO_SAMPLE_RATE = 48000; // 48kHz

static NSString *SCREEN_LOCK_TAG = @"CameraView lock";

/**
 * The camera device faces the opposite direction as the device's screen.
 */
static int FACING_BACK = 0;

/**
 * The camera device faces the same direction as the device's screen.
 */
static int FACING_FRONT = 1;

static int QUALITY_HIGH = 0;
static int QUALITY_MEDIUM = 1;
static int QUALITY_LOW = 2;
/**
 * Flash will not be fired.
 */
static int FLASH_OFF = 0;
/**
 * Flash will always be fired during snapshot.
 */
static int FLASH_ON = 1;
/**
 * Constant emission of light during preview, auto-focus and snapshot.
 */
static int FLASH_TORCH = 2;
/**
 * Flash will be fired automatically when required.
 */
static int FLASH_AUTO = 3;
/**
 * Flash will be fired in red-eye reduction mode.
 */
static int FLASH_RED_EYE = 4;

static int LANDSCAPE_90 = 90;
static int LANDSCAPE_270 = 270;

/**
 * This is max value supported by media recorder.
 */
static int MAX_RESOLUTION_WIDTH_SUPPORTED = 1920;
static int MAX_RESOLUTION_HEIGHT_SUPPORTED = 1080;

/*
 * 16 : 9
 */
static AspectRatio *DEFAULT_ASPECT_RATIO = nil;

/*
 * 4 : 3
 */
static AspectRatio *FALLBACK_ASPECT_RATIO = nil;

static AspectRatio *RATIO_16_9 = nil;
static AspectRatio *RATIO_4_3 = nil;
static AspectRatio *RATIO_1_1 = nil;

static NSString *STATUS_EMPTY = @"EMPTY";
static NSString *STATUS_DELETED = @"DELETED";
static NSString *STATUS_VERIFIED = @"VERIFIED";
static NSString *STATUS_PROCESSING = @"PROCESSING";
static NSString *STATUS_FAILED = @"FAILED";
static NSString *STATUS_READY = @"READY";

static NSString *ARG_PATH = @"ARG_PATH";
static NSString *ARG_TOKEN = @"ARG_TOKEN";
static NSString *ARG_IMAGE_MODE_ONLY = @"ARG_IMAGE_MODE_ONLY";
static NSString *ARG_URI = @"ARG_URI";
static NSString *ARG_COVER_SHOT_PATH = @"ARG_COVER_SHOT_PATH";
static NSString *ARG_FORCE_SEND = @"ARG_FORCE_SEND";
static NSString *ARG_SHOW_COVER_SHOT_SELECTION_POPUP = @"ARG_SHOW_COVER_SHOT_SELECTION_POPUP";
static NSString *ARG_SHOW_STOP_RECORDING_CONFIRMATION = @"ARG_SHOW_STOP_RECORDING_CONFIRMATION";
static NSString *ARG_SHOW_CONFIRMATION_ON_PLAYER = @"ARG_SHOW_CONFIRMATION_ON_PLAYER";
static NSString *ARG_FILE_TO_CONFIRM = @"ARG_FILE_TO_CONFIRM";
static NSString *ARG_SELECTED_FILTER = @"ARG_SELECTED_FILTER";
static NSString *ARG_SELECTED_VIEW_MODE = @"ARG_SELECTED_VIEW_MODE";
static NSString *ARG_PACKAGE_NAME = @"appname";
static NSString *ARG_CLIENT_AUTH = @"client_auth";
static NSString *ARG_SERVER_AUTH = @"server_auth";
static NSString *ARG_DATA = @"ARG_DATA";


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
/**
 * Triggered when a media uploadingStarted has started
 */
@optional
- (void)uploadStartedWithPath:(NSString *)sourcePath
                        token:(NSString *)token
                  streamToken:(NSString *)streamToken
               backgroundTask:(NSURLSessionTask *)uploadingTask;
/**
 * Continuous updates on the upload progress.
 */
@optional
- (void)uploadProgressWithPath:(NSString *)sourcePath
                         token:(NSString *)token
                   streamToken:(NSString *)streamToken
                totalBytesSent:(int)bytesSent
      totalBytesExpectedToSend:(int)totalBytes;
/**
 * Fires after upload has finished.
 */
@optional
- (void)uploadFinishedWithPath:(NSString *)sourcePath
                         token:(NSString *)token
                   streamToken:(NSString *)streamToken;
/**
 * Triggered after media is uploaded and verified that it can be processed.
 */
@optional
- (void)uploadVerifiedWithPath:(NSString *)sourcePath
                         token:(NSString *)token
                   streamToken:(NSString *)streamToken
                  withResponse:(NSURLResponse *)response
                         error:(NSError *)error
                          json:(NSDictionary *)json;
/**
 * Continuous update notifications while processing the media.
 */
@optional
- (void)uploadProcessingWithPath:(NSString *)sourcePath
                           token:(NSString *)token
                     streamToken:(NSString *)streamToken;
/**
 * Video successfully processed.
 */
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
/**
 * Called in case of error occurred
 */
@optional
- (void)errorWithInfo:(RecordingInfo *)info
                error:(NSError *)error
 lostConnectionAction:(int)lostConnectionAction;
/**
 * Called in case of error occurred
 */
@optional
- (void)errorWithError:(NSError *)error;

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
    FileSelectorConfig *_fileSelectorConfig;
    UploadingConfig *_uploadingConfig;
    PlayerConfig *_playerConfig;
    CacheConfig *_cacheConfig;
    QrScannerConfig *_qrScannerConfig;
    RecorderConfig *_recorderConfig;
    
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

// MARK: - 1. Init
- (id)init;
- (id)initWithToken:(NSString *)token;
- (void)sendLocalNotification:(NSString *)message;

// MARK: - Set Delegate
- (void)setQRScannerDelegate:(id<ZiggeoQRScannerDelegate>)delegate;
- (void)setHardwarePermissionDelegate:(id<ZiggeoHardwarePermissionDelegate>)delegate;
- (void)setUploadingDelegate:(id<ZiggeoUploadingDelegate>)delegate;
- (void)setFileSelectorDelegate:(id<ZiggeoFileSelectorDelegate>)delegate;
- (void)setRecorderDelegate:(id<ZiggeoRecorderDelegate>)delegate;
- (void)setSensorDelegate:(id<ZiggeoSensorDelegate>)delegate;
- (void)setPlayerDelegate:(id<ZiggeoPlayerDelegate>)delegate;
- (void)setScreenRecorderDelegate:(id<ZiggeoScreenRecorderDelegate>)delegate;

// MARK: - Get Delegate
- (id<ZiggeoQRScannerDelegate>)getQRScannerDelegate;
- (id<ZiggeoHardwarePermissionDelegate>)getHardwarePermissionDelegate;
- (id<ZiggeoUploadingDelegate>)getUploadingDelegate;
- (id<ZiggeoFileSelectorDelegate>)getFileSelectorDelegate;
- (id<ZiggeoRecorderDelegate>)getRecorderDelegate;
- (id<ZiggeoSensorDelegate>)getSensorDelegate;
- (id<ZiggeoPlayerDelegate>)getPlayerDelegate;
- (id<ZiggeoScreenRecorderDelegate>)getScreenRecorderDelegate;

// MARK: - Get Variables
- (NSString *)getAppToken;
- (NSString *)getServerAuthToken;
- (NSString *)getClientAuthToken;
- (UIViewController *)getParentViewController;
- (ZiggeoConfig *)config;
- (ZiggeoCacheManager *)cacheManager;
- (ZiggeoCacheManager *)playerCacheManager;
- (ZiggeoConnect *)connect;
- (ZiggeoUploadingHandler *)uploadingHandler;
- (ZiggeoVideos *)videos;
- (ZiggeoAudios *)audios;
- (ZiggeoImages *)images;
- (FileSelectorConfig *)fileSelectorConfig;
- (UploadingConfig *)uploadingConfig;
- (PlayerConfig *)playerConfig;
- (CacheConfig *)cacheConfig;
- (QrScannerConfig *)qrScannerConfig;
- (RecorderConfig *)recorderConfig;

// MARK: - Set Config Variables
- (void)setFileSelectorConfig:(FileSelectorConfig *)config;
- (void)setUploadingConfig:(UploadingConfig *)config;
- (void)setPlayerConfig:(PlayerConfig *)config;
- (void)setCacheConfig:(CacheConfig *)config;
- (void)setQrScannerConfig:(QrScannerConfig *)config;
- (void)setRecorderConfig:(RecorderConfig *)config;

// MARK: - ContactUs
- (void)sendReport:(NSArray *)array;
- (void)sendEmailToSupport:(NSString *)subject messageBody:(NSString *)messageBody file:(FileInfoData *)file;
- (void)sendEmailToSupport;
- (void)log:(NSString *)message;
- (void)logError:(NSString *)message;
- (BOOL)isNetworkConnected;
- (BOOL)isWifiConnected;


// MARK: - 2. Recorder
- (void)record;
- (void)startScreenRecorderWithAppGroup:(NSString *)appGroup
                     preferredExtension:(NSString *)preferredExtension;
- (void)trimVideo:(NSString *)videoUrl;
- (void)startImageRecorder;
- (void)startAudioRecorder;
- (void)uploadFromPath:(NSString *)fileName
                  data:(NSDictionary *)data;
- (void)uploadFromPath:(NSString *)fileName
                  data:(NSDictionary *)data
              callback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))callback
              progress:(void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
       confirmCallback:(void (^)(NSDictionary *jsonObject, NSURLResponse *response, NSError *error))confirmCallback;
- (void)startFileSelector;
- (void)cancelUpload:(NSString *)path :(bool)delete_file;


// MARK: - 3. Player
- (void)playVideo:(NSString *)token;
- (void)playVideos:(NSArray<NSString *> *)tokens;
- (void)playFromUri:(NSString *)url;
- (void)playFromUris:(NSArray<NSString *> *)urls;

- (void)showImage:(NSString *)token;
- (void)showImages:(NSArray<NSString *> *)tokens;
- (void)showImageFromUri:(NSString *)url;
- (void)showImageFromUris:(NSArray<NSString *> *)urls;

- (void)playAudio:(NSString *)token;
- (void)playAudios:(NSArray<NSString *> *)tokens;
- (void)playAudioFromUri:(NSString *)url;
- (void)playAudioFromUris:(NSArray<NSString *> *)urls;

- (void)startAudioPlayer:(NSString *)token;


// MARK: - 4. QR Scanner
- (void)startQrScanner;

@end
