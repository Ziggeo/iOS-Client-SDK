//
// Copyright (c) 2020 Ziggeo. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ButtonConfig;

@interface ZiggeoRecorderInterfaceConfig : NSObject

@property (nonatomic) ButtonConfig *recordButton;

@property (nonatomic) ButtonConfig *closeButton;

@property (nonatomic) ButtonConfig *cameraFlipButton;

@end