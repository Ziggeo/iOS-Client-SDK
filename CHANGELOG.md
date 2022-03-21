# Changelog

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
