//
//  DeviceInfo.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@interface DeviceInfo : NSObject

@property (strong, nonatomic) NSString *os;               // iOS
@property (strong, nonatomic) NSString *ziggeoSdkVer;     // 1.1.46
@property (strong, nonatomic) NSString *deviceModel;      // iPhone
@property (strong, nonatomic) NSString *systemVersion;    // 4.0
@property (strong, nonatomic) NSString *deviceName;       // My iPhone

- (id)init;
- (id)initWithJson:(NSDictionary *)json;
- (void)setInfo:(NSDictionary *)json;
- (void)clear;
- (NSString *)toString;
- (NSDictionary *)toDictionary;

@end
