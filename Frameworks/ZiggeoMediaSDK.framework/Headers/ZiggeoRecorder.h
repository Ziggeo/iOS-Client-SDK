//
//  ZiggeoRecorder.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

@import AVFoundation;

#import <UIKit/UIKit.h>
#import "ZiggeoApplication.h"
#import "ZiggeoConfig.h"
#import "ZiggeoRecordedVideoPreview.h"
#import "RecorderConfig.h"

@class RecorderInterfaceConfig;


@interface ZiggeoRecorder : UIViewController

@property (nonatomic) UIViewController<VideoPreviewProtocol>* videoPreview;

@property (nonatomic) bool showLightIndicator;
@property (nonatomic) bool showSoundIndicator;
@property (nonatomic) RecorderInterfaceConfig *interfaceConfig;
@property (nonatomic) AVLayerVideoGravity videoGravity;


- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo;
- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo videoToken:(NSString *)videoToken;
- (void)startRecordingToFile:(NSString *)outputFilePath;
- (void)stopRecording;
- (void)retake;
- (void)pauseStreaming;
- (void)resumeStreaming;
- (void)uploadVideo:(NSString *)filePath;

@end
