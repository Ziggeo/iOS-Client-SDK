//
//  QrScannerConfig.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@interface QrScannerConfig : NSObject

@property (nonatomic) bool shouldCloseAfterSuccessfulScan;

- (bool)getShouldCloseAfterSuccessfulScan;
- (void)setShouldCloseAfterSuccessfulScan:(bool)shouldCloseAfterSuccessfulScan;
- (NSString *)stringValueConfig;

@end
