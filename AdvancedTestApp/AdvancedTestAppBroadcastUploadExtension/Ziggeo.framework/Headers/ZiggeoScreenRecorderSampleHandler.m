#import "ZiggeoScreenRecorderSampleHandler.h"
@import Foundation;
@import ReplayKit;
@import Photos;

//@available(iOS 10.0, macCatalyst 13.0, *)
@implementation ZiggeoScreenRecorderSampleHandler {

    bool isRecordingVideo;

    NSURL *videoOutputFullFileName;

    AVAssetWriterInput *videoWriterInput;

    AVAssetWriterInputPixelBufferAdaptor *adapter;

    AVAssetWriterInput *audioWriterInput;

    AVAssetWriter *videoWriter;

    CMTime lastSampleTime;

    double _time;

}

- (void)broadcastStartedWithSetupInfo:(NSDictionary<NSString *,NSObject *> *)setupInfo {
    NSString *filename = [[[NSUUID UUID] UUIDString] stringByAppendingPathExtension:@"mov"];

    NSURL *directory = [NSURL fileURLWithPath: NSTemporaryDirectory() isDirectory: true];

    NSString *videoOutputFullFileNameString = [[directory absoluteString] stringByAppendingPathComponent:filename];
    videoOutputFullFileName = [NSURL fileURLWithPath:videoOutputFullFileNameString];

    NSLog(@"Video file name: %@", videoOutputFullFileName.absoluteString);

    NSLog(@"Starting screen capture...");

    UIScreen *screen = [UIScreen mainScreen];
    CGRect screenBounds = screen.bounds;

    NSMutableDictionary<NSString *, id> *videoSettings = [[NSMutableDictionary alloc] initWithDictionary:@{
        AVVideoWidthKey: @(screenBounds.size.width),
        AVVideoHeightKey: @(screenBounds.size.height),
        //AVVideoCompressionPropertiesKey: videoCompressionProperties
    }];

    if (@available(iOS 11, *)) {
        videoSettings[AVVideoCodecKey] = AVVideoCodecTypeH264;
    }

    if (videoOutputFullFileName == nil) {
        NSLog(@"Failed to generate videoOutputFullFileName");
        return;
    }

    CGRect inputSize = screenBounds;
    CGRect outputSize = screenBounds;

    NSError *error = nil;

    [[NSFileManager defaultManager] removeItemAtPath:[videoOutputFullFileName absoluteString] error:&error];

    NSError *writerError = nil;

    videoWriter = [[AVAssetWriter alloc] initWithURL:videoOutputFullFileName fileType:AVFileTypeQuickTimeMovie error:&writerError];
    if (writerError != nil) {
        error = writerError;
        videoWriter = nil;
    }

    if (videoWriter == nil) {
        NSLog(@"Failed to initialize videoWriter");
        return;
    }

    videoWriterInput = [[AVAssetWriterInput alloc] initWithMediaType:AVMediaTypeVideo outputSettings:videoSettings];

    if (videoWriterInput == nil) {
        NSLog(@"Failed to instantiate AVAssetWriterInput");
        return;
    }

    NSDictionary<NSString *, id> *sourceBufferAttributes = @{
        (NSString *)kCVPixelBufferPixelFormatTypeKey: @(kCVPixelFormatType_32ARGB),
        (NSString *)kCVPixelBufferWidthKey: @(inputSize.size.width),
        (NSString *)kCVPixelBufferHeightKey: @(inputSize.size.height),
    };

    adapter = [[AVAssetWriterInputPixelBufferAdaptor alloc] initWithAssetWriterInput:videoWriterInput sourcePixelBufferAttributes:sourceBufferAttributes];

    assert([videoWriter canAddInput:videoWriterInput]);
    [videoWriter addInput:videoWriterInput];

    NSLog(@"videoWriter.startWriting()...");

    if (![videoWriter startWriting]) {
        NSLog(@"Failed to start writing");
        return;
    }

    NSLog(@"videoWriter.startWriting() SUCCESS");
    [videoWriter startSessionAtSourceTime: kCMTimeZero];
    NSLog(@"videoWriter.startSession() success");

    isRecordingVideo = true;
}

- (void)broadcastPaused {
    // User has requested to pause the broadcast. Samples will stop being delivered.
}

- (void)processSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType {
    switch (sampleBufferType) {
        case RPSampleBufferTypeVideo:
            // streamer.appendSampleBuffer(sampleBuffer, withType: .video)
            [self captureOutput:sampleBuffer];

            break;
        case RPSampleBufferTypeAudioApp:
            // streamer.appendSampleBuffer(sampleBuffer, withType: .audio)
//            captureAudioOutput(sampleBuffer)

            break;
        case RPSampleBufferTypeAudioMic:
            // Handle audio sample buffer for mic audio
            break;
    }
}

- (void)captureOutput:(CMSampleBufferRef)sampleBuffer {
    NSLog(@"Capturing sample buffer");
    double timestamp = CMTimeGetSeconds(CMSampleBufferGetPresentationTimeStamp(sampleBuffer));

    if (videoWriterInput.isReadyForMoreMediaData) {
        CMTime time = CMTimeMake((int64_t)(timestamp - _time), (CMTimeScale)600);
        if (adapter != nil) {
            [adapter appendPixelBuffer:CMSampleBufferGetImageBuffer(sampleBuffer) withPresentationTime:time];
        }
        NSLog(@"Capture success");
    }
}

- (void)broadcastFinished {
    if (videoWriter == nil) {
        return;
    }

    NSLog(@"Finishing capture");
    NSLog(@"videoWriter.status: %li", (long)videoWriter.status);

    if (videoWriterInput == nil) {
        return;
    }

    if (!videoWriterInput.isReadyForMoreMediaData == NO) {
        NSLog(@"Error: videoWriterInput?.isReadyForMoreMediaData == false");
        return;
    }

    if (videoWriter.status == AVAssetWriterStatusFailed) {
        NSLog(@"Error: videoWriter!.status == .failed");
        return;
    }

    NSLog(@"videoWriterInput?.markAsFinished()...");
    [videoWriterInput markAsFinished];
    NSLog(@"OK");

    NSLog(@"videoWriter?.finishWriting()...");

    [videoWriter finishWritingWithCompletionHandler:^{
        NSLog(@"videoWriter?.finishWriting() DONE!");

        int64_t size = -1;
        NSURL *url = self->videoOutputFullFileName;

        if (url != nil) {
            size = [self fileSize:url];
        }
        NSLog(@"Output file size: %lli", size);

        // todo notify the app that recording finished
        self->isRecordingVideo = false;
    }];

    NSLog(@"videoWriter.status: %li", (long)videoWriter.status);
    NSLog(@"OK. finishWriting() is now continue running asynchronously...");

    while (videoWriter.status == AVAssetWriterStatusWriting && isRecordingVideo) {
        [NSThread sleepForTimeInterval: 1];
    }
}

- (int64_t) fileSize:(NSURL*)url {
    NSError *error = nil;

    NSDictionary<NSFileAttributeKey, id> *fileAttributes = [[NSFileManager defaultManager] attributesOfItemAtPath:url.path error:&error];

    if (fileAttributes == nil) {
        return -1;
    }

    return [fileAttributes fileSize];
}

@end
