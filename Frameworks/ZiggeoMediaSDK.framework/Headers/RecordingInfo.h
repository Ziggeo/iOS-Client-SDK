//
//  RecordingInfo.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "ZiggeoApplication.h"


@interface RecordingInfo : NSObject

@property (strong, nonatomic) NSString *token;
@property (nonatomic) int fileType;
@property (nonatomic) Boolean uploaded;
@property (nonatomic) Boolean verified;
@property (nonatomic) Boolean processed;
@property (nonatomic) Boolean failed;
@property (nonatomic, strong) UIImage *coverShot;
@property (nonatomic, strong) NSDictionary *extraArgs;
@property (nonatomic, strong) NSMutableArray *urisForUploading;
@property (nonatomic) int uploadedParts;
@property (nonatomic, strong) NSString *uploadId;
@property (nonatomic, strong) NSString *streamToken;


- (id)initWithToken:(NSString *)token
           uploaded:(Boolean)uploaded
           verified:(Boolean)verified
          processed:(Boolean)processed
             failed:(Boolean)failed
          extraArgs:(NSDictionary *)extraArgs
   urisForUploading:(NSMutableArray *)urisForUploading
      uploadedParts:(int)uploadedParts
           uploadId:(NSString *)uploadId
        streamToken:(NSString *)streamToken;

- (void)addExtraArgs:(NSDictionary *)extraArgs;

@end
