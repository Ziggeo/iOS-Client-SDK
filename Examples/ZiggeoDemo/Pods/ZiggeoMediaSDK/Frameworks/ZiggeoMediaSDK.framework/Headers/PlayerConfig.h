//
//  PlayerConfig.h
//  ZiggeoMediaSDK
//
//  Created by Severyn on 07/24/23.
//  Copyright © 2023 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@interface PlayerConfig : NSObject

@property (nonatomic) bool shouldShowSubtitles;
@property (nonatomic) bool shouldPreload;
@property (nonatomic) bool isMuted;
@property (nonatomic) bool isCachingEnabled;
@property (nonatomic, strong) NSString *adsUri;
@property (nonatomic, strong) NSDictionary *extraArgs;

- (bool)getShouldShowSubtitles;
- (void)setShouldShowSubtitles:(bool)shouldShowSubtitles;
- (bool)getShouldPreload;
- (void)setShouldPreload:(bool)shouldPreload;
- (bool)getIsMuted;
- (void)setIsMuted:(bool)isMuted;
- (bool)getIsCachingEnabled;
- (void)setIsCachingEnabled:(bool)isCachingEnabled;
- (NSString *)getAdsUri;
- (void)setAdsUri:(NSString *)adsUri;
- (NSMutableDictionary *)getExtraArgs;
- (void)setExtraArgs:(NSDictionary *)extraArgs;
- (void)addExtraArgs:(NSDictionary *)extraArgs;
- (NSString *)toString;
- (NSString *)stringValueConfig;

@end
