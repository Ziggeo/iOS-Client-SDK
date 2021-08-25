//
//  ZiggeoCacheManager.h
//
// Copyright (c) 2020 Ziggeo. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Ziggeo;

@interface ZiggeoCacheManager : NSObject

- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo isPlayer:(bool)isPlayer;

- (NSString *)getAudioCacheDirectory;
- (NSString *)getVideoCacheDirectory;
- (NSString *)getImageCacheDirectory;

- (NSString *)getCacheFullFileNameForVideoToken:(NSString *)token;
- (NSString *)getCacheFileNameForVideoToken:(NSString *)token;
- (NSString *)getCacheFullFileNameForAudioToken:(NSString *)token;
- (NSString *)getCacheFileNameForAudioToken:(NSString *)token;

- (void)trimAudioCache;
- (void)trimVideoCache;
- (void)trimImageCache;

@end
