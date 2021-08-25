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
#import "ZiggeoApiHelper.h"

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
- (void)ziggeoAudioRecorderFinished:(double)seconds;
@optional
- (void)ziggeoAudioRecorderPlaying;
@optional
- (void)ziggeoAudioRecorderPaused;
@end


@interface ZiggeoAudioRecorder : UIViewController

@property (nonatomic) id<ZiggeoAudioRecorderDelegate> recorderDelegate;
@property (nonatomic) id<ZiggeoApiDelegate> apiDelegate;

- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo;
- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo audioToken:(NSString*)audioToken;

@end
