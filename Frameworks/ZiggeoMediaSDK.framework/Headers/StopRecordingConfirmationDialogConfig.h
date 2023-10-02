//
//  StopRecordingConfirmationDialogConfig.h
//  ZiggeoMediaSDK
//
//  Created by Severyn on 07/24/23.
//  Copyright © 2023 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@interface StopRecordingConfirmationDialogConfig : NSObject

@property (nonatomic, strong) NSString *titleText;
@property (nonatomic, strong) NSString *mesText;
@property (nonatomic, strong) NSString *posBtnText;
@property (nonatomic, strong) NSString *negBtnText;

- (NSString *)getTitleText;
- (void)setTitleText:(NSString *)titleText;
- (NSString *)getMesText;
- (void)setMesText:(NSString *)mesText;
- (NSString *)getPosBtnText;
- (void)setPosBtnText:(NSString *)posBtnText;
- (NSString *)getNegBtnText;
- (void)setNegBtnText:(NSString *)negBtnText;
- (NSString *)stringValueConfig;

@end
