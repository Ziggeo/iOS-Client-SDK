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


@interface ViewController () <UINavigationControllerDelegate, UIImagePickerControllerDelegate, ZiggeoHardwarePermissionDelegate, ZiggeoUploadingDelegate, ZiggeoFileSelectorDelegate, ZiggeoRecorderDelegate, ZiggeoSensorDelegate, ZiggeoPlayerDelegate, ZiggeoScreenRecorderDelegate, ZiggeoQRScannerDelegate> {
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
    
    m_ziggeo = [[Ziggeo alloc] initWithToken:ZIGGEO_APP_TOKEN];
    [m_ziggeo setHardwarePermissionDelegate:self];
    [m_ziggeo setUploadingDelegate:self];
    [m_ziggeo setFileSelectorDelegate:self];
    [m_ziggeo setRecorderDelegate:self];
    [m_ziggeo setSensorDelegate:self];
    [m_ziggeo setPlayerDelegate:self];
    [m_ziggeo setScreenRecorderDelegate:self];
    
    currentType = Unknown;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}


// MARK: Button Click Action
- (IBAction)onRecordVideo:(id)sender {
    currentType = Video;

    NSMutableDictionary *themeMap = [NSMutableDictionary dictionary];
    [m_ziggeo setThemeArgsForRecorder:themeMap];
    
    NSMutableDictionary *config = [NSMutableDictionary dictionary];
//    config[@"data"] = @{@"foo": @"bar"};
//    config[@"client_auth"] = @"CLIENT_AUTH_TOKEN";
//    config[@"server_auth"] = @"SERVER_AUTH_TOKEN";
    config[@"tags"] = @"iOS_Video_Record";
    config[@"effect_profile"] = @"1234,5678";
    [m_ziggeo setExtraArgsForRecorder:config];

    [m_ziggeo setBlurMode:true];
    [m_ziggeo setCamera:REAR_CAMERA];
//    [m_ziggeo setMaxRecordingDuration:30];
    
    [m_ziggeo record];
}

- (IBAction)onPlayVideoWithToken:(id)sender {
    NSMutableDictionary *config = [NSMutableDictionary dictionary];
    config[@"hidePlayerControls"] = @"false";
    [m_ziggeo setThemeArgsForPlayer:config];
    
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
    [m_ziggeo setExtraArgsForRecorder:config];
    
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


// MARK: - ZiggeoHardwarePermissionDelegate
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

// MARK: - ZiggeoUploadingDelegate
- (void)preparingToUploadWithPath:(NSString*)sourcePath {
    NSLog(@"Preparing To Upload : %@", sourcePath);
}

- (void)failedToUploadWithPath:(NSString*)sourcePath {
    NSLog(@"Failed To Upload : %@", sourcePath);
}

- (void)uploadStartedWithPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken backgroundTask:(NSURLSessionTask*)uploadingTask {
    NSLog(@"Upload Started : %@ - %@", token, streamToken);
}

- (void)uploadProgressWithPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken totalBytesSent:(int)bytesSent totalBytesExpectedToSend:(int)totalBytes {
    NSLog(@"Upload Progress : %@ - %i - %i", token, bytesSent, totalBytes);
}

- (void)uploadFinishedWithPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken {
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

- (void)cancelUploadByPath:(NSString *)sourcePath deleteFile:(BOOL)deleteFile {
}

- (void)cancelCurrentUpload:(BOOL)deleteFile {
}

// MARL: - ZiggeoFileSelectorDelegate
- (void)uploadSelected:(NSArray *)paths {
    NSLog(@"Upload Selected: %@", paths);
}

- (void)uploadCancelledByUser {
    NSLog(@"Upload Cancelled By User");
}

// MARK: - ZiggeoRecorderDelegate
- (void)recorderReady {
    NSLog(@"Recorder Ready");
}

- (void)recorderCountdown:(int)secondsLeft {
    NSLog(@"Recorder Countdown left: %d", secondsLeft);
}

- (void)recorderStarted {
    NSLog(@"Ziggeo Recorder Started");
}

- (void)recorderStopped:(NSString *)path {
    NSLog(@"Ziggeo Recorder Stopped : %@", path);
}

- (void)recorderCurrentRecordedDurationSeconds:(double)seconds {
    NSLog(@"Recorder Current Recorded Duration Seconds : %f", seconds);
}

- (void)recorderPlaying {
    NSLog(@"Recorder Playing");
}

- (void)recorderPaused {
    NSLog(@"Recorder Paused");
}

- (void)recorderRerecord {
    NSLog(@"Recorder Rerecord");
}

- (void)recorderManuallySubmitted {
    NSLog(@"Recorder Manually Submitted");
}

- (void)streamingStarted {
    NSLog(@"Streaming Started");
}

- (void)streamingStopped {
    NSLog(@"Streaming Stopped");
}

- (void)recorderCancelledByUser {
    NSLog(@"Recorder Cancelled By User");
}


// MARK: - ZiggeoSensorDelegate
- (void)luxMeter:(double)luminousity {
    //NSLog(@"luminousity: %f", luminousity);
}

- (void)audioMeter:(double)audioLevel {
    //NSLog(@"audio: %f", audioLevel);
}

- (void)faceDetected:(int)faceID rect:(CGRect)rect {
    //NSLog(@"face %i detected with bounds: x = %f y = %f, size = %f x %f", faceID, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

// MARK: - ZiggeoPlayerDelegate
- (void)playerPlaying {
}

- (void)playerPaused {
}

- (void)playerEnded {
}

- (void)playerSeek:(double)positionMillis {
}

- (void)playerReadyToPlay {
}

- (void)playerCancelledByUser {
    NSLog(@"Player Cancelled By User");
}

// MARK: - ZiggeoQRScannerDelegate
- (void)qrCodeScaned:(NSString *)qrCode {
}

- (void)qrCodeScanCancelledByUser {
    NSLog(@"QR Code Scan Cancelled By User");
}

// MARK: - ZiggeoScreenRecorderDelegate

@end
