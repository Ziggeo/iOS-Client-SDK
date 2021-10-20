//
//  ZiggeoAudioPlayer.h
//  TestApp
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Ziggeo.h"
#import "ZiggeoApplication.h"
#import "ZiggeoCacheManager.h"


@interface ZiggeoAudioPlayer : UIViewController

- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo audioToken:(NSString *)audioToken;

@end
