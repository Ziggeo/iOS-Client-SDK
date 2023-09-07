//
//  ZiggeoCacheManager.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"


@class Ziggeo;

@interface ZiggeoCacheManager : NSObject

- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo
                       isPlayer:(bool)isPlayer;
- (NSString *)getCacheDirectoryWithType:(int)type;
- (NSString *)getCacheFilePathWithType:(int)type
                                 token:(NSString *)token;
- (NSString *)getCacheFileNameWithType:(int)type
                                 token:(NSString *)token;
- (void)trimCacheWithType:(int)type;
- (bool)fileExists:(NSString *)filePath;
- (void)removeFile:(NSString *)filePath;

@end
