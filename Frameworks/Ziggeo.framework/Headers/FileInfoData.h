//
//  FileInfoData.h
//  ZiggeoFramework
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>


@interface FileInfoData : NSObject

@property (strong, nonatomic) NSString *path;
@property (strong, nonatomic) NSURL *url;
@property (strong, nonatomic) NSString *mimeType;
@property (strong, nonatomic) NSString *name;

- (id)initWithPath:(NSString *)path mimeType:(NSString *)mimeType name:(NSString *)name;
- (id)initWithUrl:(NSURL *)url mimeType:(NSString *)mimeType name:(NSString *)name;

@end

