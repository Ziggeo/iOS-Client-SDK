//
//  ZiggeoAudioPlayer.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZiggeoMediaSDK.h"
#import "ZiggeoApplication.h"
#import "ZiggeoCacheManager.h"


@interface ZiggeoAudioPlayer : UIViewController

- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo paths:(NSArray *)paths;

@end
