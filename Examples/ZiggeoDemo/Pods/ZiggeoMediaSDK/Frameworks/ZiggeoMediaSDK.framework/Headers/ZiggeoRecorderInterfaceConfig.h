//
//  ZiggeoRecorderInterfaceConfig.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//


#import <Foundation/Foundation.h>

@class ButtonConfig;

@interface ZiggeoRecorderInterfaceConfig : NSObject

@property (nonatomic) ButtonConfig *recordButton;
@property (nonatomic) ButtonConfig *closeButton;
@property (nonatomic) ButtonConfig *cameraFlipButton;
@property (nonatomic) ButtonConfig *pauseButton;

@end
