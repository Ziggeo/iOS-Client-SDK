//
//  ZiggeoAudioPlayer.h
//  Ziggeo
//
//  Copyright (c) 2021 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZiggeoApplication.h"
@class ZiggeoAudioPlayer;


@protocol ZiggeoAudioPlayerDelegate <NSObject>

- (void)audioPlayerDidLoadedItem:(ZiggeoAudioPlayer *)audioPlayer;
- (void)audioPlayerPlayWith:(ZiggeoAudioPlayer *)audioPlayer Progress:(float)progress;
- (void)audioPlayerDidFinishItem:(ZiggeoAudioPlayer *)audioPlayer;

@end


@interface ZiggeoAudioPlayer : NSObject <DVAssetLoaderDelegatesDelegate>

@property (nonatomic, assign) id<ZiggeoAudioPlayerDelegate>delegate;
@property (nonatomic, assign) BOOL isPlaying;

- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo audioToken:(NSString*)token;
- (id)initWithZiggeoApplication:(Ziggeo*)ziggeo audioToken:(NSString*)token audioUrl:(NSString*)url;
- (void)play;
- (void)pause;
- (void)seekToTime:(float)time;
- (double)duration;

@end
