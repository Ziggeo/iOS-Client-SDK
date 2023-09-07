//
//  CameraRecorderStyle.h
//  ZiggeoMediaSDK
//
//  Created by Severyn on 07/24/23.
//  Copyright © 2023 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@interface CameraRecorderStyle : NSObject

@property (nonatomic) bool hideControls;

- (bool)getHideControls;
- (void)setHideControls:(bool)hideControls;

@end
