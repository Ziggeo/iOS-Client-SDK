//
//  ZiggeoRecorder.h
//  Ziggeo
//
//  Created by alex on 07/04/16.
//  Copyright © 2016 Ziggeo. All rights reserved.
//

@import AVFoundation;

#import <UIKit/UIKit.h>
#import "RecordedVideoPreview.h"
#import "ZiggeoApplication.h"


@class ZiggeoRecorderInterfaceConfig;

@protocol ZiggeoRecorderDelegate <NSObject>
@optional
- (void)ziggeoRecorderDidCancel;
@optional
- (void)ziggeoRecorderDidStop;
@optional
- (void)ziggeoRecorderCurrentRecordedDurationSeconds:(double)seconds;
@optional
- (void)luxMeter:(double)luminousity;
@optional
- (void)audioMeter:(double)audioLevel;
@optional
- (void)faceDetected:(int)faceID rect:(CGRect)rect;
@end

typedef enum : NSUInteger {
    LowQuality,
    MediumQuality,
    HighestQuality,
} RecordingQuality;


@interface ZiggeoRecorder : UIViewController <VideoPreviewDelegate>

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
@property (nonatomic) UIImagePickerControllerCameraDevice cameraDevice;
@property (nonatomic) id<ZiggeoRecorderDelegate> recorderDelegate;
@property (nonatomic) NSDictionary* extraArgsForCreateVideo;
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

- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo;
- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo videoToken:(NSString*)videoToken;
- (void)startRecordingToFile:(NSString *)outputFilePath;
- (void)stopRecording;
- (void)retake;
- (void)upload:(NSURL*)fileToUpload;

@end
