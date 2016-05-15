//
//  TableViewUploadingVideoCell.h
//  test
//
//  Copyright (c) 2015 Ziggeo Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
@import Foundation;

@interface TableViewUploadingVideoCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UIProgressView *progressView;
@property (strong, nonatomic) IBOutlet UIImageView *thumbView;
@property (nonatomic) NSString *sourceVideoPath;

@end
