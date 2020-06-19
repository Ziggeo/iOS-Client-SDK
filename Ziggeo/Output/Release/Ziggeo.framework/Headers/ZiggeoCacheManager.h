//
// Created by Admin on 10.06.2020.
// Copyright (c) 2020 Ziggeo. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Ziggeo;

@interface ZiggeoCacheManager : NSObject

- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo;

- (NSString *)getCacheDirectory;

- (NSString *)getCacheFullFileNameForVideoToken:(NSString *)token;

- (NSString *)getCacheFileNameForVideoToken:(NSString *)token;

- (void)trimCacheExcludingFile:(NSString *)fileNameToExclude;
@end
