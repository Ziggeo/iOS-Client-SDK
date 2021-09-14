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
#import "ZiggeoVideos.h"

@protocol ZiggeoAudioRecorderDelegate <NSObject>
@optional
- (void)ziggeoAudioRecorderReady;
@optional
- (void)ziggeoAudioRecorderCanceled;
@optional
- (void)ziggeoAudioRecorderRecoding;
@optional
- (void)ziggeoAudioRecorderCurrentRecordedDurationSeconds:(double)seconds;
@optional
- (void)ziggeoAudioRecorderFinished:(NSString *)path;
@optional
- (void)ziggeoAudioRecorderPlaying;
@optional
- (void)ziggeoAudioRecorderPaused;
@optional
- (void)ziggeoAudioRecorderRerecord;
@optional
- (void)ziggeoAudioRecorderManuallySubmitted;
@end


@interface ZiggeoAudioRecorder : UIViewController

@property (nonatomic) id<ZiggeoAudioRecorderDelegate> recorderDelegate;
@property (nonatomic) id<ZiggeoUploadDelegate> uploadDelegate;

- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo;
- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo audioToken:(NSString *)audioToken;

@end
