//
//  ZiggeoScreenRecorderSampleHandler.h
//  ZiggeoMediaSDK
//
//  Created by dragon on 11/15/18.
//  Copyright © 2016 Ziggeo Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
@import ReplayKit;

API_AVAILABLE(ios(10.0), tvos(10.0), macos(11.0))
@interface ZiggeoScreenRecorderSampleHandler : RPBroadcastSampleHandler

- (NSString *)getApplicationGroup;

@end

