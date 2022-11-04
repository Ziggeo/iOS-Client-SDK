//
//  ViewController.m
//  TestApp
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import <AVKit/AVKit.h>
#import <MobileCoreServices/MobileCoreServices.h>
#import "ViewController.h"
#import "ZiggeoMediaSDK/ZiggeoMediaSDK.h"


typedef enum {
    Video,
    Audio,
    Image,
    Unknown,
} CurrentType;


@interface ViewController () <UINavigationControllerDelegate, UIImagePickerControllerDelegate, ZiggeoDelegate> {
    Ziggeo* m_ziggeo;
    AVPlayerLayer* embeddedPlayerLayer;
    CurrentType currentType;
}

@end


@implementation ViewController

NSString *ZIGGEO_APP_TOKEN = @"ZIGGEO_APP_TOKEN";
NSString *SERVER_AUTH_TOKEN = @"SERVER_AUTH_TOKEN";
NSString *CLIENT_AUTH_TOKEN = @"CLIENT_AUTH_TOKEN";

NSString *Last_Video_Token = @"Last_Video_Token";
NSString *Last_Audio_Token = @"Last_Audio_Token";
NSString *Last_Image_Token = @"Last_Image_Token";

- (void)viewDidLoad {
    [super viewDidLoad];
    
    m_ziggeo = [[Ziggeo alloc] initWithToken:ZIGGEO_APP_TOKEN Delegate:self];
    currentType = Unknown;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}


// MARK: Button Click Action

- (IBAction)onRecordVideo:(id)sender {
    currentType = Video;

    NSMutableDictionary *config = [NSMutableDictionary dictionary];
    config[@"tags"] = @"iOS_Video_Record";
    config[@"effect_profile"] = @"1234,5678";
    [m_ziggeo setUploadingConfig:config];
    
    NSMutableDictionary *themeMap = [NSMutableDictionary dictionary];
    [m_ziggeo setThemeArgsForRecorder:themeMap];
    
    NSMutableDictionary *map = [NSMutableDictionary dictionary];
//    map[@"data"] = @{@"foo": @"bar"};
//    map[@"client_auth"] = @"CLIENT_AUTH_TOKEN";
//    map[@"server_auth"] = @"SERVER_AUTH_TOKEN";
    [m_ziggeo setExtraArgsForRecorder:map];

    [m_ziggeo setBlurMode:true];
    [m_ziggeo setCamera:REAR_CAMERA];
//    [m_ziggeo setMaxRecordingDuration:30];
    
    [m_ziggeo record];
}

- (IBAction)onPlayVideoWithToken:(id)sender {
    NSMutableDictionary *map = [NSMutableDictionary dictionary];
    map[@"hidePlayerControls"] = @"false";
    [m_ziggeo setThemeArgsForPlayer:map];
    
    [m_ziggeo playVideo:@[Last_Video_Token]];
}

- (IBAction)onChooseMedia:(id)sender {
    currentType = Unknown;
    
    NSMutableDictionary *config = [NSMutableDictionary dictionary];
    config[@"tags"] = @"iOS_Choose_Media";
    [m_ziggeo setUploadingConfig:config];
    
    NSMutableDictionary *data = [NSMutableDictionary dictionary];
//    data[ARG_MEDIA_TYPE] = @[@"video", @"image"];
//    data[ARG_DURATION] = @"20";
    [m_ziggeo uploadFromFileSelector:data];
}

- (IBAction)onRecordAudio:(id)sender {
    currentType = Audio;
    
    NSMutableDictionary *config = [NSMutableDictionary dictionary];
    config[@"tags"] = @"iOS_Audio_Record";
    [m_ziggeo setUploadingConfig:config];
    
    [m_ziggeo startAudioRecorder];
}

- (IBAction)onPlayAudio:(id)sender {
    [m_ziggeo startAudioPlayer:@[Last_Audio_Token]];
}

- (IBAction)onTakePhoto:(id)sender {
    currentType = Image;
    
    NSMutableDictionary *config = [NSMutableDictionary dictionary];
    config[@"tags"] = @"iOS_Take_Photo";
    [m_ziggeo setUploadingConfig:config];
    
    [m_ziggeo startImageRecorder];
}

- (IBAction)onShowImage:(id)sender {
    [m_ziggeo showImage:@[Last_Image_Token]];
}


// MARK: - ZiggeoRecorderDelegate
- (void)ziggeoRecorderReady {
    NSLog(@"Ziggeo Recorder Ready");
}

- (void) ziggeoRecorderCanceled {
    NSLog(@"Ziggeo Recorder Canceled");
}

- (void)ziggeoRecorderCountdown:(int)secondsLeft {
    NSLog(@"Ziggeo Recorder Countdown left: %d", secondsLeft);
}

- (void)ziggeoRecorderStarted {
    NSLog(@"Ziggeo Recorder Started");
}

- (void)ziggeoRecorderStopped:(NSString *)path {
    NSLog(@"Ziggeo Recorder Stopped : %@", path);
}

- (void)ziggeoRecorderCurrentRecordedDurationSeconds:(double)seconds {
    NSLog(@"Ziggeo Recorder Current Recorded Duration Seconds : %f", seconds);
}

- (void)ziggeoRecorderPlaying {
    NSLog(@"Ziggeo Recorder Playing");
}

- (void)ziggeoRecorderPaused {
    NSLog(@"Ziggeo Recorder Paused");
}

- (void)ziggeoRecorderRerecord {
    NSLog(@"Ziggeo Recorder Rerecord");
}

- (void)ziggeoRecorderManuallySubmitted {
    NSLog(@"Ziggeo Recorder Manually Submitted");
}

- (void)ziggeoStreamingStarted {
    NSLog(@"Ziggeo Streaming Started");
}

- (void)ziggeoStreamingStopped {
    NSLog(@"Ziggeo Streaming Stopped");
}

- (void)luxMeter:(double)luminousity {
    //NSLog(@"luminousity: %f", luminousity);
}

- (void)audioMeter:(double)audioLevel {
    //NSLog(@"audio: %f", audioLevel);
}

- (void)faceDetected:(int)faceID rect:(CGRect)rect {
    //NSLog(@"face %i detected with bounds: x = %f y = %f, size = %f x %f", faceID, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

// MARK: - ZiggeoUploadDelegate
- (void)ziggeoUploadCancelledByUser {
    NSLog(@"Upload cancelled by user");
}

- (void)ziggeoUploadSelected:(NSArray *)paths {
    NSLog(@"Upload Selected: %@", paths);
}

- (void)preparingToUploadWithPath:(NSString*)sourcePath {
    NSLog(@"Preparing To Upload : %@", sourcePath);
}

- (void)failedToUploadWithPath:(NSString*)sourcePath {
    NSLog(@"Failed To Upload : %@", sourcePath);
}

- (void)uploadStartedWithPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken backgroundTask:(NSURLSessionTask*)uploadingTask {
    NSLog(@"Upload Started : %@ - %@", token, streamToken);
}

- (void)uploadProgressForPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken totalBytesSent:(int)bytesSent totalBytesExpectedToSend:(int)totalBytes {
    NSLog(@"Upload Progress : %@ - %i - %i", token, bytesSent, totalBytes);
}

- (void)uploadFinishedForPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken {
    NSLog(@"Upload Finished : %@ - %@", token, streamToken);
}

- (void)uploadVerifiedWithPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken withResponse:(NSURLResponse*)response error:(NSError*)error json:(NSDictionary*)json {
    NSLog(@"Upload Verified : %@", token);
    if (currentType == Video) {
        Last_Video_Token = token;
    } else if (currentType == Audio) {
        Last_Audio_Token = token;
    } else if (currentType == Image) {
        Last_Image_Token = token;
    }
}

- (void)uploadProcessingWithPath:(NSString *)sourcePath token:(NSString *)token streamToken:(NSString *)streamToken {
    NSLog(@"Upload Processing : %@ - %@", token, streamToken);
}

- (void)uploadProcessedWithPath:(NSString *)sourcePath token:(NSString *)token streamToken:(NSString *)streamToken {
    NSLog(@"Upload Processed : %@ - %@", token, streamToken);
}

- (void)deleteWithToken:(NSString*)token streamToken:(NSString*)streamToken withResponse:(NSURLResponse*)response error:(NSError*)error json:(NSDictionary*)json {
    NSLog(@"Delete : %@ - %@", token, streamToken);
}


// MARK: - ZiggeoHardwarePermissionCheckDelegate
- (void)checkCameraPermission:(BOOL)granted {
    NSLog(@"Check Camera Permission : %d", granted);
}

- (void)checkMicrophonePermission:(BOOL)granted {
    NSLog(@"Check Microphone Permission : %d", granted);
}

- (void)checkPhotoLibraryPermission:(BOOL)granted {
    NSLog(@"Check Photo Library Permission : %d", granted);
}

- (void)checkHasCamera:(BOOL)hasCamera {
    NSLog(@"Check Has Camera : %d", hasCamera);
}

- (void)checkHasMicrophone:(BOOL)hasMicrophone {
    NSLog(@"Check Has Microphone : %d", hasMicrophone);
}


// MARK: - ZiggeoPlayerDelegate
- (void)ziggeoPlayerPlaying {
    
}

- (void)ziggeoPlayerPaused {
    
}

- (void)ziggeoPlayerEnded {
    
}

- (void)ziggeoPlayerSeek:(double)positionMillis {
    
}

- (void)ziggeoPlayerReadyToPlay {
    
}

- (void)ziggeoPlayerCancelledByUser {
    
}

@end
