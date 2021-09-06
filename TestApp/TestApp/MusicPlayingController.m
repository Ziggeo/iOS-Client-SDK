//
//  MusicPlayingController.m
//  TestApp
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import "MusicPlayingController.h"

@interface MusicPlayingController () <AVAudioPlayerDelegate> {
    AVAudioPlayer *audioPlayer;
    Ziggeo *m_ziggeo;
    NSString *m_audioToken;
    NSString *m_audioPath;
    NSTimer *m_timer;
    BOOL m_prepared;
}

@property (weak, nonatomic) IBOutlet UILabel *statusLabel;
@property (weak, nonatomic) IBOutlet UILabel *currentTimeLabel;
@property (weak, nonatomic) IBOutlet UIButton *playOrPauseButton;
@property (weak, nonatomic) IBOutlet UISlider *timeSlider;

@end

@implementation MusicPlayingController

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil ziggeo:(Ziggeo *)ziggeo audioToken:(NSString *)audioToken
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.view.backgroundColor = [UIColor whiteColor];
        m_ziggeo = ziggeo;
        m_audioToken = audioToken;
        m_prepared = false;
        
        self.statusLabel.text = @"Loading";
        [self.playOrPauseButton setTitle:@"" forState:UIControlStateNormal];
        self.timeSlider.value = 0;
        
        [m_ziggeo.audios downloadAudioWithToken:m_audioToken Callback:^(NSString *filePath) {
            dispatch_async(dispatch_get_main_queue(), ^{
                m_audioPath = filePath;
                
                NSURL *fileUrl = [NSURL URLWithString:filePath];
                audioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:fileUrl error:nil];
                audioPlayer.delegate = self;
                
                m_prepared = YES;
                
                self.statusLabel.text = @"";
                [self.playOrPauseButton setTitle:@"Play" forState:UIControlStateNormal];
                self.timeSlider.minimumValue = 0;
                if (audioPlayer != nil) {
                    self.timeSlider.maximumValue = audioPlayer.duration;
                }
                self.timeSlider.value = 0;
            });
        }];
    }
    return self;
}

- (void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
    
    if (audioPlayer != nil && audioPlayer.isPlaying) {
        [audioPlayer stop];
    }
    [self.playOrPauseButton setTitle:@"Play" forState:UIControlStateNormal];
}

- (IBAction)onChangeCurrentTime:(UISlider *)sender {
    if (audioPlayer != nil) {
        audioPlayer.currentTime = sender.value;
    }
}

- (IBAction)onPlayOrPause:(UIButton *)sender {
    if (audioPlayer == nil) {
        return;
    }
    
    [self stopTimer];
    
    if (audioPlayer.isPlaying) {
        [audioPlayer pause];
        self.statusLabel.text = @"Paused";
        [self.playOrPauseButton setTitle:@"Play" forState:UIControlStateNormal];
    } else {
        m_timer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(playingAction:) userInfo:nil repeats:YES];
        
        [audioPlayer play];
        self.statusLabel.text = @"Playing";
        [self.playOrPauseButton setTitle:@"Pause" forState:UIControlStateNormal];
    }
}

- (IBAction)onClose:(id)sender {
    [self stopTimer];
    if (audioPlayer != nil && audioPlayer.isPlaying) {
        [audioPlayer stop];
    }
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)stopTimer {
    if (m_timer != nil) {
        [m_timer invalidate];
        m_timer = nil;
    }
}

- (void)playingAction:(id)sender {
    float progress = audioPlayer.currentTime;
    int hours = (int)progress / 3600;
    int minutes = ((int)progress % 3600) / 60;
    int seconds = (int)progress % 60;
    self.currentTimeLabel.text = [NSString stringWithFormat:@"%02d:%02d:%02d", hours, minutes, seconds];
    self.timeSlider.value = progress;
}


//MARK: - AVAudioPlayerDelegate
- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag {
    if (flag == true) {
        self.statusLabel.text = @"";
        [self.playOrPauseButton setTitle:@"Play" forState:UIControlStateNormal];
        self.currentTimeLabel.text = @"00:00:00";
        self.timeSlider.value = 0;
        
        [self stopTimer];
    }
}

@end
