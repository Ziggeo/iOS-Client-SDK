//
//  ButtonConfig.h
//  ZiggeoMediaSDK
//
//  Created by Severyn on 07/24/23.
//  Copyright © 2023 Ziggeo Inc. All rights reserved.
//

@import Foundation;
@import UIKit;


@interface ButtonConfig : NSObject

@property (nonatomic) NSString *imagePath;
@property (nonatomic) NSString *selectedImagePath;
@property (nonatomic) CGFloat scale;
@property (nonatomic) CGFloat *width;
@property (nonatomic) CGFloat *height;

@end
