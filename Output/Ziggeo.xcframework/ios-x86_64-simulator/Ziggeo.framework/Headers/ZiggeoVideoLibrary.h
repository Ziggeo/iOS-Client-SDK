//
//  ZiggeoVideoLibrary.h
//  Ziggeo
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

@import UIKit;

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
#import "CoverSelectorController.h"
#import "ZiggeoRecorder.h"
#import "ZiggeoUploadingHandler.h"


@interface ZiggeoVideoLibrary : UIImagePickerController<UIImagePickerControllerDelegate, UINavigationControllerDelegate>

@property (nonatomic) bool coverSelectorEnabled;
@property (nonatomic) bool cameraFlipButtonVisible;

- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo;
- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo videoToken:(NSString *)videoToken;
- (void)selectExistingVideo;

@end
