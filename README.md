Ziggeo iOS SDK 2.0
=============

Ziggeo API (http://ziggeo.com) allows you to integrate video recording and playback with only two lines of code in your site, service or app. This is the iOS SDK repository. 

## v 1.1.32 to v.1.1.33
The update merges several apis for videos, audios and images.

## v 1.1.31 to v.1.1.32
The update fixes several issues when playing and uploading files.

## v 1.1.30 to v.1.1.31
The update adds the missing events.

## v 1.1.29 to v.1.1.30
The update adds the updated uploading apis for videos, audios and images.

## v 1.1.28 to v.1.1.29
The update adds the audio recording and play functions.

## v 1.1.27 to v.1.1.28
The update fixes the black screen issues when records video using camera.
And the updated changes the several file names.

## v 1.1.26 to v.1.1.27
The update fixes issues when the files could to be uploaded several times. 

## v 1.1.25 to v.1.1.26
The update fixes several issues which occur when uploading files.

## v 1.1.24 to v.1.1.25
The update adds 2 new methods to ZiggeoRecorder2 which allow better control over recording - startRecordingToFile and stopRecording.

## v 1.1.23 to v.1.1.24
The update fixes issues which arise in some cases with the GoogleAds-IMA-iOS-SDK dependency

## v 1.1.22 to v.1.1.23
The update adds support for pre-roll ads. See the new method `playWithAdsWithAdTagURL:playerContainer:playerViewController:;` in the class `ZiggeoPlayer`

## v 1.1.21 to v.1.1.22
The update fixes the issue where it was not possible to start multiple video uploads each right after other

## v 1.1.20 to v.1.1.21
The update brings a new feature - playback of videos from any URL.

## v 1.1.19 to v.1.1.20
The update brings a new feature - screen recording.

## v 1.1.18 to v.1.1.19
The update brings a fix to the issue - in some cases cached files were stored when recorder cache size was set to 0.

## v 1.1.17 to v.1.1.18
The update brings a new feature - ability to customize player caching parameters using a new method `setPlayerCacheConfig`.

## v 1.1.16 to v.1.1.17
The update brings a fix to the issue which might happen when creating application archive ("bitcode bundle could not be generated").

## v 1.1.15 to v.1.1.16
The update brings a new feature - ability to set recording start delay with countdown after pressing the record button.

## v 1.1.14 to v.1.1.15
The update brings a new feature - ability to add event handler to the event when video recording stops.

## v 1.1.13 to v.1.1.14
The update brings a fix to the customization of recorder buttons

## v 1.1.12 to v.1.1.13
The update brings a new feature - ability to adjust size of buttons and to set custom button icons in the video recorder .

## v 1.1.11 to v.1.1.12
The update brings a fix for compilation for iOS devices.

## v 1.1.10 to v.1.1.11
The update adds a new method setRecorderCacheConfig to ZiggeoRecorder

## v 1.1.9 to v.1.1.10
The update brings a fix for uploading videos from the camera roll in the latest iOS versions.

## v 1.1.8 to v.1.1.9
The update brings a fix for the compilation error in the advanced test app.

## v 1.1.7 to v.1.1.8
The update brings minor updates and fixes

## v 1.1.6 to v.1.1.7
the update brings iPad video orientation fix 

## v 1.1.5 to v.1.1.6
The update brings custom video and audio settings.

## v 1.1.4 to v.1.1.5
The update improves custom data support.

## v 1.1.3 to v.1.1.4
The update brings minor bugfixes mostly related to video orientation issues on some devices.

## v 1.1.2 to v.1.1.3
The update brings custom user data support on new video creation. See Custom User Data for details.

## v 1.1.1 to v.1.1.2
The update brings subtitles support for auto-transcripted videos. Another new feature - custom video gravity options for the Recorder.

## v 1.1.0 to v.1.1.1
The update brings new optional features such as light meter, audio level meter and face outlining. These features are also available in the updated ZiggeoRecorder delegate

## v.1.0.9 to v.1.1.0
The update bring hidden controls modes for recorder and player.

## v.1.0.8 to v.1.0.9
The update bring dashboard `/debugger` error reporting.

## v.1.0.7 to v.1.0.8
The update bring new `recordingQuality` parameter.

## v.1.0.6 to v.1.0.7
The update bring new `serverAuthToken` and `clientAuthToken` parameters in `ziggeo.connect` object (useful for global auth tokens).

## v.1.0.5 to v.1.0.6
The update bring minor bugfixes and new `data` parameter in `getImageForVideoByToken` method (useful for auth tokens).

## v.1.0.4 to v.1.0.5

New changes bring new features without changing the entry or exit points of any methods or functions. You can safely upgrade without any changes to your existing codes.

Added feature:
1. Video recorder can be utilized with `server_auth` and `client_auth` auth tokens.
	* To specify them for recorder you should use `extraArgsForCreateVideo`
2. Video player can be utilized with `server_auth` and `client_auth` auth tokens.
	* To specify them for player you should use [method described bellow](#initialization-with-optional-authorization-token)

## Setup
- Create iOS App
- Add the following frameworks
	- AVFoundation.framework
	- Ziggeo.framework
- Make sure Ziggeo.framework is added to Embedded Binaries and Linked Framework sections in your app target settings

## Building/Packaging App
- Using `universal` framework is ideal for building apps that run on simulators and actual devices.
  See: _iOS-Client-SDK/Output/ directory

## Preparing App for submission to App Store
- Create "new run script phase" in the application target build settings to strip unused architectures. Use the script provided with the _iOS-Client-SDK/TestApp_ example (TestApp target settings -> Build phases -> Run script section)


# Basic Usage
## Initialize Application

```
#import "Ziggeo/Ziggeo.h"

Ziggeo* m_ziggeo = [[Ziggeo alloc] initWithToken:@"ZIGGEO_APP_TOKEN" Delegate:self];];
```

## Usage
### Record Video
```
    [m_ziggeo record];
```

Add audio category setup to enable playback and recording while application is in silent mode. This category will also allow to record background audio.
```
//AppDelegate.m
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord
                                     withOptions:AVAudioSessionCategoryOptionDuckOthers | AVAudioSessionCategoryOptionDefaultToSpeaker
                                           error:nil];
    return YES;
}
```

### Play Video With Token
```
[m_ziggeo playVideo:@"VIDEO_TOKEN"];
```

### Play Video With Url
```
[m_ziggeo playFromUri:Video_Url];
```

### Record Audio
```
[m_ziggeo startAudioRecorder];
```

### Play Audio
```
[m_ziggeo startAudioPlayer:@"AUDIO_TOKEN"];
```

### Record Image
```
[m_ziggeo startImageRecorder];
```

### Show Image
```
[m_ziggeo showImage:@"IMAGE_TOKEN"];
```

### Start Screen Recorder
```
[m_ziggeo startScreenRecorder];
```

### Upload From Path
```
[m_ziggeo uploadFromPath:@"FILE_PATH" :@{}];
```

### Upload From File Selector
```
[m_ziggeo uploadFromFileSelector:@{}];
```

### Cancel Request
```
[m_ziggeo cancelRequest];
```

### Start QR Scanner
```
[m_ziggeo startQrScanner:@{}];
```


## Config

### Uploading Config
```
NSDictionary *config = [NSDictionary dictionaryWithObject:@"iOS_Choose_Media" forKey:@"tags"];
[m_ziggeo setUploadingConfig:config];
```

### Streaming Recording
```
[m_ziggeo setLiveStreamingEnabled:YES];
```
Streaming recording mode will upload the video stream during the recording without caching to local file first. Video preview and video re-record are not available in this mode.

### Autostart Recording After
```
[m_ziggeo setAutostartRecordingAfter:0];
```

### Start Delay
```
[m_ziggeo setStartDelay:0];
```

### Extra Argment For Recorder
```
NSMutableDictionary *map = [NSMutableDictionary dictionary];
map[@"blur_effect"] = @"false";
map[@"effect_profile"] = @"12345";
map[@"data"] = @{@"foo": @"bar"};
map[@"client_auth"] = @"CLIENT_AUTH_TOKEN";
map[@"server_auth"] = @"SERVER_AUTH_TOKEN";
[m_ziggeo setExtraArgsForRecorder:map];
```

### Extra Argment For Recorder
```
NSMutableDictionary *map = [NSMutableDictionary dictionary];
map[@"hideRecorderControls"] = @"false";
[m_ziggeo setThemeArgsForRecorder:map];
```

### Enable Cover Selector Dialog
```
[m_ziggeo setCoverSelectorEnabled:YES];
```

### Capture Duration Limit
```
[m_ziggeo setMaxRecordingDuration:20];
```

### Set Video Width
```
[m_ziggeo setVideoWidth:1920];
```

### Set Video Height
```
[m_ziggeo setVideoHeight:1080];
```

### Set Video Bitrate
```
[m_ziggeo setVideoBitrate:1024 * 1024 * 2];
```

### Set Audio Sample Rate
```
[m_ziggeo setAudioSampleRate:44100];
```

### Set Audio Bitrate
```
[m_ziggeo setAudioBitrate:128 * 1024];
```

### Set CAmera Switch Enabled
```
[m_ziggeo setCameraSwitchEnabled:YES];
```

### Set Send Immediately
```
[m_ziggeo setSendImmediately:YES];
```

### Set Recording Quality
```
//[m_ziggeo setQuality:LowQuality];
[m_ziggeo setQuality:MediumQuality];
//[m_ziggeo setQuality:HighestQuality];
```

### Set Camera
```
[m_ziggeo setCamera:0];
```

### Set Extra Argument For Player
```
[m_ziggeo setExtraArgsForPlayer:@{}];
```

### Set Theme Argument For Player 
```
NSMutableDictionary *map = [NSMutableDictionary dictionary];
map[@"hidePlayerControls"] = @"false";
[m_ziggeo setThemeArgsForPlayer:map];
```

### Set Player Cache Config
```
[m_ziggeo setPlayerCacheConfig:@{}];
```

### Set Ads Url
```
[m_ziggeo setAdsURL:@"ADS_URL"];
```


### Delegate
#### ZiggeoRecorderDelegate
You can use ZiggeoRecorderDelegate in your app to be notified about video recording events.
```
@interface ViewController : UIViewController <ZiggeoRecorderDelegate>

...
- (void)luxMeter:(double)luminousity {
    //
}

- (void)audioMeter:(double)audioLevel {
    //
}

- (void)faceDetected:(int)faceID rect:(CGRect)rect {
    // this method will be called when face is detected
}

- (void)ziggeoRecorderReady {
    // this method will be called when recorder is ready to recorder
}

- (void) ziggeoRecorderCanceled {
    // this method will be called when recorder is canceled
}

- (void)ziggeoRecorderStarted {
    // this method will be called when recorder is started
}

- (void)ziggeoRecorderStopped:(NSString *)path {
    // this method will be called when recorder is stopped
}

- (void)ziggeoRecorderCurrentRecordedDurationSeconds:(double)seconds {
    // this method will be called while recording
}

- (void)ziggeoRecorderPlaying {
    // this method will be called when recorder plays the recorded audio
}

- (void)ziggeoRecorderPaused {
    // this method will be called when recorder pauses the recorded audio
}

- (void)ziggeoRecorderRerecord {
    // this method will be called when recorder is rerecorded
}

- (void)ziggeoRecorderManuallySubmitted {
    // this method will be called when recorded file(video or audio) is uploaded by the user
}

- (void)ziggeoStreamingStarted {
    // Triggered when a streaming process has started (Press on the Record button if countdown 0 or after the countdown goes to 0)
}

- (void)ziggeoStreamingStopped {
    // Triggered when a streaming process has stopped (automatically after reaching the maximum duration or manually.)
}
```


#### ZiggeoUploadDelegate
You can use ZiggeoUploadDelegate in your app to be notified about file(video, audio, image) uploading events.
```
@interface ViewController : UIViewController <ZiggeoUploadDelegate>

- (void)preparingToUploadWithPath:(NSString*)sourcePath {
    // this method will be called first before any Ziggeo API interaction
}

- (void)failedToUploadWithPath:(NSString*)sourcePath {
    // this method will be called when file(video, audio, image) uploading was failed
}

- (void)uploadStartedWithPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken backgroundTask:(NSURLSessionTask*)uploadingTask {
    // this method will be called on actual file(video, audio, image) upload start after empty file(video, audio, image) creation on Ziggeo platform
}

- (void)uploadProgressForPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken totalBytesSent:(int)bytesSent totalBytesExpectedToSend:(int)totalBytes {
    // this method will be called while uploading the file(video, audio, image)
}

- (void)uploadFinishedForPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken {
    // this method will be called after the file(video, audio, image) was uploaded
}

- (void)uploadVerifiedWithPath:(NSString*)sourcePath token:(NSString*)token streamToken:(NSString *)streamToken withResponse:(NSURLResponse*)response error:(NSError*)error json:(NSDictionary*)json {
    // this method will be called when file(video, audio, image) upload finished successfully or failed
}

- (void)uploadProcessingWithPath:(NSString *)sourcePath token:(NSString *)token streamToken:(NSString *)streamToken {
    // this method will be called while processing the file(video, audio, image)
}

- (void)uploadProcessedWithPath:(NSString *)sourcePath token:(NSString *)token streamToken:(NSString *)streamToken {
    // this method will be called when uploading the file(video, audio, image) was finished by ziggeo servers
}

- (void)deleteWithToken:(NSString*)token streamToken:(NSString*)streamToken withResponse:(NSURLResponse*)response error:(NSError*)error json:(NSDictionary*)json {
    // this method will be called when file(video, audio, image) was deleted
}
```


#### ZiggeoPlayerDelegate
You can use ZiggeoPlayerDelegate in your app to be notified about file(video, audio) playing events.
```
- (void)ziggeoPlayerPlaying {
    // Fires any time a playback is started
}

- (void)ziggeoPlayerPaused {
    // Fires when the pause button is clicked (and at the end of the video)
}

- (void)ziggeoPlayerEnded {
    // Fires when a video playback has ended (reaches the end)
}

- (void)ziggeoPlayerSeek:(double)positionMillis {
    // Triggered when the user moves the progress indicator to continue video playback from a different position
}

- (void)ziggeoPlayerReadyToPlay {
    // Triggered when a video player is ready to play a video
}
```


#### ZiggeoHardwarePermissionCheckDelegate
You can use ZiggeoHardwarePermissionCheckDelegate in your app to be notified about hardware and permission.
```
@interface ViewController : UIViewController <ZiggeoHardwarePermissionCheckDelegate>

- (void)checkCameraPermission:(BOOL)granted {
    // this method will return when camera access permission is granted or denied.
}

- (void)checkMicrophonePermission:(BOOL)granted {
    // this method will return when microphone access permission is granted or denied.
}

- (void)checkPhotoLibraryPermission:(BOOL)granted {
    // this method will return when photo library access permission is granted or denied.
}

- (void)checkHasCamera:(BOOL)hasCamera {
    // this method will return whether camera hardware is detected or not.
}

- (void)checkHasMicrophone:(BOOL)hasMicrophone {
    // this method will return whether microphone hardware is detected or not.
}
```
