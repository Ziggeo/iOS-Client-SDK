//
//  ZiggeoRecordedVideoPreview.h
//  Ziggeo
//
//  Created by alex on 08/04/16.
//  Copyright © 2016 Ziggeo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVKit/AVKit.h>

@protocol VideoPreviewDelegate

- (void)retake;
- (void)uploadVideo:(NSString *)filePath;

@end


@protocol VideoPreviewProtocol

@property (nonatomic) NSURL* videoURL;
@property (nonatomic) AVLayerVideoGravity videoGravity;
@property (nonatomic) id<VideoPreviewDelegate> previewDelegate;

@end


@interface ZiggeoRecordedVideoPreview : UIViewController <VideoPreviewProtocol>

@property (weak, nonatomic) IBOutlet UIButton *playPauseButton;
@property (weak, nonatomic) IBOutlet UIView *videoPlaceholder;
@property (nonatomic) NSURL* videoURL;
@property (nonatomic) AVLayerVideoGravity videoGravity;
@property (nonatomic) id<VideoPreviewDelegate> previewDelegate;

@end
