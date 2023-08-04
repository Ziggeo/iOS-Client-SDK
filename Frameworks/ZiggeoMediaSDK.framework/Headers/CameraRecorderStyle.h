//
//  CameraRecorderStyle.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@interface CameraRecorderStyle : NSObject

@property (nonatomic) bool hideControls;

- (bool)getHideControls;
- (void)setHideControls:(bool)hideControls;

@end
