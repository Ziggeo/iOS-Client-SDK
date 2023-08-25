//
//  CustomUIRecroderViewController.h
//  TestApp
//
//  Copyright © 2016 Ziggeo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ZiggeoMediaSDK/ZiggeoMediaSDK.h"


@interface CustomUIRecroderViewController : UIViewController

@property (nonatomic, weak) IBOutlet UIBarButtonItem *recordButton;
@property (nonatomic, weak) IBOutlet UIBarButtonItem *stopAndUploadButton;

@property (nonatomic, weak) ZiggeoRecorder* m_recorder;

@end

