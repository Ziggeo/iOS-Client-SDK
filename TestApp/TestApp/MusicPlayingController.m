//
//  MusicPlayingController.m
//  TestApp
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import "MusicPlayingController.h"

@interface MusicPlayingController () <ZiggeoAudioPlayerDelegate> {
    ZiggeoAudioPlayer *audioPlayer;
    Ziggeo *m_ziggeo;
    NSString *m_audioToken;
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
        audioPlayer = [[ZiggeoAudioPlayer alloc] initWithZiggeoApplication:m_ziggeo audioToken:m_audioToken];
        audioPlayer.delegate = self;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.statusLabel.text = @"Loading";
    [self.playOrPauseButton setTitle:@"" forState:UIControlStateNormal];
    self.timeSlider.value = 0;
}

- (void)viewWillDisappear:(BOOL)animated{
    [super viewWillDisappear:animated];
    
    [audioPlayer pause];
    [self.playOrPauseButton setTitle:@"Play" forState:UIControlStateNormal];
}

- (IBAction)onChangeCurrentTime:(UISlider *)sender
{
    [audioPlayer seekToTime:sender.value];
}

- (IBAction)onPlayOrPause:(UIButton *)sender
{
    if (audioPlayer.isPlaying) {
        [audioPlayer pause];
        self.statusLabel.text = @"Paused";
        [self.playOrPauseButton setTitle:@"Play" forState:UIControlStateNormal];
    } else {
        [audioPlayer play];
        self.statusLabel.text = @"Playing";
        [self.playOrPauseButton setTitle:@"Pause" forState:UIControlStateNormal];
    }
}

- (IBAction)onClose:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

//MARK: - ZiggeoAudioPlayerDelegate
- (void)audioPlayerDidLoadedItem:(ZiggeoAudioPlayer *)audioPlayer
{
    self.statusLabel.text = @"";
    [self.playOrPauseButton setTitle:@"Play" forState:UIControlStateNormal];
    self.timeSlider.minimumValue = 0;
    self.timeSlider.maximumValue = [audioPlayer duration];
    self.timeSlider.value = 0;
    NSLog(@"Duration : %f", [audioPlayer duration]);
}

- (void)audioPlayerDidFinishItem:(ZiggeoAudioPlayer *)audioPlayer
{
    self.statusLabel.text = @"";
    [self.playOrPauseButton setTitle:@"Play" forState:UIControlStateNormal];
}

-(void)audioPlayerPlayWith:(ZiggeoAudioPlayer *)audioPlayer Progress:(float)progress
{
    NSLog(@"%f", progress);

    int hours = (int)progress / 3600;
    int minutes = ((int)progress % 3600) / 60;
    int seconds = (int)progress % 60;
    self.currentTimeLabel.text = [NSString stringWithFormat:@"%02d:%02d:%02d", hours, minutes, seconds];
    self.timeSlider.value = progress;
}

@end
