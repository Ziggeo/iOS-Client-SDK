//
//  ZiggeoCacheManager.h
//
// Copyright (c) 2020 Ziggeo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"

@class Ziggeo;


@interface ZiggeoCacheManager : NSObject

- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo isPlayer:(bool)isPlayer;

- (NSString *)getCacheDirectoryWithType:(Media_Type)type;
- (NSString *)getCacheFilePathWithType:(Media_Type)type Token:(NSString *)token;
- (NSString *)getCacheFileNameWithType:(Media_Type)type Token:(NSString *)token;
- (void)trimCacheWithType:(Media_Type)type;

- (bool)fileExists:(NSString *)filePath;
- (void)removeFile:(NSString *)filePath;

@end
