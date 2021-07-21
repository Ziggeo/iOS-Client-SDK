//
//  ZiggeoPhotoLibrary.h
//  Ziggeo
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

@import UIKit;

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
#import "CoverSelectorController.h"
#import "ZiggeoRecorder.h"


@interface ZiggeoPhotoLibrary : UIImagePickerController<UIImagePickerControllerDelegate,UINavigationControllerDelegate,CoverSelectorDelegate>

@property (nonatomic) bool coverSelectorEnabled;
@property (nonatomic) bool cameraFlipButtonVisible;
@property (nonatomic) id<ZiggeoRecorderDelegate> recorderDelegate;
@property (nonatomic) NSDictionary* extraArgsForCreateVideo;

-(id) initWithZiggeoApplication:(Ziggeo*)ziggeo;
-(id) initWithZiggeoApplication:(Ziggeo*)ziggeo videoToken:(NSString*)videoToken;
-(void) selectExistingVideo;

@end
