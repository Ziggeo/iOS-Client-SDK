//
//  ViewController.m
//  CustomUITestApp
//
//  Copyright © 2016 Ziggeo. All rights reserved.
//

#import "ViewController.h"
#import "Ziggeo/Ziggeo.h"
@import AVKit;


@interface ViewController () {
    Ziggeo* m_ziggeo;
    ZiggeoRecorder* m_recorder;
}

@property (nonatomic) IBOutlet UIView *overlayView;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *recordButton;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *stopAndUploadButton;


@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    m_ziggeo = [[Ziggeo alloc] initWithToken:@"APPLICATION_TOKEN"];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)onRecordButtonPressed:(id)sender {
    m_recorder = [[ZiggeoRecorder alloc] initWithZiggeoApplication:m_ziggeo];
    [[NSBundle mainBundle] loadNibNamed:@"OverlayView" owner:self options:nil];
    self.overlayView.frame = m_recorder.cameraOverlayView.frame;
    m_recorder.cameraOverlayView = self.overlayView;
    m_recorder.showsCameraControls = NO;
    self.overlayView = nil;
    [self presentViewController:m_recorder animated:true completion:nil];
    self.stopAndUploadButton.enabled = NO;
}

- (IBAction)closeButtonPressed:(id)sender {
    if(m_recorder) [m_recorder dismissViewControllerAnimated:YES completion:nil];
    m_recorder = nil;
    
}

- (IBAction)recordButtonPressed:(id)sender {
    if(m_recorder) [m_recorder startVideoCapture];
    self.stopAndUploadButton.enabled = YES;
    self.recordButton.enabled = NO;
}

- (IBAction)stopButtonPressed:(id)sender {
    if(m_recorder) [m_recorder stopVideoCapture];
}

@end
