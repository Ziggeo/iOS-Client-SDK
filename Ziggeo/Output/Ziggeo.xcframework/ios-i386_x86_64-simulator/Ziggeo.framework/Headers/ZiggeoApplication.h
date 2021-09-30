//
//  Ziggeo.h
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ZiggeoConfig;
@class ZiggeoConnect;
@class ZiggeoCacheManager;
@class ZiggeoVideos;
@class ZiggeoAudios;
@class ZiggeoImages;


@protocol ZiggeoHardwarePermissionCheckDelegate <NSObject>

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

@interface Ziggeo : NSObject {
    ZiggeoConfig* _configObj;
    ZiggeoConnect* _connectObj;
    ZiggeoCacheManager *_cacheManager;
    ZiggeoCacheManager *_playerCacheManager;
    ZiggeoVideos *_videos;
    ZiggeoAudios *_audios;
    ZiggeoImages *_images;
}
    
@property (strong, nonatomic) NSString *token;
@property (nonatomic) bool enableDebugLogs;

- (id)initWithToken:(NSString *)token_;
- (void)log:(NSString *)message;
- (void)logError:(NSString *)message;

- (ZiggeoConfig *)config;

- (ZiggeoCacheManager *)cacheManager;
- (ZiggeoCacheManager *)playerCacheManager;

- (ZiggeoConnect *)connect;
- (ZiggeoVideos *)videos;
- (ZiggeoAudios *)audios;
- (ZiggeoImages *)images;
- (void)cancelRequest;
- (void)checkHardwarePermission:(id<ZiggeoHardwarePermissionCheckDelegate>)delegate;

@end
