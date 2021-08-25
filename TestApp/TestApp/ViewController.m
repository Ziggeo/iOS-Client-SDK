//
//  ViewController.m
//  TestApp
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import "ViewController.h"
#import "Ziggeo/Ziggeo.h"
#import "MusicPlayingController.h"
@import AVKit;


typedef enum {
    Video,
    Audio,
    Image,
} CurrentType;


@interface ViewController () <ZiggeoRecorderDelegate, ZiggeoAudioRecorderDelegate, ZiggeoApiDelegate, ZiggeoImagePickerDelegate> {
    Ziggeo* m_ziggeo;
    ZiggeoPlayer* embeddedPlayer;
    AVPlayerLayer* embeddedPlayerLayer;
    CurrentType currentType;
}

@property (weak, nonatomic) IBOutlet UIImageView *previewImageView;
@property (weak, nonatomic) IBOutlet UIView *previewVideoView;

@end


@implementation ViewController

NSString *ZIGGEO_APP_TOKEN = @"344a71099193b17a693ab11fdd0eeb10";
NSString *ZIGGEO_SERVER_AUTH_TOKEN = @"2502a8288403cec13382a6f4d8f54f64";
NSString *CLIENT_AUTH_TOKEN = @"15901364881299187057";

NSString *Last_Video_Token = @"4eaea7e4d3792a6d1b8dc4f2caeea319";
NSString *Last_Audio_Token = @"zawimvpc7pbivcfgjjspvxfk34p6icnf";
NSString *Last_Image_Token = @"xzg4saj6u3ojm47los1kzaztju2cl3on";

- (void)viewDidLoad {
    [super viewDidLoad];
    
    m_ziggeo = [[Ziggeo alloc] initWithToken:ZIGGEO_APP_TOKEN];
    
    [self.previewImageView setHidden:true];
    [self.previewVideoView setHidden:true];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}


//MARK: Button Click Action

- (IBAction)onVideoRecord:(id)sender {
    currentType = Video;
    
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
    m_ziggeo.connect.serverAuthToken = ZIGGEO_SERVER_AUTH_TOKEN;
    [self presentViewController:recorder animated:true completion:nil];
}

- (IBAction)onVideoPlayFullScreen:(id)sender {
    [ZiggeoPlayer createPlayerWithAdditionalParams:m_ziggeo videoToken:Last_Video_Token params:@{ @"client_auth" : CLIENT_AUTH_TOKEN } callback:^(ZiggeoPlayer *player) {
        dispatch_async(dispatch_get_main_queue(), ^
        {
            AVPlayerViewController* playerController = [[AVPlayerViewController alloc] init];
            playerController.player = player;
            //hide player on playback finished
            player.didFinishPlaying = ^(NSString *videoToken, NSError *error) {
                dispatch_async(dispatch_get_main_queue(), ^
                {
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
    if (embeddedPlayer) //remove previous player instance
    {
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
    
    ZiggeoAudioRecorder *audioRecorder = [[ZiggeoAudioRecorder alloc] initWithZiggeoApplication:m_ziggeo];
    audioRecorder.recorderDelegate = self;
    audioRecorder.apiDelegate = self;
    [self presentViewController:audioRecorder animated:true completion:nil];
}

- (IBAction)onAudioPlay:(id)sender {
    MusicPlayingController *audioPlyerVC = [[MusicPlayingController alloc] initWithNibName:@"MusicPlayingController" bundle:nil ziggeo:m_ziggeo audioToken:Last_Audio_Token];
    [self presentViewController:audioPlyerVC animated:true completion:nil];
}

- (IBAction)onTakePhoto:(id)sender {
    currentType = Image;
}

- (IBAction)onChooseImage:(id)sender {
    currentType = Image;
    
    ZiggeoChooseImage *imagePicker = [[ZiggeoChooseImage alloc] initWithZiggeoApplication:m_ziggeo];
    imagePicker.imagePickerDelegate = self;
    imagePicker.apiDelegate = self;
    [self presentViewController:imagePicker animated:true completion:nil];
}

- (IBAction)onShowImage:(id)sender {
    dispatch_async(dispatch_get_global_queue(0,0), ^{
        NSString *imagePath = [m_ziggeo.apiHelper getURLForImageToken:Last_Image_Token];
        NSData *data = [[NSData alloc] initWithContentsOfURL: [NSURL URLWithString:imagePath]];
        if (data == nil)
            return;
        
        dispatch_async(dispatch_get_main_queue(), ^{
            self.previewImageView.image = [UIImage imageWithData: data];
        });
    });
    
    [self.previewImageView setHidden:false];
    [self.previewVideoView setHidden:true];
}


//MARK: - ZiggeoRecorderDelegate

-(void) luxMeter:(double)luminousity {
    //NSLog(@"luminousity: %f", luminousity);
}

-(void) audioMeter:(double)audioLevel {
    //NSLog(@"audio: %f", audioLevel);
}

-(void) faceDetected:(int)faceID rect:(CGRect)rect {
    //NSLog(@"face %i detected with bounds: x = %f y = %f, size = %f x %f", faceID, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
}


//MARK: - ZiggeoAudioRecorderDelegate

- (void)ziggeoAudioRecorderReady {
//    NSLog(@"ziggeoAudioRecorderReady");
}

- (void) ziggeoAudioRecorderCanceled {
//    NSLog(@"ziggeoAudioRecorderCanceled");
}

- (void)ziggeoAudioRecorderRecoding {
//    NSLog(@"ziggeoAudioRecorderRecoding");
}

- (void)ziggeoAudioRecorderCurrentRecordedDurationSeconds:(double)seconds {
//    NSLog(@"ziggeoAudioRecorderCurrentRecordedDurationSeconds: %f", seconds);
}

- (void)ziggeoAudioRecorderFinished:(double)seconds {
//    NSLog(@"ziggeoAudioRecorderFinished: %f", seconds);
}

- (void)ziggeoAudioRecorderPlaying {
//    NSLog(@"ziggeoAudioRecorderPlaying");
}

- (void)ziggeoAudioRecorderPaused {
//    NSLog(@"ziggeoAudioRecorderPaused");
}


//MARK: - ZiggeoApiDelegate

- (void)preparingToUploadWithPath:(NSString*)sourcePath {
//    NSLog(@"preparingToUploadWithPath : %@", sourcePath);
    dispatch_async( dispatch_get_main_queue(), ^{
        [self dismissViewControllerAnimated:YES completion:NULL];
    });
}

- (void)preparingToUploadWithPath:(NSString*)sourcePath token:(NSString*)token {
//    NSLog(@"preparingToUploadWithPath : %@ - %@", sourcePath, token);
}

- (void)uploadStartedWithPath:(NSString*)sourcePath token:(NSString*)token backgroundTask:(NSURLSessionTask*)uploadingTask {
//    NSLog(@"uploadStartedWithPath : %@ - %@", sourcePath, token);
}

- (void)uploadProgressForPath:(NSString*)sourcePath token:(NSString*)token totalBytesSent:(int)bytesSent totalBytesExpectedToSend:(int)totalBytes {
//    NSLog(@"uploadProgressForPath : %@ - %i - %i", token, bytesSent, totalBytes);
}

- (void)uploadCompletedForPath:(NSString*)sourcePath token:(NSString*)token withResponse:(NSURLResponse*)response error:(NSError*)error json:(NSDictionary*)json {
    NSLog(@"Ziggeo File Upload Completed : %@", token);
    if (currentType == Video) {
        Last_Video_Token = token;
    } else if (currentType == Audio) {
        Last_Audio_Token = token;
    } else if (currentType == Image) {
        Last_Image_Token = token;
        [self onShowImage:self];
    }
}


//MARK: - ZiggeoImagePickerDelegate
- (void)ziggeoImagePickerDidCancel {
    NSLog(@"ziggeoImagePickerDidCancel");
}

- (void)ziggeoImagePickerDidSelected:(NSString *)imageFilePath {
    NSLog(@"ziggeoImagePickerDidSelected : %@", imageFilePath);
}

- (void)ziggeoImagePickerDidFailed {
    NSLog(@"ziggeoImagePickerDidFailed");
}

@end
