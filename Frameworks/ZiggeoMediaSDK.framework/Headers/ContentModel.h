//
//  ContentModel.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@interface ContentModel : NSObject

@property (strong, nonatomic) NSString *key;
@property (strong, nonatomic) NSString *title;
@property (strong, nonatomic) NSString *_description;
@property (strong, nonatomic) NSString *stateString;
@property (strong, nonatomic) NSString *token;
@property (strong, nonatomic) NSString *streamToken;
@property (nonatomic) long date;
@property (nonatomic) double duration;

- (id)init;

- (NSString *)getDescription;
- (void)setDescription:(NSString *)description;
- (long)getDate;

@end

