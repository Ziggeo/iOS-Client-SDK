//
//  Video.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "ContentModel.h"
#import "DeviceInfo.h"
#import "StreamModel.h"

@interface Video : ContentModel

@property (nonatomic) bool _volatile;
@property (nonatomic) int state;
@property (nonatomic) bool onlyAudio;
@property (nonatomic) double maxDuration;
@property (nonatomic) bool enforceDuration;
@property (strong, nonatomic) NSString *videoSource;
@property (strong, nonatomic) NSArray *tags;
@property (strong, nonatomic) NSObject *data;
@property (strong, nonatomic) DeviceInfo *deviceInfo;
@property (nonatomic) long submissionDate;
@property (strong, nonatomic) NSObject *expirationDays;
@property (nonatomic) int resubmissionDate;
@property (nonatomic) int streamSubmissionDate;
@property (nonatomic) bool userLanguage;
@property (nonatomic) bool deleteOldStreams;
@property (nonatomic) bool autoCrop;
@property (nonatomic) bool autoPad;
@property (nonatomic) bool hd;
@property (strong, nonatomic) NSObject *averageRating;
@property (nonatomic) bool submitted;
@property (nonatomic) bool approved;
@property (strong, nonatomic) NSString *moderationReason;
@property (strong, nonatomic) NSObject *effectProfile;
@property (nonatomic) double defaultImageSelector;
@property (strong, nonatomic) NSString *videoFileName;
@property (strong, nonatomic) NSString *type;
@property (nonatomic) int created;
@property (nonatomic) bool owned;
@property (strong, nonatomic) NSString *videoProfile;
@property (strong, nonatomic) NSString *metaProfile;
@property (strong, nonatomic) NSString *metaProfileId;
@property (strong, nonatomic) NSArray *streams;
@property (strong, nonatomic) StreamModel *originalStream;
@property (strong, nonatomic) StreamModel *defaultStream;
@property (strong, nonatomic) NSString *embedImageUrl;
@property (strong, nonatomic) NSString *embedVideoUrl;

- (id)init;
- (id)initWithJson:(NSDictionary *)json;
- (void)setInfo:(NSDictionary *)json;
- (void)clear;
- (NSDictionary *)toDictionary;
- (NSString *)toString;

- (bool)isVolatile;
- (void)setVolatile:(bool)_volatile;

@end

