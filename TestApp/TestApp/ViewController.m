//
//  ViewController.m
//  TestApp
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import "ViewController.h"
#import "Ziggeo/Ziggeo.h"
@import AVKit;

@interface ViewController () {
    Ziggeo* m_ziggeo;
    ZiggeoPlayer* embeddedPlayer;
    AVPlayerLayer* embeddedPlayerLayer;
}
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    m_ziggeo = [[Ziggeo alloc] initWithToken:@"ZIGGEO_APP_TOKEN"];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (IBAction)playFullScreen:(id)sender {
    //ZiggeoPlayer.cr
    [ZiggeoPlayer createPlayerWithAdditionalParams:m_ziggeo videoToken:@"VIDEO_TOKEN" params:@{ @"client_auth" : @"CLIENT_AUTH_TOKEN" } callback:^(ZiggeoPlayer *player) {
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

- (IBAction)playEmbedded:(id)sender {
    if(embeddedPlayer) //remove previous player instance
    {
        [embeddedPlayer pause];
        [embeddedPlayerLayer removeFromSuperlayer];
        embeddedPlayerLayer = nil;
        embeddedPlayer = nil;
    }
    ZiggeoPlayer* player = [[ZiggeoPlayer alloc] initWithZiggeoApplication:m_ziggeo videoToken:@"VIDEO_TOKEN"];
    AVPlayerLayer* playerLayer = [AVPlayerLayer playerLayerWithPlayer:player];
    playerLayer.frame = self.videoViewPlaceholder.frame;
    [self.videoViewPlaceholder.layer addSublayer:playerLayer];
    [player play];
    embeddedPlayer = player;
    embeddedPlayerLayer = playerLayer;
}

- (IBAction)record:(id)sender {
    ZiggeoRecorder2* recorder = [[ZiggeoRecorder2 alloc] initWithZiggeoApplication:m_ziggeo];
    recorder.coverSelectorEnabled = NO;
    recorder.cameraFlipButtonVisible = YES;
    recorder.cameraDevice = UIImagePickerControllerCameraDeviceFront;
    recorder.useLiveStreaming = NO;
    recorder.maxRecordedDurationSeconds = 0; //infinite
    recorder.autostartRecordingAfterSeconds = 0; //never
    recorder.controlsVisible = false; //no controls, autostart enabled, max duration = 30
//    recorder.extraArgsForCreateVideo = @{ @"effect_profile" : @"12345" };
// recorder level auth tokens:
//    recorder.extraArgsForCreateVideo = @{ @"client_auth" : @"CLIENT_AUTH_TOKEN" };
//    recorder.extraArgsForCreateVideo = @{ @"server_auth" : @"SERVER_AUTH_TOKEN" };
// global (application level) auth tokens:
//    m_ziggeo.connect.clientAuthToken = @"CLIENT_AUTH_TOKEN";
//    m_ziggeo.connect.serverAuthToken = @"SERVER_AUTH_TOKEN";
    [self presentViewController:recorder animated:true completion:nil];
}

@end
