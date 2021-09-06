//
//  ZiggeoCacheManager.h
//
// Copyright (c) 2020 Ziggeo. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Ziggeo;

@interface ZiggeoCacheManager : NSObject

- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo isPlayer:(bool)isPlayer;

- (NSString *)getVideoCacheDirectory;
- (NSString *)getVideoCacheFilePathForToken:(NSString *)token;
- (NSString *)getVideoCacheFileNameForToken:(NSString *)token;
- (void)trimVideoCache;

- (NSString *)getAudioCacheDirectory;
- (NSString *)getAudioCacheFilePathForToken:(NSString *)token;
- (NSString *)getAudioCacheFileNameForToken:(NSString *)token;
- (void)trimAudioCache;

- (NSString *)getImageCacheDirectory;
- (NSString *)getImageCacheFilePathForToken:(NSString *)token;
- (NSString *)getImageCacheFileNameForToken:(NSString *)token;
- (void)trimImageCache;

- (bool)fileExists:(NSString *)filePath;
- (void)removeFile:(NSString *)filePath;

@end
