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

@end
