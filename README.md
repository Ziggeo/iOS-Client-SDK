Ziggeo iOS SDK 2.0
=============

Ziggeo API (http://ziggeo.com) allows you to integrate video recording and playback with only two lines of code in your site, service or app. This is the iOS SDK repository. 

## Setup
- Create iOS App
- Add the following frameworks
	- AVFoundation.framework
	- Ziggeo.framework
- Make sure Ziggeo.framework is added to Embedded Binaries and Linked Framework sections in your app target settings


# Basic usage
## Initialize Application

```
#import "Ziggeo/Ziggeo.h"

Ziggeo* m_ziggeo = [[Ziggeo alloc] initWithToken:@"ZIGGEO_APP_TOKEN"];
```

## Player

### Initialization
```
- (ZiggeoPlayer*) createPlayer
{
    return [[ZiggeoPlayer alloc] initWithZiggeoApplication:m_ziggeo videoToken:@"ZIGGEO_VIDEO_TOKEN"];
}
```

### Fullscreen playback
```
    AVPlayerViewController* playerController = [[AVPlayerViewController alloc] init];
    playerController.player = [self createPlayer];
    [self presentViewController:playerController animated:true completion:nil];
    [playerController.player play];
```

### Embedded playback
```
    ZiggeoPlayer* player = [self createPlayer];
    AVPlayerLayer* playerLayer = [AVPlayerLayer playerLayerWithPlayer:player];
    playerLayer.frame = self.videoViewPlaceholder.frame;
    [self.videoViewPlaceholder.layer addSublayer:playerLayer];
    [player play];
```

## Recorder

```
    ZiggeoRecorder* recorder = [[ZiggeoRecorder alloc] initWithZiggeoApplication:m_ziggeo];
    [self presentViewController:recorder animated:true completion:nil];
```

### Capture duration limit
```
    ZiggeoRecorder* recorder = [[ZiggeoRecorder alloc] initWithZiggeoApplication:m_ziggeo];
	recorder.videoMaximumDuration = 20; //optional capture duration limit
    [self presentViewController:recorder animated:true completion:nil];
```

### Enable cover selector dialog
```
    recorder.coverSelectorEnabled = YES;
```

### Select existing video instead of capturing a new one

```
    [recorder selectExistingVideo];
```

### Disable camera flip button

```
    recorder.cameraFlipButtonVisible = NO;
```

### Set active camera device

```
    recorder.cameraDevice = UIImagePickerControllerCameraDeviceRear;
```

### Delegate
You can use ZiggeoVideosDelegate in your app to be notified about video uploading events.
```
@interface ViewController : UIViewController <ZiggeoVideosDelegate>

...

{
	...
	[m_ziggeo videos].delegate = self;
}

-(void) videoUploadStartedWithPath:(NSString*)sourcePath backgroundTask:(NSURLSessionTask*)uploadingTask {

}

-(void) videoUploadCompleteForPath:(NSString*)sourcePath withResponse:(NSURLResponse*)response error:(NSError*)error json:(NSDictionary*)json {

}

-(void) videoUploadProgressForPath:(NSString*)sourcePath totalBytesSent:(int)bytesSent totalBytesExpectedToSend:(int)totalBytes {
}

```

# Advanced SDK usage
# Ziggeo API access
You can use the SDK to access Ziggeo Server API methods in the async manner. The SDK provides next functionality:
- Create/remove/index videos
- Custom Ziggeo Embedded Server API requests 

All the API methods are working asynchronously and never blocking the calling thread. You may optionally use custom callbacks (completion blocks) to receive the results.

## Videos API

### Get video accessor object
```
    ZiggeoVideos* videos = [m_ziggeo videos];
```

### Get all videos
```
    [videos indexWithData:nil Callback:^(NSArray *jsonArray, NSError *error) {
    	//the completion block will be executed asynchronously on the response received
        NSLog(@"videos: %@\nerror: %@", jsonArray, error);
    }];
```

### Create new video
#### Basic
```
	[videos createVideoWithData:nil file:videoPath cover:nil callback:nil Progress:nil];
```

#### Advanced
You can add your custom completion/progress callbacks here to make the SDK inform your app about uploading progress and response. Cover image is optional and could be nil, making Ziggeo platform to generate default video cover
```
    [videos createVideoWithData:nil file:videoPath cover:(UIImage*)cover
    	callback:^(NSDictionary *jsonObject, NSURLResponse *response, NSError *error) {
	    	NSLog(@"video upload complete: %@, error = %@", jsonObject, error);
   		} Progress:^(int bytesSent, int totalBytes) {
    		NSLog(@"video upload progress: %i/%i", bytesSent, totalBytes);
    	}
    }];
```

### Delete video
```
	[[self.ziggeo videos] deleteVideoByToken:videoToken 
    	callback:^(NSData *responseData, NSURLResponse *response, NSError *error) {
		//update UI 	
	}];
```

### Get video URL to be used in your own custom player
```
    NSURL* videoURL = [NSURL URLWithString:[videos getURLForVideoByToken:token]];
```

### Get remote video thumb asynchronously
Remote video thumbs are cached on client side, so you can call the method as frequently as you wish without the performance or network load impact
```
    [videos getImageForVideoByToken:token 
    	callback:^(UIImage *image, NSURLResponse *response, NSError *error) {
        //update UI with the received image
    }];
```

### Generate local video thumb asynchronously
Local video thumbs are cached on client side, so you can call the method as frequently as you wish without the performance impact
```
	[videos getImageForVideoByPath:localVideoPath 
    	callback:^(UIImage *image, NSError *error) {
    	//update UI with the received image
	}];
```

## Custom Ziggeo API requests
The SDK provides an opportunity to make custom requests to Ziggeo Embedded Server API. You can make POST/GET/custom_method requests and receive RAW data, json-dictionary or string as the result.

### Get API accessor object
```
ZiggeoConnect* connection = [m_ziggeo connect];
```

### Make POST request and parse JSON response
```
[connection postJsonWithPath:path Data:(NSDictionary*)data 
	Callback:^(NSDictionary *jsonObject, NSURLResponse *response, NSError *error) {
    	//jsonObject contains parsed json response received from Ziggeo API Server
	}
];
```

### Make POST request and get RAW data response
```
[connection postWithPath:path Data:(NSDictionary*)data 
	Callback:^(NSData *data, NSURLResponse *response, NSError *error) {
    	//data object contains raw data response received from Ziggeo API Server
	}
];
```

### Make GET request and get string response
```
[connection getStringWithPath:path Data:(NSDictionary*)data 
	Callback:^(NSString *string, NSURLResponse *response, NSError *error) {
    	//the string contains stringified response received from Ziggeo API Server
	}
];
```
There are bunch of other methods for different http methods and response types.
