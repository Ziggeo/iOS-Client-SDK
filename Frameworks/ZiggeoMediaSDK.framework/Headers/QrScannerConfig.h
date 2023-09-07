//
//  QrScannerConfig.h
//  ZiggeoMediaSDK
//
//  Created by Severyn on 07/24/23.
//  Copyright © 2023 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@interface QrScannerConfig : NSObject

@property (nonatomic) bool shouldCloseAfterSuccessfulScan;

- (bool)getShouldCloseAfterSuccessfulScan;
- (void)setShouldCloseAfterSuccessfulScan:(bool)shouldCloseAfterSuccessfulScan;
- (NSString *)stringValueConfig;

@end
