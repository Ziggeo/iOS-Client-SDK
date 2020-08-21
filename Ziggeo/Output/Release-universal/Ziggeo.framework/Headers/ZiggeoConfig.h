//
//  ZiggeoConfig.h
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ZiggeoConfig : NSObject

@property (strong, nonatomic) NSString *server_api_url;
@property (strong, nonatomic) NSString *cdn_api_url;
@property (strong, nonatomic) NSString *wowza_url;

@property (nonatomic) uint64_t cache_size;
@property (nonatomic) uint64_t player_cache_size;
@property (strong, nonatomic) NSString *cache_root;
@property (strong, nonatomic) NSString *player_cache_root;

-(id)initWithToken:(NSString*)token;

-(void) setRecorderCacheConfig:(NSDictionary *)recorderCacheConfig;
-(void) setPlayerCacheConfig:(NSDictionary *)config;

@end
