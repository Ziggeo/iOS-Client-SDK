//
//  AspectRatio.h
//  ZiggeoMediaSDK
//
//  Created by Severyn on 07/24/23.
//  Copyright © 2023 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@class VideoSize;

@interface AspectRatio : NSObject

@property (nonatomic) int mX;
@property (nonatomic) int mY;

- (instancetype)initWithX:(int)x y:(int)y;
+ (int)gcd:(int)a :(int)b;
+ (AspectRatio *)of:(int)width :(int)height;
+ (AspectRatio *)parse:(NSString *)string;
- (int)getX;
- (int)getY;
- (NSString *)toString;
- (float)toFloat;
- (bool)matches:(VideoSize *)size;
- (bool)equals:(AspectRatio *)ratio;
- (int)compareTo:(AspectRatio *)ratio;
- (AspectRatio *)inverse;

@end
