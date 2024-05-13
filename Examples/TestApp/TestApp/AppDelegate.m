//
//  AppDelegate.m
//  TestApp
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import "AppDelegate.h"
#import "ZiggeoMediaSDK/ZiggeoMediaSDK.h"


@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    UNUserNotificationCenter* center = [UNUserNotificationCenter currentNotificationCenter];
    center.delegate = self;
    [center requestAuthorizationWithOptions:(UNAuthorizationOptionAlert + UNAuthorizationOptionSound + UNAuthorizationOptionBadge)
                          completionHandler:^(BOOL granted, NSError * _Nullable error) {
                              // Enable or disable features based on authorization.
                          }];
    [[UIApplication sharedApplication] registerForRemoteNotifications];
    
    return YES;
}

//finish background upload for closed or purged app
- (void)application:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)(void))completionHandler {
    Ziggeo* ziggeo = [[Ziggeo alloc] initWithToken:@"ZIGGEO_APP_TOKEN"];
    [ziggeo.connect postWithPath:identifier data:nil callback:^(NSData *data, NSURLResponse *response, NSError *error) {
        completionHandler();
    }];
}

- (void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions))completionHandler {
    completionHandler(UNNotificationPresentationOptionSound |
                      UNNotificationPresentationOptionBadge |
                      UNNotificationPresentationOptionBanner |
                      UNNotificationPresentationOptionList);
}

@end
