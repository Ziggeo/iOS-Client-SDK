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

static NSString * _Nonnull SCREEN_LOCK_TAG = @"CameraView lock";

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
static AspectRatio * __null_unspecified DEFAULT_ASPECT_RATIO = nil;

/*
 * 4 : 3
 */
static AspectRatio * __null_unspecified FALLBACK_ASPECT_RATIO = nil;

static AspectRatio * __null_unspecified RATIO_16_9 = nil;
static AspectRatio * __null_unspecified RATIO_4_3 = nil;
static AspectRatio * __null_unspecified RATIO_1_1 = nil;

static NSString * __nonnull STATUS_EMPTY = @"EMPTY";
static NSString * __nonnull STATUS_DELETED = @"DELETED";
static NSString * __nonnull STATUS_VERIFIED = @"VERIFIED";
static NSString * __nonnull STATUS_PROCESSING = @"PROCESSING";
static NSString * __nonnull STATUS_FAILED = @"FAILED";
static NSString * __nonnull STATUS_READY = @"READY";

static NSString * __nonnull ARG_PATH = @"ARG_PATH";
static NSString * __nonnull ARG_TOKEN = @"ARG_TOKEN";
static NSString * __nonnull ARG_IMAGE_MODE_ONLY = @"ARG_IMAGE_MODE_ONLY";
static NSString * __nonnull ARG_URI = @"ARG_URI";
static NSString * __nonnull ARG_COVER_SHOT_PATH = @"ARG_COVER_SHOT_PATH";
static NSString * __nonnull ARG_FORCE_SEND = @"ARG_FORCE_SEND";
static NSString * __nonnull ARG_SHOW_COVER_SHOT_SELECTION_POPUP = @"ARG_SHOW_COVER_SHOT_SELECTION_POPUP";
static NSString * __nonnull ARG_SHOW_STOP_RECORDING_CONFIRMATION = @"ARG_SHOW_STOP_RECORDING_CONFIRMATION";
static NSString * __nonnull ARG_SHOW_CONFIRMATION_ON_PLAYER = @"ARG_SHOW_CONFIRMATION_ON_PLAYER";
static NSString * __nonnull ARG_FILE_TO_CONFIRM = @"ARG_FILE_TO_CONFIRM";
static NSString * __nonnull ARG_SELECTED_FILTER = @"ARG_SELECTED_FILTER";
static NSString * __nonnull ARG_SELECTED_VIEW_MODE = @"ARG_SELECTED_VIEW_MODE";
static NSString * __nonnull ARG_PACKAGE_NAME = @"appname";
static NSString * __nonnull ARG_CLIENT_AUTH = @"client_auth";
static NSString * __nonnull ARG_SERVER_AUTH = @"server_auth";
static NSString * __nonnull ARG_DATA = @"ARG_DATA";


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
- (void)preparingToUploadWithPath:(nonnull NSString *)sourcePath;
/**
 * Triggered when a media uploadingStarted has started
 */
@optional
- (void)uploadStartedWithPath:(nonnull NSString *)sourcePath
                        token:(nonnull NSString *)token
                  streamToken:(nonnull NSString *)streamToken
               backgroundTask:(nonnull NSURLSessionTask *)uploadingTask;
/**
 * Continuous updates on the upload progress.
 */
@optional
- (void)uploadProgressWithPath:(nonnull NSString *)sourcePath
                         token:(nonnull NSString *)token
                   streamToken:(nonnull NSString *)streamToken
                totalBytesSent:(int)bytesSent
      totalBytesExpectedToSend:(int)totalBytes;
/**
 * Fires after upload has finished.
 */
@optional
- (void)uploadFinishedWithPath:(nonnull NSString *)sourcePath
                         token:(nullable NSString *)token
                   streamToken:(nullable NSString *)streamToken;
/**
 * Triggered after media is uploaded and verified that it can be processed.
 */
@optional
- (void)uploadVerifiedWithPath:(nonnull NSString *)sourcePath
                         token:(nonnull NSString *)token
                   streamToken:(nonnull NSString *)streamToken
                  withResponse:(nonnull NSURLResponse *)response
                         error:(nullable NSError *)error
                          json:(nullable NSDictionary *)json;
/**
 * Continuous update notifications while processing the media.
 */
@optional
- (void)uploadProcessingWithPath:(nonnull NSString *)sourcePath
                           token:(nonnull NSString *)token
                     streamToken:(nonnull NSString *)streamToken;
/**
 * Video successfully processed.
 */
@optional
- (void)uploadProcessedWithPath:(nonnull NSString *)sourcePath
                          token:(nonnull NSString *)token
                    streamToken:(nonnull NSString *)streamToken;
@optional
- (void)deleteWithToken:(nonnull NSString *)token
            streamToken:(nonnull NSString *)streamToken
           withResponse:(nonnull NSURLResponse *)response
                  error:(nullable NSError *)error
                   json:(nullable NSDictionary *)json;
@optional
- (void)cancelUploadByPath:(nonnull NSString *)sourcePath
                deleteFile:(BOOL)deleteFile;
@optional
- (void)cancelCurrentUpload:(BOOL)deleteFile;
/**
 * Called in case of error occurred
 */
@optional
- (void)errorWithInfo:(nullable RecordingInfo *)info
                error:(nonnull NSError *)error
 lostConnectionAction:(int)lostConnectionAction;
/**
 * Called in case of error occurred
 */
@optional
- (void)errorWithError:(nonnull NSError *)error;

@end


// MARK: - ZiggeoFileSelectorDelegate
@protocol ZiggeoFileSelectorDelegate <NSObject>

@optional
- (void)uploadSelected:(nonnull NSArray<NSString *> *)paths;
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
- (void)recorderStopped:(nonnull NSString *)path;
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
- (void)qrCodeScaned:(nonnull NSString *)qrCode;
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
    QrScannerConfig *_qrScannerConfig;
    CacheConfig *_cacheConfig;
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
    
@property (strong, nonatomic) NSString * __nonnull token;
@property (nonatomic) bool enableDebugLogs;

// MARK: - 1. Init
- (nonnull id)init;
- (nonnull id)initWithToken:(nonnull NSString *)token;
- (void)sendLocalNotification:(nonnull NSString *)message;

// MARK: - Set Delegate
- (void)setQRScannerDelegate:(nullable id<ZiggeoQRScannerDelegate>)delegate;
- (void)setHardwarePermissionDelegate:(nullable id<ZiggeoHardwarePermissionDelegate>)delegate;
- (void)setUploadingDelegate:(nullable id<ZiggeoUploadingDelegate>)delegate;
- (void)setFileSelectorDelegate:(nullable id<ZiggeoFileSelectorDelegate>)delegate;
- (void)setRecorderDelegate:(nullable id<ZiggeoRecorderDelegate>)delegate;
- (void)setSensorDelegate:(nullable id<ZiggeoSensorDelegate>)delegate;
- (void)setPlayerDelegate:(nullable id<ZiggeoPlayerDelegate>)delegate;
- (void)setScreenRecorderDelegate:(nullable id<ZiggeoScreenRecorderDelegate>)delegate;

// MARK: - Get Delegate
- (nullable id<ZiggeoQRScannerDelegate>)getQRScannerDelegate;
- (nullable id<ZiggeoHardwarePermissionDelegate>)getHardwarePermissionDelegate;
- (nullable id<ZiggeoUploadingDelegate>)getUploadingDelegate;
- (nullable id<ZiggeoFileSelectorDelegate>)getFileSelectorDelegate;
- (nullable id<ZiggeoRecorderDelegate>)getRecorderDelegate;
- (nullable id<ZiggeoSensorDelegate>)getSensorDelegate;
- (nullable id<ZiggeoPlayerDelegate>)getPlayerDelegate;
- (nullable id<ZiggeoScreenRecorderDelegate>)getScreenRecorderDelegate;

// MARK: - Get Variables
- (nonnull NSString *)getAppToken;
- (nullable NSString *)getServerAuthToken;
- (nullable NSString *)getClientAuthToken;
- (nonnull UIViewController *)getParentViewController;
- (nonnull ZiggeoConfig *)config;
- (nonnull ZiggeoCacheManager *)cacheManager;
- (nonnull ZiggeoCacheManager *)playerCacheManager;
- (nonnull ZiggeoConnect *)connect;
- (nonnull ZiggeoUploadingHandler *)uploadingHandler;
- (nonnull ZiggeoVideos *)videos;
- (nonnull ZiggeoAudios *)audios;
- (nonnull ZiggeoImages *)images;
- (nonnull FileSelectorConfig *)fileSelectorConfig;
- (nonnull UploadingConfig *)uploadingConfig;
- (nonnull PlayerConfig *)playerConfig;
- (nonnull QrScannerConfig *)qrScannerConfig;
- (nonnull CacheConfig *)cacheConfig;
- (nonnull RecorderConfig *)recorderConfig;

// MARK: - Set Config Variables
- (void)setFileSelectorConfig:(nonnull FileSelectorConfig *)config;
- (void)setUploadingConfig:(nonnull UploadingConfig *)config;
- (void)setPlayerConfig:(nonnull PlayerConfig *)config;
- (void)setQrScannerConfig:(nonnull QrScannerConfig *)config;
- (void)setCacheConfig:(nonnull CacheConfig *)config;
- (void)setRecorderConfig:(nonnull RecorderConfig *)config;

// MARK: - ContactUs
- (void)sendReport:(nonnull NSArray *)array;
- (void)sendEmailToSupport:(nonnull NSString *)subject messageBody:(nonnull NSString *)messageBody file:(nullable FileInfoData *)file;
- (void)sendEmailToSupport;
- (void)log:(nonnull NSString *)message;
- (void)logError:(nonnull NSString *)message;
- (BOOL)isNetworkConnected;
- (BOOL)isWifiConnected;


// MARK: - 2. Recorder
- (void)record;
- (void)startScreenRecorderWithAppGroup:(nonnull NSString *)appGroup
                     preferredExtension:(nonnull NSString *)preferredExtension NS_SWIFT_NAME( startScreenRecorder(appGroup:preferredExtension:) );
- (void)trimVideo:(nonnull NSString *)videoUrl;
- (void)startImageRecorder;
- (void)startAudioRecorder;
- (void)uploadFromPath:(nonnull NSString *)fileName
                  data:(nonnull NSDictionary *)data;
- (void)uploadFromPath:(nonnull NSString *)fileName
                  data:(nonnull NSDictionary *)data
              callback:(nullable void (^)(NSDictionary * __nullable jsonObject, NSURLResponse * __nonnull response, NSError * __nullable error))callback
              progress:(nullable void (^)(int totalBytesSent, int totalBytesExpectedToSend))progress
       confirmCallback:(nullable void (^)(NSDictionary * __nullable jsonObject, NSURLResponse * __nonnull response, NSError * __nullable error))confirmCallback;
- (void)startFileSelector;
- (void)cancelUpload:(nullable NSString *)path :(bool)delete_file;


// MARK: - 3. Player
- (void)playVideo:(nonnull NSString *)token;
- (void)playVideos:(nonnull NSArray<NSString *> *)tokens;
- (void)playFromUri:(nonnull NSString *)url;
- (void)playFromUris:(nonnull NSArray<NSString *> *)urls;

- (void)showImage:(nonnull NSString *)token;
- (void)showImages:(nonnull NSArray<NSString *> *)tokens;
- (void)showImageFromUri:(nonnull NSString *)url;
- (void)showImageFromUris:(nonnull NSArray<NSString *> *)urls;

- (void)playAudio:(nonnull NSString *)token;
- (void)playAudios:(nonnull NSArray<NSString *> *)tokens;
- (void)playAudioFromUri:(nonnull NSString *)url;
- (void)playAudioFromUris:(nonnull NSArray<NSString *> *)urls;

- (void)startAudioPlayer:(nonnull NSString *)token;


// MARK: - 4. QR Scanner
- (void)startQrScanner;

@end
