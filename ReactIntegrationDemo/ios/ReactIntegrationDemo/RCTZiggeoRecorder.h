//
//  ZiggeoRecorderRCT.h
//  ReactTest2
//
//  Created by alex on 29/06/2017.
//  Copyright © 2017 Facebook. All rights reserved.
//

#ifndef ZiggeoRecorderRCT_h
#define ZiggeoRecorderRCT_h

#import <React/RCTBridgeModule.h>
#import <React/RCTEventEmitter.h>
#import <Ziggeo/Ziggeo.h>

@interface RCTZiggeoRecorder : RCTEventEmitter <RCTBridgeModule, ZiggeoRecorder2Delegate, ZiggeoVideosDelegate>
- (void)present;

@property (strong, nonatomic) NSString *appToken;
@property (nonatomic) BOOL cameraFlipButtonVisible;
@property (nonatomic) BOOL coverSelectorEnabled;
@property (nonatomic) NSInteger camera;


@end


#endif /* ZiggeoRecorderRCT_h */
