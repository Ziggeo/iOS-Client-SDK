//
//  SampleHandler.m
//  AdvancedTestAppBroadcastUploadExtension
//
//  Created by Admin on 30.08.2020.
//  Copyright © 2020 Ziggeo. All rights reserved.
//


#import "SampleHandler.h"
#import <Ziggeo/Streamer.h>

@implementation SampleHandler

@property (nonatomic) LiveStreamer* liveStreamer;

- (void)broadcastStartedWithSetupInfo:(NSDictionary<NSString *,NSObject *> *)setupInfo {
    // User has requested to start the broadcast. Setup info from the UI extension can be supplied but optional.


    self.liveStreamer = [[LiveStreamer alloc] initWithTargetAddress:targetAddress streamName:streamAddress];
}

- (void)broadcastPaused {
    // User has requested to pause the broadcast. Samples will stop being delivered.
}

- (void)broadcastResumed {
    // User has requested to resume the broadcast. Samples delivery will resume.
}

- (void)broadcastFinished {
    // User has requested to finish the broadcast.
}

- (void)processSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType {
    
    switch (sampleBufferType) {
        case RPSampleBufferTypeVideo:
            if (self.liveStreamer != nil && _streamingNow) {
                [self.liveStreamer putVideoSample:sampleBuffer];
            }
            break;
        case RPSampleBufferTypeAudioApp:
            if (self.liveStreamer != nil) {
                [self.liveStreamer putAudioSample:sampleBuffer asc:asc pts:pts];
            }
            break;
        case RPSampleBufferTypeAudioMic:
            // Handle audio sample buffer for mic audio
            break;
            
        default:
            break;
    }
}

@end
