//
//  ZiggeoRecorder.h
//  Ziggeo
//
//  Created by alex on 07/04/16.
//  Copyright © 2016 Ziggeo. All rights reserved.
//

@import AVFoundation;
#import <UIKit/UIKit.h>
#import "ZiggeoApplication.h"

@interface ZiggeoAudioPlayer : UIViewController

- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo;
- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo audioToken:(NSString*)audioToken;
- (void)startRecordingToFile:(NSString *)outputFilePath;
- (void)stopRecording;
- (void)retake;
- (void)upload:(NSURL*)fileToUpload;

@end
