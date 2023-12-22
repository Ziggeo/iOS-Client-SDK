//
//  StreamModel.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@interface StreamModel : NSObject

@property (nonatomic) bool _volatile;
@property (strong, nonatomic) NSString *token;
@property (strong, nonatomic) NSString *key;
@property (nonatomic) int creationType;
@property (nonatomic) int state;
@property (nonatomic) int streamable;
@property (strong, nonatomic) NSDictionary *videoAnalysis;
@property (strong, nonatomic) NSDictionary *audioTranscription;
@property (strong, nonatomic) NSArray *audioKeywords;
// when changing the type, make sure this is resolved asana:1112443089041912
@property (strong, nonatomic) NSArray *pushServicesSuccess;
@property (strong, nonatomic) NSString *defaultStreamId;
@property (strong, nonatomic) NSString *effectProfile;
@property (strong, nonatomic) NSString *effectProfileId;
@property (strong, nonatomic) NSString *videoProfileTranscoding;
@property (strong, nonatomic) NSString *videoType;
@property (strong, nonatomic) NSString *videoSubType;
@property (nonatomic) int imageSize;
@property (nonatomic) int audioSize;
@property (nonatomic) int videoSize;
@property (nonatomic) int videoWidth;
@property (nonatomic) int videoHeight;
@property (nonatomic) double duration;
@property (nonatomic) bool hasVideo;
@property (nonatomic) bool hasImage;
@property (nonatomic) bool hasAudio;
@property (nonatomic) bool videoHasAudio;
@property (strong, nonatomic) NSDictionary *nsfw;
@property (nonatomic) int submissionDate;
@property (strong, nonatomic) NSArray *subtitles;
@property (strong, nonatomic) NSString *type;
@property (nonatomic) int created;
@property (nonatomic) bool owned;
@property (strong, nonatomic) NSString *creationTypeString;
@property (strong, nonatomic) NSString *streamableString;
@property (strong, nonatomic) NSString *stateString;
@property (strong, nonatomic) NSString *videoToken;
@property (strong, nonatomic) NSString *parentStream;


- (id)initWithJson:(NSDictionary *)json;
- (void)setInfo:(NSDictionary *)json;
- (void)clear;
- (NSDictionary *)toDictionary;
- (bool)isVolatile;
- (void)setVolatile:(bool)_volatile;

@end

