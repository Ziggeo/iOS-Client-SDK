# Changelog

Version 1.1.48-blurring *(2024-06-04)*
-----------------------------
* The update raises minimum iOS deployment target to 15.0.
* The update makes minor changes in SDK API functions naming.
* The update fixes video recorder crash for unavailable camera.
* The update fixes potential memory leaks.


Version 1.1.47-blurring *(2024-01-22)*
-----------------------------
* The update changes cache functions.
* The update changes demo project.


Version 1.1.46-blurring *(2023-12-22)*
-----------------------------
* The update changes some models.
* The update changes demo project.

Version 1.1.45-blurring *(2023-10-20)*
-----------------------------
* The update changes delegate functions of mediapipe selfiesegmentation framework.
* The update fixes pausable recording function on blurring mode.

Version 1.1.44-blurring *(2023-09-28)*
-----------------------------
* The update adds stop recording confirmation dialog config.
* The update adds pause button on recording video/audio screen.

Version 1.1.42-blurring *(2023-09-21)*
-----------------------------
* The update adds ability to remove the video from uploading when connection is lost.
* The update adds method select the way to handle the video that failed.
* The update adds callback for the network connection status.
* The update adds custom recorder view.

Version 1.1.41-blurring *(2023-08-24)*
* The update changes `playVideo`, `showImage` and `playAudio` functions to use only a item.
* The update adds `playVideos`, `showImages` and `playAudios` functions to support multiple items.
* The update adds `playFromUri`, `playFromUris`, `showImageFromUri`, `showImageFromUris`, `playAudioWithPath` and `playAudioWithPaths`  functions to play from uri.
* The update changes `uploadFromFileSelector` to `startFileSelector`.
* The update creates getters and setters for `AppToken`, `ServerAuthToken` and `ClientAuthToken`.
* The update add configs refactorings for `FileSelectorConfig`, `RecorderConfig`, `UploadingConfig`, `PlayerConfig` and `QrScannerConfig`.

Version 1.1.40-blurring *(2023-03-27)*
-----------------------------
* The update adds pausable audio recording function.
* The update does not use `ZiggeoDelegate`, and use separated delegate(`ZiggeoHardwarePermissionDelegate`, `ZiggeoUploadingDelegate`, `ZiggeoFileSelectorDelegate`, `ZiggeoRecorderDelegate`, `ZiggeoSensorDelegate`, `ZiggeoPlayerDelegate`, `ZiggeoScreenRecorderDelegate`, `ZiggeoQRScannerDelegate`).
* The update changes some delegate functions.

Version 1.1.39-blurring *(2022-09-26)*
-----------------------------
* The update changes the pod name to `ZiggeoMediaSDK`.
* The update does not use `Ziggeo.framework`, and use `ZiggeoMediaSDK.framework`.
* The update changes `playVideo`, `showImage`, `startAudioPlayer` and `playFromUrl` functions to support multiple items.

Version 1.1.38-blurring *(2022-08-10)*
-----------------------------
* The update adds multiple file uploads, multiple video plays, multiple audio plays and multiple image views.
* The update adds QR code reader, video trim, sending email to support and sending report.
* The update fixes the problem of playing video from url.
* The update updates some screens.

Version 1.1.37-blurring *(2022-05-23)*
-----------------------------
* The update adds Mediapipe SelfieSegmentation.

Version 1.1.36 *(2022-03-28)*
-----------------------------
* The update removes GoogleAds.
* The update fixes black button problem of audio recording and playing screen on the dark mode.
* The update does not use `Ziggeo.xcframework`, and use `Ziggeo.framework`.

Version 1.1.35 *(2022-02-11)*
-----------------------------
* The update adds the blurring effect using mediapipe selfiesegmentation.
* SelfieSegmentation.framework does not contain bitcode.
* Users have to set "Enable Bitcode" to "No" on the Build Settings of the project.

Version 1.1.34 *(2022-01-05)*
-----------------------------
* The update implements `getVideoUrl` function.

Version 1.1.33 *(2021-10-20)*
-----------------------------
* The update merges several apis for videos, audios and images.

Version 1.1.32 *(2021-10-07)*
-----------------------------
* The update fixes several issues when playing and uploading files.

Version 1.1.31
---------------------------
* The update adds the missing events.

Version 1.1.30
---------------------------
* The update adds the updated uploading apis for videos, audios and images.

Version 1.1.29
---------------------------
* The update adds the audio recording and play functions.

Version 1.1.28
---------------------------
* The update fixes the black screen issues when records video using camera.
* And the updated changes the several file names.

Version 1.1.27
---------------------------
* The update fixes issues when the files could to be uploaded several times. 

Version 1.1.26
---------------------------
* The update fixes several issues which occur when uploading files.

Version 1.1.25
---------------------------
* The update adds 2 new methods to ZiggeoRecorder2 which allow better control over recording - startRecordingToFile and stopRecording.

Version 1.1.24
---------------------------
* The update fixes issues which arise in some cases with the GoogleAds-IMA-iOS-SDK dependency

Version 1.1.23
---------------------------
* The update adds support for pre-roll ads. See the new method `playWithAdsWithAdTagURL:playerContainer:playerViewController:;` in the class `ZiggeoPlayer`

Version 1.1.22
---------------------------
* The update fixes the issue where it was not possible to start multiple video uploads each right after other

Version 1.1.21
---------------------------
* The update brings a new feature - playback of videos from any URL.

Version 1.1.20
---------------------------
* The update brings a new feature - screen recording.

Version 1.1.19
---------------------------
* The update brings a fix to the issue - in some cases cached files were stored when recorder cache size was set to 0.

Version 1.1.18
---------------------------
* The update brings a new feature - ability to customize player caching parameters using a new method `setPlayerCacheConfig`.

Version 1.1.17
---------------------------
* The update brings a fix to the issue which might happen when creating application archive ("bitcode bundle could not be generated").

Version 1.1.16
---------------------------
* The update brings a new feature - ability to set recording start delay with countdown after pressing the record button.

Version 1.1.15
---------------------------
* The update brings a new feature - ability to add event handler to the event when video recording stops.

Version 1.1.14
---------------------------
* The update brings a fix to the customization of recorder buttons

Version 1.1.13
---------------------------
* The update brings a new feature - ability to adjust size of buttons and to set custom button icons in the video recorder .

Version 1.1.12
---------------------------
* The update brings a fix for compilation for iOS devices.

Version 1.1.11
---------------------------
* The update adds a new method setRecorderCacheConfig to ZiggeoRecorder

Version 1.1.10
---------------------------
* The update brings a fix for uploading videos from the camera roll in the latest iOS versions.

Version 1.1.9
---------------------------
* The update brings a fix for the compilation error in the advanced test app.

Version 1.1.8
---------------------------
* The update brings minor updates and fixes

Version 1.1.7
---------------------------
* the update brings iPad video orientation fix 

Version 1.1.6
---------------------------
* The update brings custom video and audio settings.

Version 1.1.5
---------------------------
* The update improves custom data support.

Version 1.1.4
---------------------------
* The update brings minor bugfixes mostly related to video orientation issues on some devices.

Version 1.1.3
---------------------------
* The update brings custom user data support on new video creation. See Custom User Data for details.

Version 1.1.2
---------------------------
* The update brings subtitles support for auto-transcripted videos. Another new feature - custom video gravity options for the Recorder.

Version 1.1.1
---------------------------
* The update brings new optional features such as light meter, audio level meter and face outlining. These features are also available in the updated ZiggeoRecorder delegate

Version 1.1.0
---------------------------
* The update bring hidden controls modes for recorder and player.

Version 1.0.9
---------------------------
* The update bring dashboard `/debugger` error reporting.

Version 1.0.8
---------------------------
* The update bring new `recordingQuality` parameter.

Version 1.0.7
---------------------------
* The update bring new `serverAuthToken` and `clientAuthToken` parameters in `ziggeo.connect` object (useful for global auth tokens).

Version 1.0.6
---------------------------
* The update bring minor bugfixes and new `data` parameter in `getImageForVideoByToken` method (useful for auth tokens).

Version 1.0.5
---------------------------
* New changes bring new features without changing the entry or exit points of any methods or functions. You can safely upgrade without any changes to your existing codes.

Added feature:
1. Video recorder can be utilized with `server_auth` and `client_auth` auth tokens.
	* To specify them for recorder you should use `extraArgsForCreateVideo`
2. Video player can be utilized with `server_auth` and `client_auth` auth tokens.
	* To specify them for player you should use [method described bellow](#initialization-with-optional-authorization-token)
