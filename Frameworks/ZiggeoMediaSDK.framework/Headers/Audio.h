//
//  Audio.h
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

@interface Audio : ContentModel

@property (strong, nonatomic) NSString *_id;
@property (strong, nonatomic) NSString *created;
@property (strong, nonatomic) NSString *updated;
@property (strong, nonatomic) NSString *applicationId;
@property (nonatomic) int state;
@property (nonatomic) double minDuration;
@property (strong, nonatomic) NSString *maxDuration;
@property (nonatomic) bool enforceDuration;
@property (strong, nonatomic) NSString *originalStreamId;
@property (strong, nonatomic) NSString *defaultStreamId;
@property (strong, nonatomic) NSArray *tags;
@property (strong, nonatomic) NSString *data;
@property (strong, nonatomic) DeviceInfo *deviceInfo;
@property (nonatomic) long submissionDate;
@property (strong, nonatomic) NSString *expirationDays;
@property (strong, nonatomic) NSString *resubmissionDate;
@property (nonatomic) long streamSubmissionDate;
@property (nonatomic) bool userLanguage;
@property (nonatomic) bool deleteOldStreams;
@property (nonatomic) bool autoCrop;
@property (strong, nonatomic) NSString *creationAuthSessionId;
@property (nonatomic) int averageRating;
@property (strong, nonatomic) NSString *ratings;
@property (strong, nonatomic) NSArray *comments;
@property (nonatomic) bool submitted;
@property (strong, nonatomic) NSString *approved;
@property (strong, nonatomic) NSString *moderationReason;
@property (strong, nonatomic) NSString *audioProfileId;
@property (strong, nonatomic) NSString *metaProfileId;
@property (nonatomic) bool _volatile;
@property (strong, nonatomic) NSDictionary *defaultStream;
@property (strong, nonatomic) StreamModel *originalStream;

- (id)init;
- (id)initWithJson:(NSDictionary *)json;
- (void)setInfo:(NSDictionary *)json;
- (void)clear;
- (NSDictionary *)toDictionary;

- (NSString *)getId;
- (void)setId:(NSString *)_id;

@end
