//
//  MediaFields.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@interface MediaFields : NSObject

@property (strong, nonatomic) NSString *key;
@property (strong, nonatomic) NSString *contentType;
@property (strong, nonatomic) NSString *bucket;
@property (strong, nonatomic) NSString *xAmzAlgorithm;
@property (strong, nonatomic) NSString *xAmzCredential;
@property (strong, nonatomic) NSString *xAmzSignature;
@property (strong, nonatomic) NSString *xAmzDate;
@property (strong, nonatomic) NSString *xAmzSecurityToken;
@property (strong, nonatomic) NSString *policy;

- (id)init;
- (id)initWithJson:(NSDictionary *)json;
- (void)setInfo:(NSDictionary *)json;
- (void)clear;
- (NSString *)toString;
- (NSDictionary *)toDictionary;

@end

