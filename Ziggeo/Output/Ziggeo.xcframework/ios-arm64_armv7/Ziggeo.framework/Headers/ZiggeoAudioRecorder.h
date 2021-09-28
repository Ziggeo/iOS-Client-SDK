//
//  ZiggeoAudioRecorder.h
//  Ziggeo
//
//  Created by alex on 07/04/16.
//  Copyright © 2016 Ziggeo. All rights reserved.
//

@import AVFoundation;
#import <UIKit/UIKit.h>
#import "ZiggeoApplication.h"
#import "ZiggeoConfig.h"


@interface ZiggeoAudioRecorder : UIViewController

@property (nonatomic) id<ZiggeoRecorderDelegate> recorderDelegate;
@property (nonatomic) id<ZiggeoUploadDelegate> uploadDelegate;

- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo;
- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo audioToken:(NSString *)audioToken;

@end
