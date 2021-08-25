//
//  ZiggeoImagePicker.h
//  Ziggeo
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

@import UIKit;

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"


@interface ZiggeoTakePhoto : UIImagePickerController <UIImagePickerControllerDelegate, UINavigationControllerDelegate>

@property (nonatomic) bool cameraFlipButtonVisible;
@property (nonatomic) id<ZiggeoRecorderDelegate> recorderDelegate;
@property (nonatomic) NSDictionary* extraArgsForCreateVideo;

- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo;
- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo imageToken:(NSString*)imageToken;


@end
