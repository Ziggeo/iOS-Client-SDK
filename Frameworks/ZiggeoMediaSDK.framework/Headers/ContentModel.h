//
//  ContentModel.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "ZiggeoApplication.h"


@interface ContentModel : NSObject

@property (strong, nonatomic) NSString *key;
@property (strong, nonatomic) NSString *title;
@property (strong, nonatomic) NSString *desc;
@property (strong, nonatomic) NSString *stateString;
@property (strong, nonatomic) NSString *token;
@property (nonatomic) double date;
@property (nonatomic) double duration;

- (id)initWithJson:(NSDictionary *)json;
- (void)setInfo:(NSDictionary *)json;
- (void)clear;

@end

