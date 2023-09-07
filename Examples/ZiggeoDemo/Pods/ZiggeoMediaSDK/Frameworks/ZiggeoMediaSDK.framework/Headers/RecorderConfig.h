//
//  RecorderConfig.h
//  ZiggeoMediaSDK
//
//  Created by Severyn on 07/24/23.
//  Copyright © 2023 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "CameraRecorderStyle.h"
#import "VideoSize.h"

@interface RecorderConfig : NSObject

@property (nonatomic, strong) CameraRecorderStyle *style;
@property (nonatomic) bool shouldShowFaceOutline;
@property (nonatomic, strong) UIImage *faceOutlineDrawable;
@property (nonatomic) bool isLiveStreaming;
@property (nonatomic) bool shouldAutoStartRecording;
@property (nonatomic) bool isImageOnlyMode;
@property (nonatomic) bool isPausedMode;
@property (nonatomic) int startDelay;
@property (nonatomic) bool shouldSendImmediately;
@property (nonatomic) bool shouldDisableCameraSwitch;
@property (nonatomic) int videoQuality;
@property (nonatomic) int facing;
@property (nonatomic) bool blurMode;
@property (nonatomic) long maxDuration;
@property (nonatomic) bool shouldEnableCoverShot;
@property (nonatomic) UIColor *colorForStoppedCameraOverlay;
@property (nonatomic) UIImage *drawableForStoppedCameraOverlay;
@property (nonatomic) bool shouldConfirmStopRecording;
@property (nonatomic, strong) VideoSize *resolution;
@property (nonatomic) int videoBitrate;
@property (nonatomic) int audioBitrate;
@property (nonatomic) int audioSampleRate;
@property (nonatomic, strong) NSDictionary *extraArgs;

- (CameraRecorderStyle *)getStyle;
- (void)setStyle:(CameraRecorderStyle *)style;
- (bool)getShouldShowFaceOutline;
- (void)setShouldShowFaceOutline:(bool)shouldShowFaceOutline;
- (UIImage *)getFaceOutlineDrawable;
- (void)setFaceOutlineDrawable:(UIImage *)faceOutlineDrawable;
- (bool)getIsLiveStreaming;
- (void)setLiveStreaming:(bool)liveStreaming;
- (bool)getShouldAutoStartRecording;
- (void)setShouldAutoStartRecording:(bool)shouldAutoStartRecording;
- (bool)getIsImageOnlyMode;
- (void)setImageOnlyMode:(bool)imageOnlyMode;
- (bool)getIsPausedMode;
- (void)setIsPausedMode:(bool)isPausedMode;
- (int)getStartDelay;
- (void)setStartDelay:(int)startDelay;
- (bool)getShouldSendImmediately;
- (void)setShouldSendImmediately:(bool)shouldSendImmediately;
- (bool)getShouldDisableCameraSwitch;
- (void)setShouldDisableCameraSwitch:(bool)shouldDisableCameraSwitch;
- (int)getVideoQuality;
- (void)setVideoQuality:(int)videoQuality;
- (int)getFacing;
- (void)setFacing:(int)facing;
- (bool)getBlurMode;
- (void)setBlurMode:(bool)blurMode;
- (long)getMaxDuration;
- (void)setMaxDuration:(long)maxDuration;
- (bool)getShouldEnableCoverShot;
- (void)setShouldEnableCoverShot:(bool)shouldEnableCoverShot;
- (UIColor *)getColorForStoppedCameraOverlay;
- (void)setColorForStoppedCameraOverlay:(UIColor *)colorForStoppedCameraOverlay;
- (UIImage *)getDrawableForStoppedCameraOverlay;
- (void)setDrawableForStoppedCameraOverlay:(UIImage *)drawableForStoppedCameraOverlay;
- (bool)getShouldConfirmStopRecording;
- (void)setShouldConfirmStopRecording:(bool)shouldConfirmStopRecording;
- (VideoSize *)getResolution;
- (void)setResolution:(VideoSize *)resolution;
- (int)getVideoBitrate;
- (void)setVideoBitrate:(int)videoBitrate;
- (int)getAudioBitrate;
- (void)setAudioBitrate:(int)audioBitrate;
- (int)getAudioSampleRate;
- (void)setAudioSampleRate:(int)rate;
- (NSMutableDictionary *)getExtraArgs;
- (void)setExtraArgs:(NSDictionary *)extraArgs;
- (void)addExtraArgs:(NSDictionary *)extraArgs;
- (NSString *)stringValueConfig;

@end
