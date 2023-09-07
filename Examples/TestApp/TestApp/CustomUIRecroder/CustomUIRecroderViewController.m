//
//  CustomUIRecroderViewController.m
//  TestApp
//
//  Copyright © 2016 Ziggeo. All rights reserved.
//

#import "CustomUIRecroderViewController.h"


@implementation CustomUIRecroderViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.stopAndUploadButton.enabled = NO;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)closeButtonPressed:(id)sender {
    if (self.m_recorder) [self.m_recorder dismissViewControllerAnimated:YES completion:nil];
    self.m_recorder = nil;
}

- (IBAction)recordButtonPressed:(id)sender {
    if (self.m_recorder) [self.m_recorder startRecordingToFile:NULL];
    self.stopAndUploadButton.enabled = YES;
    self.recordButton.enabled = NO;
}

- (IBAction)stopButtonPressed:(id)sender {
    if(self.m_recorder) [self.m_recorder stopRecording];
    self.stopAndUploadButton.enabled = NO;
    self.recordButton.enabled = YES;
}

@end
