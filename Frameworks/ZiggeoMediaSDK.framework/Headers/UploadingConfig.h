//
//  UploadingConfig.h
//  ZiggeoMediaSDK
//
//  Created by Severyn on 07/24/23.
//  Copyright © 2023 Ziggeo Inc. All rights reserved.
//

@import Foundation;
@import UIKit;


@interface UploadingConfig : NSObject

@property (nonatomic) long syncInterval;
// turn off uploading feature at all
@property (nonatomic) bool shouldTurnOffUploader;
@property (nonatomic) bool shouldUseWifiOnly;
// upload without starting a background service (will start only when the app goes foreground)
@property (nonatomic) bool shouldStartAsForeground;
@property (nonatomic) bool shouldDeleteFailedFile;
@property (nonatomic) int lostConnectionAction;
@property (nonatomic, strong) NSDictionary *extraArgs;

- (long)getSyncInterval;
- (void)setSyncInterval:(long)syncInterval;
- (bool)getShouldTurnOffUploader;
- (void)setShouldTurnOffUploader:(bool)shouldTurnOffUploader;
- (bool)getShouldUseWifiOnly;
- (void)setShouldUseWifiOnly:(bool)shouldUseWifiOnly;
- (bool)getShouldStartAsForeground;
- (void)setShouldStartAsForeground:(bool)shouldStartAsForeground;
- (bool)getShouldDeleteFailedFile;
- (void)setShouldDeleteFailedFile:(bool)shouldDeleteFailedFile;
- (int)getLostConnectionAction;
- (void)setLostConnectionAction:(int)lostConnectionAction;
- (NSMutableDictionary *)getExtraArgs;
- (void)setExtraArgs:(NSDictionary *)extraArgs;
- (void)addExtraArgs:(NSDictionary *)extraArgs;
- (NSString *)stringValueConfig;

@end
