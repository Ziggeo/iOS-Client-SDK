//
//  ZiggeoRecorder.h
//  Ziggeo
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
@import UIKit;

@interface ZiggeoRecorder : UIImagePickerController<UIImagePickerControllerDelegate,UINavigationControllerDelegate>

-(id) initWithZiggeoApplication:(Ziggeo*)ziggeo;

@end
