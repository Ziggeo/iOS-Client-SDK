//
//  ZiggeoRecorder.h
//  ZiggeoFramework
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

@import AVFoundation;

#import <UIKit/UIKit.h>
#import "ZiggeoApplication.h"
#import "ZiggeoConfig.h"
#import "ZiggeoRecordedVideoPreview.h"

@class ZiggeoRecorderInterfaceConfig;

typedef enum : NSUInteger {
    LowQuality,
    MediumQuality,
    HighestQuality,
} RecordingQuality;


@interface ZiggeoRecorder : UIViewController

@property (nonatomic) UIViewController<VideoPreviewProtocol>* videoPreview;
@property (nonatomic) bool coverSelectorEnabled;
@property (nonatomic) bool sendImmediately;
@property (nonatomic) bool cameraFlipButtonVisible;
@property (nonatomic) bool useLiveStreaming;
@property (nonatomic) bool controlsVisible;
@property (nonatomic) bool showFaceOutline;
@property (nonatomic) bool showLightIndicator;
@property (nonatomic) bool showSoundIndicator;
@property (nonatomic) ZiggeoRecorderInterfaceConfig *interfaceConfig;
@property (nonatomic) double maxRecordedDurationSeconds;
@property (nonatomic) double autostartRecordingAfterSeconds;
@property (nonatomic) double startDelay;
@property (nonatomic) AVLayerVideoGravity videoGravity;
//resolution
@property (nonatomic) int videoWidth;
@property (nonatomic) int videoHeight;
@property (nonatomic) RecordingQuality recordingQuality;
@property (nonatomic) int videoBitrate;
@property (nonatomic) int audioSampleRate;
@property (nonatomic) int audioBitrate;
// blurring
@property (nonatomic) bool useFrontCamera;
@property (nonatomic) bool blurMode;


- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo;
- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo videoToken:(NSString *)videoToken;
- (void)startRecordingToFile:(NSString *)outputFilePath;
- (void)stopRecording;
- (void)retake;
- (void)uploadVideo:(NSString *)filePath;

@end
