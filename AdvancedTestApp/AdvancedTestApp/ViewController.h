//
//  ViewController.h
//  test
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Ziggeo/Ziggeo.h"

@interface ViewController : UITableViewController <ZiggeoVideosDelegate>

@property (strong) Ziggeo *ziggeo;

@end

