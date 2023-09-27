//
//  CacheConfig.h
//  ZiggeoMediaSDK
//
//  Created by Severyn on 07/24/23.
//  Copyright © 2023 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@interface CacheConfig : NSObject

@property (nonatomic) int maxCacheSize;
@property (nonatomic) NSString *cacheRoot;

- (int)getMaxCacheSize;
- (void)setMaxCacheSize:(int)maxCacheSize;
- (NSString *)getCacheRoot;
- (void)setCacheRoot:(NSString *)cacheRoot;

- (NSString *)toString;
- (NSString *)stringValueConfig;

@end
