//
//  FileSelectorConfig.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@interface FileSelectorConfig : NSObject

@property (nonatomic) long maxDuration;
@property (nonatomic) long minDuration;
@property (nonatomic) bool shouldAllowMultipleSelection;
@property (nonatomic) int mediaType;
@property (nonatomic, strong) NSDictionary *extraArgs;

- (long)getMaxDuration;
- (void)setMaxDuration:(long)maxDuration;
- (long)getMinDuration;
- (void)setMinDuration:(long)minDuration;
- (bool)getShouldAllowMultipleSelection;
- (void)setShouldAllowMultipleSelection:(bool)shouldAllowMultipleSelection;
- (int)getMediaType;
- (void)setMediaType:(int)mediaType;
- (NSMutableDictionary *)getExtraArgs;
- (void)setExtraArgs:(NSDictionary *)extraArgs;
- (void)addExtraArgs:(NSDictionary *)extraArgs;
- (NSString *)stringValueConfig;

@end
