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
#import "CustomUIRecroderViewController.h"


@interface ViewController () <UINavigationControllerDelegate, UIImagePickerControllerDelegate, ZiggeoHardwarePermissionDelegate, ZiggeoUploadingDelegate, ZiggeoFileSelectorDelegate, ZiggeoRecorderDelegate, ZiggeoSensorDelegate, ZiggeoPlayerDelegate, ZiggeoScreenRecorderDelegate, ZiggeoQRScannerDelegate> {
    Ziggeo* m_ziggeo;
    AVPlayerLayer* embeddedPlayerLayer;
    int currentType;
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
    
    currentType = 0;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}


// MARK: Button Click Action
- (IBAction)onRecordVideo:(id)sender {
    currentType = VIDEO;
    
    RecorderConfig *recorderConfig = [[RecorderConfig alloc] init];
    [recorderConfig setShouldAutoStartRecording:true];
    [recorderConfig setStartDelay:DEFAULT_START_DELAY];
    [recorderConfig setShouldDisableCameraSwitch:false];
    [recorderConfig setVideoQuality:QUALITY_HIGH];
    [recorderConfig setFacing:FACING_BACK];
    [recorderConfig setMaxDuration:0];
    [recorderConfig setBlurMode:true];
    [recorderConfig.resolution setAspectRatio:DEFAULT_ASPECT_RATIO];
    [recorderConfig setExtraArgs:@{@"tags": @"iOS,Video,Record",
                                   @"client_auth" : @"CLIENT_AUTH_TOKEN",
                                   @"server_auth" : @"SERVER_AUTH_TOKEN",
                                   @"data" : @{@"foo": @"bar"},
                                   @"effect_profile" : @"1234,5678"}];
    [m_ziggeo setRecorderConfig:recorderConfig];
    
    [m_ziggeo record];
}

- (IBAction)onPlayVideoWithToken:(id)sender {
    PlayerConfig *playerConfig = [[PlayerConfig alloc] init];
    [playerConfig setAdsUri:@"https://pubads.g.doubleclick.net/gampad/ads?"
     @"iu=/21775744923/external/single_ad_samples&sz=640x480&cust_params=sample_ct%3Dlinear&"
     @"ciu_szs=300x250%2C728x90&gdfp_req=1&output=vast&unviewed_position_start=1&env=vp&"
     @"impl=s&correlator="];
    [m_ziggeo setPlayerConfig:playerConfig];

    [m_ziggeo playVideo:Last_Video_Token];
}

- (IBAction)onChooseMedia:(id)sender {
    currentType = 0;
    
    FileSelectorConfig *fileSelectorConfig = [[FileSelectorConfig alloc] init];
    [fileSelectorConfig setMaxDuration:0];
    [fileSelectorConfig setMinDuration:0];
    [fileSelectorConfig setShouldAllowMultipleSelection:true];
    [fileSelectorConfig setMediaType:VIDEO | AUDIO | IMAGE];
    [fileSelectorConfig setExtraArgs:@{@"tags" : @"iOS,Choose,Media"}];
    [m_ziggeo setFileSelectorConfig:fileSelectorConfig];

    [m_ziggeo startFileSelector];
}

- (IBAction)onRecordAudio:(id)sender {
    currentType = AUDIO;
    
    RecorderConfig *recorderConfig = [[RecorderConfig alloc] init];
    [recorderConfig setIsPausedMode:true];
    [recorderConfig setExtraArgs:@{@"tags": @"iOS,Audio,Record"}];
    [m_ziggeo setRecorderConfig:recorderConfig];
    
    [m_ziggeo startAudioRecorder];
}

- (IBAction)onPlayAudio:(id)sender {
    [m_ziggeo startAudioPlayer:Last_Audio_Token];
}

- (IBAction)onTakePhoto:(id)sender {
    currentType = IMAGE;
    
    UploadingConfig *uploadingConfig = [[UploadingConfig alloc] init];
    [uploadingConfig setExtraArgs:@{@"tags": @"iOS,Take,Photo"}];
    [m_ziggeo setUploadingConfig:uploadingConfig];
    
    [m_ziggeo startImageRecorder];
}

- (IBAction)onShowImage:(id)sender {
    [m_ziggeo showImage:Last_Image_Token];
}

- (IBAction)onCustomUIRecorder:(id)sender {
    RecorderConfig *recorderConfig = [[RecorderConfig alloc] init];
    [recorderConfig setShouldAutoStartRecording:false];
    [recorderConfig setVideoQuality:QUALITY_HIGH];
    [recorderConfig setFacing:FACING_BACK];
    [recorderConfig setMaxDuration:0];
    [recorderConfig setShouldSendImmediately:true];
    [recorderConfig.style setHideControls:true];
    [recorderConfig.resolution setAspectRatio:DEFAULT_ASPECT_RATIO];
    [recorderConfig setExtraArgs:@{@"tags": @"iOS,Video,Custom UI Record",
                                   @"client_auth" : @"CLIENT_AUTH_TOKEN",
                                   @"server_auth" : @"SERVER_AUTH_TOKEN",
                                   @"data" : @{@"foo": @"bar"},
                                   @"effect_profile" : @"1234,5678"}];
    [m_ziggeo setRecorderConfig:recorderConfig];    
    
    ZiggeoRecorder *m_recorder = [[ZiggeoRecorder alloc] initWithZiggeoApplication:m_ziggeo];
    
    CustomUIRecroderViewController *customUIRecroderVC = [[CustomUIRecroderViewController alloc] initWithNibName:@"CustomUIRecroderView" bundle:nil];
    customUIRecroderVC.m_recorder = m_recorder;
    customUIRecroderVC.view.frame = CGRectMake(0, 0, m_recorder.view.bounds.size.width, m_recorder.view.bounds.size.height);
    [m_recorder.view addSubview:customUIRecroderVC.view];
    [self addChildViewController:customUIRecroderVC];

    m_recorder.modalPresentationStyle = UIModalPresentationFullScreen;
    [self presentViewController:m_recorder animated:true completion:nil];
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

- (void)errorWithInfo:(RecordingInfo *)info error:(NSError *)error lostConnectionAction:(int)lostConnectionAction {
    NSLog(@"Error To Upload : %@ : %@ : %d", info, error, lostConnectionAction);
}

- (void)uploadStartedWithPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken backgroundTask:(NSURLSessionTask*)uploadingTask {
    NSLog(@"Upload Started : %@ - %@", token, streamToken);
}

- (void)uploadProgressWithPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken totalBytesSent:(int)bytesSent totalBytesExpectedToSend:(int)totalBytes {
    CGFloat percent = 0;
    if (totalBytes > 0) {
        percent = (CGFloat)bytesSent / (CGFloat)totalBytes * 100;
    }
    NSLog(@"Upload Progress : %@ - %.2f%%", token, percent);
}

- (void)uploadFinishedWithPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken {
    NSLog(@"Upload Finished : %@ - %@", token, streamToken);
}

- (void)uploadVerifiedWithPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken withResponse:(NSURLResponse*)response error:(NSError*)error json:(NSDictionary*)json {
    NSLog(@"Upload Verified : %@", token);
    if (currentType == VIDEO) {
        Last_Video_Token = token;
    } else if (currentType == AUDIO) {
        Last_Audio_Token = token;
    } else if (currentType == IMAGE) {
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
    NSLog(@"seek: %lf", positionMillis);
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
