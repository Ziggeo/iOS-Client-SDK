//
//  VideoSize.h
//  ZiggeoMediaSDK
//
//  Created by Severyn on 07/24/23.
//  Copyright © 2023 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

@class AspectRatio;

@interface VideoSize : NSObject

@property (nonatomic) int width;
@property (nonatomic) int height;
@property (nonatomic) AspectRatio *aspectRatio;

- (instancetype)initWithWidth:(int)width height:(int)height;
- (instancetype)initWithWidth:(int)width height:(int)height aspectRatio:(AspectRatio *)aspectRatio;
- (int)getWidth;
- (int)getHeight;
- (AspectRatio *)getAspectRatio;
- (void)setAspectRatio:(AspectRatio *)aspectRatio;
- (bool)equals:(VideoSize *)size;
- (NSString *)toString;
- (int)compareTo:(VideoSize *)size;

@end
