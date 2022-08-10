//
//  ZiggeoPlayer.h
//  ZiggeoFramework
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"


@import AVFoundation;

@interface ZiggeoPlayer : AVQueuePlayer

@property (nonatomic, copy) void (^didFinishPlaying)(NSString * videoToken, NSError* error);

- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo
                     videoToken:(NSString *)token;

- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo
                     videoToken:(NSString *)token
                       videoUrl:(NSString *)url;

- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo
                    playerItems:(NSArray *)playerItems;

- (id)initWithZiggeoApplication:(Ziggeo *)ziggeo
                     playerItem:(AVPlayerItem *)playerItem;

+ (void)createPlayerWithAdditionalParams:(Ziggeo *)ziggeo
                              videoToken:(NSString *)token
                                  params:(NSDictionary*)params
                                callback:(void (^)(ZiggeoPlayer* player))callback;

+ (void)createPlayerWithAdditionalParams:(Ziggeo *)ziggeo
                              videoToken:(NSString *)token
                                videoUrl:(NSString *)url
                                  params:(NSDictionary*)params
                                callback:(void (^)(ZiggeoPlayer* player))callback;

+ (void)createPlayersWithAdditionalParams:(Ziggeo *)ziggeo
                              videoTokens:(NSArray *)tokens
                                videoUrls:(NSArray *)urls
                                   params:(NSDictionary*)params
                                 callback:(void (^)(ZiggeoPlayer* player))callback;

+ (void)createPlayerWithServerAuthToken:(Ziggeo *)ziggeo
                             videoToken:(NSString *)token
                              authToken:(NSString *)authToken
                               callback:(void (^)(ZiggeoPlayer* player))callback;

+ (void)createPlayerWithClientAuthToken:(Ziggeo *)ziggeo
                             videoToken:(NSString *)token
                              authToken:(NSString *)authToken
                               callback:(void (^)(ZiggeoPlayer* player))callback;

@end
