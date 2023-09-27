//
//  ZiggeoConfig.h
//  ZiggeoMediaSDK
//
//  Created by Severyn on 07/24/23.
//  Copyright © 2023 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MobileCoreServices/MobileCoreServices.h>
#import <AVFoundation/AVFoundation.h>
#import <Photos/Photos.h>
@import UIKit;


@interface ZiggeoConfig : NSObject

@property (strong, nonatomic) NSString *server_api_url;
@property (strong, nonatomic) NSString *dev_server_api_url;
@property (strong, nonatomic) NSString *file_server_url;
@property (strong, nonatomic) NSString *cdn_api_url;
@property (strong, nonatomic) NSString *wowza_url;

- (id)initWithToken:(NSString *)token;

@end
