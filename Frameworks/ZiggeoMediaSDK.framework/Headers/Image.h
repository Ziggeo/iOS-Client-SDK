//
//  Image.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "ContentModel.h"
#import "DeviceInfo.h"

@interface Image : ContentModel

@property (strong, nonatomic) NSString *_id;
@property (strong, nonatomic) NSString *created;
@property (strong, nonatomic) NSString *updated;
@property (strong, nonatomic) NSString *applicationId;
@property (nonatomic) int state;
@property (nonatomic) double imageSource;
@property (strong, nonatomic) NSString *originalStreamId;
@property (strong, nonatomic) NSString *defaultStreamId;
@property (strong, nonatomic) NSArray *tags;
@property (strong, nonatomic) NSString *data;
@property (strong, nonatomic) DeviceInfo *deviceInfo;
@property (nonatomic) long submissionDate;
@property (strong, nonatomic) NSString *expirationDays;
@property (strong, nonatomic) NSString *resubmissionDate;
@property (strong, nonatomic) NSString *streamSubmissionDate;
@property (strong, nonatomic) NSString *userLanguage;
@property (strong, nonatomic) NSString *deleteOldStreams;
@property (strong, nonatomic) NSString *autoCrop;
@property (nonatomic) bool autoPad;
@property (nonatomic) bool hd;
@property (strong, nonatomic) NSString *creationAuthSessionId;
@property (nonatomic) int averageRating;
@property (strong, nonatomic) NSString *ratings;
@property (strong, nonatomic) NSArray *comments;
@property (strong, nonatomic) NSString *submitted;
@property (strong, nonatomic) NSString *approved;
@property (strong, nonatomic) NSString *moderationReason;
@property (nonatomic) int facebookLikes;
@property (nonatomic) int facebookShares;
@property (strong, nonatomic) NSString *imageFileName;

- (id)init;
- (id)initWithJson:(NSDictionary *)json;
- (void)setInfo:(NSDictionary *)json;
- (void)clear;
- (NSDictionary *)toDictionary;

- (NSString *)getId;
- (void)setId:(NSString *)_id;

@end

