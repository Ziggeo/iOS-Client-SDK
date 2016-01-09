//
//  ZiggeoRecorder.h
//  Ziggeo
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
#import "CoverSelectorController.h"
@import UIKit;

@interface ZiggeoRecorder : UIImagePickerController<UIImagePickerControllerDelegate,UINavigationControllerDelegate,CoverSelectorDelegate>

-(id) initWithZiggeoApplication:(Ziggeo*)ziggeo;
@property (nonatomic) bool coverSelectorEnabled;

-(void) selectExistingVideo;

@end
