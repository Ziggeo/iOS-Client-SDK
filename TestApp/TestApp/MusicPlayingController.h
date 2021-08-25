//
//  MusicPlayingController.h
//  TestApp
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Ziggeo/Ziggeo.h"


@interface MusicPlayingController : UIViewController

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil ziggeo:(Ziggeo *)ziggeo audioToken:(NSString *)audioToken;

@end
