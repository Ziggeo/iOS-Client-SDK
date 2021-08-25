//
//  ZiggeoChooseImage.h
//  Ziggeo
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

@import UIKit;

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
#import "ZiggeoApiHelper.h"

@protocol ZiggeoImagePickerDelegate <NSObject>
@optional
- (void)ziggeoImagePickerDidCancel;
@optional
- (void)ziggeoImagePickerDidSelected:(NSString *)imageFilePath;
@optional
- (void)ziggeoImagePickerDidFailed;
@end


@interface ZiggeoChooseImage : UIImagePickerController <UIImagePickerControllerDelegate, UINavigationControllerDelegate>

@property (nonatomic) id<ZiggeoImagePickerDelegate>imagePickerDelegate;
@property (nonatomic) id<ZiggeoApiDelegate> apiDelegate;

- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo;
- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo imageToken:(NSString*)imageToken;

@end
