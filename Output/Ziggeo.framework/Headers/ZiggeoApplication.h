//
//  Ziggeo.h
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class ZiggeoConfig;
@class ZiggeoConnect;
@class ZiggeoCacheManager;
@class ZiggeoUploadingHandler;
@class ZiggeoVideos;
@class ZiggeoAudios;
@class ZiggeoImages;


typedef enum {
    video,
    audio,
    image
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
static NSString *MAX_DURATION = @"max_duration";
static NSString *ENFORCE_DURATION = @"enforce_duration";

// MARK: - ZiggeoDelegate
@protocol ZiggeoDelegate <NSObject>

// ZiggeoUploadDelegate
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
- (void)uploadProgressForPath:(NSString *)sourcePath
                        token:(NSString *)token
                  streamToken:(NSString *)streamToken
               totalBytesSent:(int)bytesSent
     totalBytesExpectedToSend:(int)totalBytes;
@optional
- (void)uploadFinishedForPath:(NSString *)sourcePath
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

// ZiggeoHardwarePermissionCheckDelegate
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

// ZiggeoRecorderDelegate
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

// ZiggeoPlayerDelegate
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



@interface Ziggeo : NSObject {
    ZiggeoConfig *_configObj;
    ZiggeoConnect *_connectObj;
    ZiggeoCacheManager *_cacheManager;
    ZiggeoCacheManager *_playerCacheManager;
    ZiggeoUploadingHandler *_uploadingHandler;
    ZiggeoVideos *_videos;
    ZiggeoAudios *_audios;
    ZiggeoImages *_images;
}
    
@property (strong, nonatomic) NSString *token;
@property (nonatomic) bool enableDebugLogs;
@property (weak) id<ZiggeoDelegate> delegate;


- (id)initWithToken:(NSString *)token;
- (id)initWithToken:(NSString *)token Delegate:(id<ZiggeoDelegate>)delegate;

- (NSString *)getPathWithType:(Media_Type)type token:(NSString *)mediaToken;
- (NSString *)getVideoImage:(NSString *)videoToken;
- (void)log:(NSString *)message;
- (void)logError:(NSString *)message;

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
- (void)sendEmailToSupport;

// ZiggeoRecorder
- (void)setRecorderCacheConfig:(NSDictionary *)config;
- (void)setRecorderInterfaceConfig:(NSDictionary *)config; //
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

- (void)record;
- (void)startImageRecorder;
- (void)startAudioRecorder;
- (void)startAudioPlayer:(NSString *)token;
- (void)showImage:(NSString *)token;
- (void)startScreenRecorder;
- (void)uploadFromPath:(NSString *)fileName :(NSDictionary *)data;
- (void)uploadFromFileSelector:(NSDictionary *)data;
- (void)cancelUpload:(NSString *)path :(bool)delete_file;
- (void)startQrScanner:(NSDictionary *)data;

// ZiggeoPlayer
- (void)playVideo:(NSString *)videoId;
- (void)playFromUri:(NSString *)path_or_url;
- (void)setExtraArgsForPlayer:(NSDictionary *)map;
- (void)setThemeArgsForPlayer:(NSDictionary *)map;
- (void)setPlayerCacheConfig:(NSDictionary *)config; //
- (void)setAdsURL:(NSString *)url;

- (NSString *)getVideoUrl:(NSString *)token;
- (NSString *)getAudioUrl:(NSString *)token;
- (NSString *)getImageUrl:(NSString *)token;

@end
