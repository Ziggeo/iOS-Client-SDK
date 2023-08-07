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
- (NSString *)getToken;
- (void)setToken:(NSString *)token;
- (int)getFileType;
- (void)setFileType:(int)fileType;
- (Boolean)getUploaded;
- (void)setUploaded:(Boolean)uploaded;
- (Boolean)getVerified;
- (void)setVerified:(Boolean)verified;
- (Boolean)getProcessed;
- (void)setProcessed:(Boolean)processed;
- (Boolean)getFailed;
- (void)setFailed:(Boolean)failed;
- (NSMutableDictionary *)getExtraArgs;
- (void)setExtraArgs:(NSDictionary *)extraArgs;
- (void)addExtraArgs:(NSDictionary *)extraArgs;
- (NSMutableArray *)getUrisForUploading;
- (void)setUrisForUploading:(NSMutableArray *)urisForUploading;
- (int)getUploadedParts;
- (void)setUploadedParts:(int)uploadedParts;
- (NSString *)getUploadId;
- (void)setUploadId:(NSString *)uploadId;
- (NSString *)getStreamToken;
- (void)setStreamToken:(NSString *)streamToken;

@end
