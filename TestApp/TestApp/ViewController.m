//
//  ViewController.m
//  TestApp
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

@import AVKit;
#import <MobileCoreServices/MobileCoreServices.h>

#import "ViewController.h"
#import "Ziggeo/Ziggeo.h"
#import "MusicPlayingController.h"


typedef enum {
    Video,
    Audio,
    Image,
} CurrentType;


@interface ViewController () <ZiggeoRecorderDelegate, ZiggeoUploadDelegate, UINavigationControllerDelegate, UIImagePickerControllerDelegate, ZiggeoHardwarePermissionCheckDelegate, ZiggeoPlayerDelegate> {
    Ziggeo* m_ziggeo;
    ZiggeoPlayer* embeddedPlayer;
    AVPlayerLayer* embeddedPlayerLayer;
    CurrentType currentType;
}

@property (weak, nonatomic) IBOutlet UIImageView *previewImageView;
@property (weak, nonatomic) IBOutlet UIView *previewVideoView;
@property (weak, nonatomic) IBOutlet UILabel *currentStateLabel;

@end


@implementation ViewController

//NSString *ZIGGEO_APP_TOKEN = @"344a71099193b17a693ab11fdd0eeb10";
//NSString *SERVER_AUTH_TOKEN = @"2502a8288403cec13382a6f4d8f54f64";
//NSString *CLIENT_AUTH_TOKEN = @"15901364881299187057";
//
//NSString *Last_Video_Token = @"4eaea7e4d3792a6d1b8dc4f2caeea319";
//NSString *Last_Audio_Token = @"zawimvpc7pbivcfgjjspvxfk34p6icnf";
//NSString *Last_Image_Token = @"xzg4saj6u3ojm47los1kzaztju2cl3on";

NSString *ZIGGEO_APP_TOKEN = @"ZIGGEO_APP_TOKEN";
NSString *SERVER_AUTH_TOKEN = @"SERVER_AUTH_TOKEN";
NSString *CLIENT_AUTH_TOKEN = @"CLIENT_AUTH_TOKEN";

NSString *Last_Video_Token = @"Video_Token";
NSString *Last_Audio_Token = @"Audio_Token";
NSString *Last_Image_Token = @"Image_Token";

- (void)viewDidLoad {
    [super viewDidLoad];
    
    m_ziggeo = [[Ziggeo alloc] initWithToken:ZIGGEO_APP_TOKEN];
    [m_ziggeo checkHardwarePermission:self];
    
    [self.previewImageView setHidden:true];
    [self.previewVideoView setHidden:true];
    [self updateStateLabel:@""];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}


// MARK: Button Click Action

- (IBAction)onVideoRecord:(id)sender {
    currentType = Video;
    [self updateStateLabel:@""];
    
    ZiggeoRecorder* recorder = [[ZiggeoRecorder alloc] initWithZiggeoApplication:m_ziggeo];
    recorder.coverSelectorEnabled = NO;
    recorder.cameraFlipButtonVisible = YES;
    recorder.cameraDevice = UIImagePickerControllerCameraDeviceFront;
    recorder.useLiveStreaming = NO;
    recorder.recordingQuality = LowQuality;
    recorder.audioSampleRate = 44100;
    recorder.maxRecordedDurationSeconds = 0; //infinite
    recorder.autostartRecordingAfterSeconds = 0; //never
    recorder.controlsVisible = true; //false - no controls, autostart enabled, max duration = 30
    recorder.recorderDelegate = self;
    recorder.uploadDelegate = self;
    recorder.videoGravity = AVLayerVideoGravityResizeAspectFill;

    BOOL customizeButtons = NO;
    if (customizeButtons) {
        ZiggeoRecorderInterfaceConfig *config = [[ZiggeoRecorderInterfaceConfig alloc] init];
        config.recordButton.scale = 0.25;
        config.closeButton.scale = 0.5;
        config.cameraFlipButton.scale = 0.5;
        NSURL *flipCameraUrl = [NSBundle.mainBundle URLForResource:@"FlipCamera" withExtension:@"png"];
        if (flipCameraUrl) {
            config.cameraFlipButton.imagePath = flipCameraUrl.path;
        }
        recorder.interfaceConfig = config;
    }

    //recorder.showSoundIndicator = false;
    //recorder.showLightIndicator = false;
    //recorder.showFaceOutline = false;
    //recorder.extraArgsForCreateVideo = @{ @"effect_profile" : @"12345" };
    //recorder.extraArgsForCreateVideo = @{@"data": @"{\"foo\":\"bar\"}"}; //custom user data
// recorder level auth tokens:
//    recorder.extraArgsForCreateVideo = @{ @"client_auth" : @"CLIENT_AUTH_TOKEN" };
//    recorder.extraArgsForCreateVideo = @{ @"server_auth" : @"SERVER_AUTH_TOKEN" };
// global (application level) auth tokens:
//    m_ziggeo.connect.clientAuthToken = @"CLIENT_AUTH_TOKEN";
    m_ziggeo.connect.serverAuthToken = SERVER_AUTH_TOKEN;
    [self presentViewController:recorder animated:true completion:nil];
}

- (IBAction)onChooseVideo:(id)sender {
    currentType = Video;
    [self updateStateLabel:@""];
    
    UIImagePickerController* videoPicker = [[UIImagePickerController alloc] init];
    videoPicker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    videoPicker.delegate = self;
    videoPicker.mediaTypes = [[NSArray alloc] initWithObjects:(NSString *)kUTTypeMovie, nil];
    [self presentViewController:videoPicker animated:true completion:nil];
}

- (IBAction)onVideoPlayFullScreen:(id)sender {
    [self updateStateLabel:@""];
    
    [ZiggeoPlayer createPlayerWithAdditionalParams:m_ziggeo videoToken:Last_Video_Token params:@{ @"client_auth" : CLIENT_AUTH_TOKEN } callback:^(ZiggeoPlayer *player) {
        dispatch_async(dispatch_get_main_queue(), ^{
            player.playerDelegate = self;
            AVPlayerViewController* playerController = [[AVPlayerViewController alloc] init];
            playerController.player = player;
            //hide player on playback finished
            player.didFinishPlaying = ^(NSString *videoToken, NSError *error) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    [playerController dismissViewControllerAnimated:true completion:nil];
                });
            };
            //show playback controls
            playerController.showsPlaybackControls = true;
            [self presentViewController:playerController animated:true completion:nil];
            [playerController.player play];
        });
    }];
}

- (IBAction)onVideoPlayEmbedded:(id)sender {
    [self updateStateLabel:@""];
    
    if (embeddedPlayer) { //remove previous player instance
        [embeddedPlayer pause];
        [embeddedPlayerLayer removeFromSuperlayer];
        embeddedPlayerLayer = nil;
        embeddedPlayer = nil;
    }
    ZiggeoPlayer* player = [[ZiggeoPlayer alloc] initWithZiggeoApplication:m_ziggeo videoToken:Last_Video_Token];
    AVPlayerLayer* playerLayer = [AVPlayerLayer playerLayerWithPlayer:player];
    playerLayer.frame = self.previewVideoView.frame;
    [self.previewVideoView.layer addSublayer:playerLayer];
    [player play];
    embeddedPlayer = player;
    embeddedPlayerLayer = playerLayer;
    
    [self.previewImageView setHidden:true];
    [self.previewVideoView setHidden:false];
}

- (IBAction)onAudioRecord:(id)sender {
    currentType = Audio;
    [self updateStateLabel:@""];
    
    ZiggeoAudioRecorder *audioRecorder = [[ZiggeoAudioRecorder alloc] initWithZiggeoApplication:m_ziggeo];
    audioRecorder.recorderDelegate = self;
    audioRecorder.uploadDelegate = self;
    [self presentViewController:audioRecorder animated:true completion:nil];
}

- (IBAction)onAudioPlay:(id)sender {
    [self updateStateLabel:@""];
    
    MusicPlayingController *audioPlyerVC = [[MusicPlayingController alloc] initWithNibName:@"MusicPlayingController" bundle:nil ziggeo:m_ziggeo audioToken:Last_Audio_Token];
    [self presentViewController:audioPlyerVC animated:true completion:nil];
}

- (IBAction)onTakePhoto:(id)sender {
    currentType = Image;
    [self updateStateLabel:@""];
    
    if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera]) {
        UIImagePickerController* imagePicker = [[UIImagePickerController alloc] init];
        imagePicker.sourceType = UIImagePickerControllerSourceTypeCamera;
        imagePicker.delegate = self;
        imagePicker.allowsEditing = false;
        imagePicker.mediaTypes = [[NSArray alloc] initWithObjects:(NSString *)kUTTypeImage, nil];
        [self presentViewController:imagePicker animated:true completion:nil];
    }
}

- (IBAction)onChooseImage:(id)sender {
    currentType = Image;
    [self updateStateLabel:@""];
    
    UIImagePickerController* imagePicker = [[UIImagePickerController alloc] init];
    imagePicker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    imagePicker.delegate = self;
    imagePicker.allowsEditing = false;
    imagePicker.mediaTypes = [[NSArray alloc] initWithObjects:(NSString *)kUTTypeImage, nil];
    [self presentViewController:imagePicker animated:true completion:nil];
}

- (IBAction)onShowImage:(id)sender {
    [self updateStateLabel:@""];
    [self.previewImageView setHidden:false];
    [self.previewVideoView setHidden:true];
    
    [m_ziggeo.images downloadImageWithToken:Last_Image_Token Callback:^(NSString *filePath) {
        dispatch_async(dispatch_get_global_queue(0,0), ^{
            NSData *data = [[NSData alloc] initWithContentsOfURL:[NSURL fileURLWithPath:filePath]];
            if (data == nil)
                return;
            
            dispatch_async(dispatch_get_main_queue(), ^{
                self.previewImageView.image = [UIImage imageWithData: data];
            });
        });
    }];
}

- (void)updateStateLabel:(NSString *)state {
    dispatch_async(dispatch_get_main_queue(), ^{
        self.currentStateLabel.text = state;
    });
}


// MARK: - UINavigationControllerDelegate, UIImagePickerControllerDelegate

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<UIImagePickerControllerInfoKey,id> *)info {
    NSString *mediaType = info[UIImagePickerControllerMediaType];
    if (CFStringCompare ((__bridge_retained CFStringRef) mediaType, kUTTypeImage, 0) == kCFCompareEqualTo) {
        UIImage *imageFile = info[UIImagePickerControllerOriginalImage];
        self->m_ziggeo.images.uploadDelegate = self;
        [self->m_ziggeo.images uploadImageWithFile:imageFile];
        [self dismissViewControllerAnimated:YES completion:nil];
        
    } else if (CFStringCompare ((__bridge_retained CFStringRef) mediaType, kUTTypeMovie, 0) == kCFCompareEqualTo) {
        NSString *path = [info[UIImagePickerControllerMediaURL] path];

        NSString *documentsDirectory = NSTemporaryDirectory();
        NSString *newFilePath = [documentsDirectory stringByAppendingPathComponent:@"video.mp4"];
        NSError *error = nil;
        if ([[NSFileManager defaultManager] fileExistsAtPath:newFilePath]) {
            [[NSFileManager defaultManager] removeItemAtPath:newFilePath error:&error];
        }
        
        BOOL success = [[NSFileManager defaultManager] copyItemAtPath:path toPath:newFilePath error:&error];
        if (success) {
            path = newFilePath;
        }
        self->m_ziggeo.videos.uploadDelegate = self;
        NSDictionary *dic = [NSDictionary dictionaryWithObject:@"TEST_TAG" forKey:@"tags"];
        [self->m_ziggeo.videos uploadVideoWithPath:path Data: dic];
        [self dismissViewControllerAnimated:YES completion:nil];
    }
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker {
    if (currentType == Video) {
        NSLog(@"Video Picker canceled.");
    } else if (currentType == Image) {
        NSLog(@"Image Picker canceled.");
    }
    [self dismissViewControllerAnimated:YES completion:nil];
}


// MARK: - ZiggeoRecorderDelegate

- (void)luxMeter:(double)luminousity {
    //NSLog(@"luminousity: %f", luminousity);
}

- (void)audioMeter:(double)audioLevel {
    //NSLog(@"audio: %f", audioLevel);
}

- (void)faceDetected:(int)faceID rect:(CGRect)rect {
    //NSLog(@"face %i detected with bounds: x = %f y = %f, size = %f x %f", faceID, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}

- (void)ziggeoRecorderReady {
    NSLog(@"Ziggeo Recorder Ready");
}

- (void) ziggeoRecorderCanceled {
    NSLog(@"Ziggeo Recorder Canceled");
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


// MARK: - ZiggeoUploadDelegate

- (void)preparingToUploadWithPath:(NSString*)sourcePath {
    NSLog(@"Preparing To Upload : %@", sourcePath);
    if (currentType == Video) {
        [self updateStateLabel:@"Video Upload Started"];
    } else if (currentType == Audio) {
        [self updateStateLabel:@"Audio Upload Started"];
    } else if (currentType == Image) {
        [self updateStateLabel:@"Image Upload Started"];
    }
}

- (void)failedToUploadWithPath:(NSString*)sourcePath {
    NSLog(@"Failed To Upload : %@", sourcePath);
    [self updateStateLabel:@"Upload Failed"];
}

- (void)uploadStartedWithPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken backgroundTask:(NSURLSessionTask*)uploadingTask {
    NSLog(@"Upload Started : %@ - %@", token, streamToken);
}

- (void)uploadProgressForPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken totalBytesSent:(int)bytesSent totalBytesExpectedToSend:(int)totalBytes {
    NSLog(@"Upload Progress : %@ - %i - %i", token, bytesSent, totalBytes);
    if (currentType == Video) {
        [self updateStateLabel:[NSString stringWithFormat:@"Video Uploading : %d / %d", bytesSent, totalBytes]];
    } else if (currentType == Audio) {
        [self updateStateLabel:[NSString stringWithFormat:@"Audio Uploading : %d / %d", bytesSent, totalBytes]];
    } else if (currentType == Image) {
        [self updateStateLabel:[NSString stringWithFormat:@"Image Uploading : %d / %d", bytesSent, totalBytes]];
    }
}

- (void)uploadFinishedForPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken {
    NSLog(@"Upload Finished : %@ - %@", token, streamToken);
}

- (void)uploadVerifiedWithPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken withResponse:(NSURLResponse*)response error:(NSError*)error json:(NSDictionary*)json {
    NSLog(@"Upload Verified : %@", token);
    if (currentType == Video) {
        Last_Video_Token = token;
        [self updateStateLabel:@"Video Upload Completed"];
    } else if (currentType == Audio) {
        Last_Audio_Token = token;
        [self updateStateLabel:@"Audio Upload Completed"];
    } else if (currentType == Image) {
        Last_Image_Token = token;
        [self updateStateLabel:@"Image Upload Completed"];
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



@end
