//
//  HomeViewController.swift
//  ZiggeoDemo
//
//  Created by Dragon on 6/24/22.
//

import UIKit
import ActiveLabel
import SideMenu
import ZiggeoMediaSDK
import AVKit
import AVFoundation
import MobileCoreServices


class HomeViewController: UIViewController {

    // MARK: - Outlets
    @IBOutlet weak var titleLabel: UILabel!
    @IBOutlet weak var popupMenuButton: UIView!
    @IBOutlet weak var popupMenuImageView: UIImageView!
    @IBOutlet weak var popupMenuView: UIStackView!
    @IBOutlet weak var containerView: UIView!
    @IBOutlet weak var playAllButtonView: UIView!
    
    // MARK: - Private variables
    private var isShowPopupMenu = false
    private var sideMenuVc: SideMenuNavigationController?
    
    // MARK: - Lifecycle
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        if let vc = Common.getStoryboardViewController("SideMenuViewController") as? SideMenuViewController {
            vc.delegate = self
            
            sideMenuVc = SideMenuNavigationController(rootViewController: vc)
            SideMenuManager.default.leftMenuNavigationController = sideMenuVc
            sideMenuVc?.settings = makeSettings()
            SideMenuManager.default.addPanGestureToPresent(toView: self.navigationController!.navigationBar)
//            SideMenuManager.default.addScreenEdgePanGesturesToPresent(toView: self.navigationController!.view)
            sideMenuVc?.statusBarEndAlpha = 0
        }
        refreshPopupMenu()
        
        Common.mainNavigationController = self.navigationController
        Common.homeViewController = self
        
        Common.ziggeo?.setHardwarePermissionDelegate(self)
        Common.ziggeo?.setUploadingDelegate(self)
        Common.ziggeo?.setFileSelectorDelegate(self)
        Common.ziggeo?.setRecorderDelegate(self)
        Common.ziggeo?.setSensorDelegate(self)
        Common.ziggeo?.setPlayerDelegate(self)
        Common.ziggeo?.setScreenRecorderDelegate(self)
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
    }
    
    // MARK: - Actions
    @IBAction func onShowMenu(_ sender: Any) {
        if (sideMenuVc != nil) {
            present(sideMenuVc!, animated: true, completion: nil)
        }
    }
    
    @IBAction func onPopupMenu(_ sender: Any) {
        isShowPopupMenu = !isShowPopupMenu
        refreshPopupMenu()
    }
    
    @IBAction func onPicker(_ sender: Any) {
        let fileSelectorConfig = FileSelectorConfig()
        fileSelectorConfig.maxDuration = 0
        fileSelectorConfig.minDuration = 0
        fileSelectorConfig.shouldAllowMultipleSelection = true
        fileSelectorConfig.mediaType = VIDEO | AUDIO | IMAGE
        fileSelectorConfig.extraArgs = ["tags" : "iOS,Choose,Media"]
        Common.ziggeo?.setFileSelectorConfig(fileSelectorConfig)
        
        Common.ziggeo?.startFileSelector()
        
        self.hideMenu()
    }
    
    @IBAction func onCameraImage(_ sender: Any) {
        let uploadingConfig = UploadingConfig()
        uploadingConfig.extraArgs = ["tags": "iOS,Take,Photo"]
        Common.ziggeo?.setUploadingConfig(uploadingConfig)

        Common.ziggeo?.startImageRecorder()
        
        self.hideMenu()
    }
    
    @IBAction func onVocieRecord(_ sender: Any) {
        let recorderConfig = RecorderConfig()
        recorderConfig.isPausedMode = true
        recorderConfig.extraArgs = ["tags": "iOS,Audio,Record"]
        Common.ziggeo?.setRecorderConfig(recorderConfig)
        
        Common.ziggeo?.startAudioRecorder()
        
        self.hideMenu()
    }
    
    @available(iOS 12.0, *)
    @IBAction func onScreenRecord(_ sender: Any) {
        Common.ziggeo?.startScreenRecorder(withAppGroup: "group.com.ziggeo.demo",
                                           preferredExtension: "com.ziggeo.demo.BroadcastExtension")
        
        self.hideMenu()
    }
    
    @IBAction func onVideoRecord(_ sender: Any) {
        if (UserDefaults.standard.bool(forKey: Common.Custom_Camera_Key) == true) {
            let vc = CustomVideoRecorder()
            self.present(vc, animated: true, completion: nil)

        } else {
            let recorderConfig = RecorderConfig()
            recorderConfig.shouldAutoStartRecording = true
            let startDelayString = UserDefaults.standard.string(forKey: Common.Start_Delay_Key)
            if (startDelayString != nil && startDelayString != "") {
                let startDelay = Int(startDelayString!) ?? 0
                recorderConfig.startDelay = Int32(startDelay)
            }
            recorderConfig.shouldDisableCameraSwitch = false
            recorderConfig.videoQuality = QUALITY_HIGH
            recorderConfig.facing = FACING_BACK
            recorderConfig.maxDuration = 0
            recorderConfig.blurMode = UserDefaults.standard.bool(forKey: Common.Blur_Mode_Key)
            recorderConfig.extraArgs = ["tags": "iOS,Video,Record",
                                        "client_auth" : "CLIENT_AUTH_TOKEN",
                                        "server_auth" : "SERVER_AUTH_TOKEN",
                                        "data" : ["foo": "bar"],
                                        "effect_profile" : "1234,5678"]
            Common.ziggeo?.setRecorderConfig(recorderConfig)
            
            Common.ziggeo?.record()
        }
        
        self.hideMenu()
    }
    
    @IBAction func onPlayAll(_ sender: Any) {
        if (Common.currentTab == VIDEO) {
            var tokens: [String] = []
            if (Common.recordingVideosController != nil) {
                for recording in Common.recordingVideosController!.recordings {
                    tokens.append(recording.token)
                }
            }
                       
            if (tokens.count > 0) {
                Common.ziggeo?.playVideos(tokens)
            } else {
                Common.showAlertView("Video recordings are empty.")
            }
            
        } else if (Common.currentTab == AUDIO) {
            var tokens: [String] = []
            if (Common.recordingAudiosController != nil) {
                for recording in Common.recordingAudiosController!.recordings {
                    tokens.append(recording.token)
                }
            }
            
            if (tokens.count > 0) {
                Common.ziggeo?.playAudios(tokens)
            } else {
                Common.showAlertView("Audio recordings are empty.")
            }
            
        } else {
            var tokens: [String] = []
            if (Common.recordingImagesController != nil) {
                for recording in Common.recordingImagesController!.recordings {
                    tokens.append(recording.token)
                }
            }
            
            if (tokens.count > 0) {
                Common.ziggeo?.showImages(tokens)
            } else {
                Common.showAlertView("Image recordings are empty.")
            }
        }
    }
    
    // MARK: - Private functions
    private func refreshPopupMenu() {
        if (isShowPopupMenu) {
            popupMenuView.isHidden = false
            popupMenuImageView.image = UIImage(named: "ic_close")
        } else {
            popupMenuView.isHidden = true
            popupMenuImageView.image = UIImage(named: "ic_plus")
        }
    }
    
    private func hideMenu() {
        isShowPopupMenu = false
        self.refreshPopupMenu()
    }
    
    private func makeSettings() -> SideMenuSettings {
        let presentationStyle = SideMenuPresentationStyle.menuSlideIn
        presentationStyle.backgroundColor = UIColor.black
        presentationStyle.menuStartAlpha = 0.2
        presentationStyle.menuScaleFactor = 1
        presentationStyle.onTopShadowOpacity = 1
        presentationStyle.presentingEndAlpha = 1
        presentationStyle.presentingScaleFactor = 1

        var settings = SideMenuSettings()
        settings.presentationStyle = presentationStyle
        settings.menuWidth = min(view.frame.width, view.frame.height) * 0.8
        settings.blurEffectStyle = UIBlurEffect.Style.dark
        settings.statusBarEndAlpha = 1

        return settings
    }
}

// MARK: -
extension HomeViewController: MenuActionDelegate {
    func didSelectLogoutMenu() {
        if let vc = Common.getStoryboardViewController("AuthViewController") as? AuthViewController {
            self.navigationController?.setViewControllers([vc], animated: true)
        }
    }
    
    func didSelectRecordingMenu() {
        self.titleLabel.text = "Recordings"
        popupMenuButton.isHidden = false
        isShowPopupMenu = false
        refreshPopupMenu()
        
        if let vc = Common.getStoryboardViewController("RecordingsViewController") as? RecordingsViewController {
            Common.subNavigationController?.setViewControllers([vc], animated: false)
        }
    }
    
    func didSelectVideoEditorMenu() {
        self.titleLabel.text = "Video Editor"
        popupMenuButton.isHidden = true
        popupMenuView.isHidden = true
        
        if let vc = Common.getStoryboardViewController("VideoEditorViewController") as? VideoEditorViewController {
            Common.subNavigationController?.setViewControllers([vc], animated: false)
        }
    }
    
    func didSelectSettingsMenu() {
        self.titleLabel.text = "Settings"
        popupMenuButton.isHidden = true
        popupMenuView.isHidden = true
        
        if let vc = Common.getStoryboardViewController("SettingsViewController") as? SettingsViewController {
            Common.subNavigationController?.setViewControllers([vc], animated: false)
        }
    }
    
    func didSelectAvailableSdksMenu() {
        self.titleLabel.text = "Available SDKs"
        popupMenuButton.isHidden = true
        popupMenuView.isHidden = true
        
        if let vc = Common.getStoryboardViewController("AvailableSdksViewController") as? AvailableSdksViewController {
            Common.subNavigationController?.setViewControllers([vc], animated: false)
        }
    }
    
    func didSelectTopClientsMenu() {
        self.titleLabel.text = "Top Clients"
        popupMenuButton.isHidden = true
        popupMenuView.isHidden = true
        
        if let vc = Common.getStoryboardViewController("TopClientsViewController") as? TopClientsViewController {
            Common.subNavigationController?.setViewControllers([vc], animated: false)
        }
    }
    
    func didSelectContactUsMenu() {
        self.titleLabel.text = "Contact Us"
        popupMenuButton.isHidden = true
        popupMenuView.isHidden = true
        
        if let vc = Common.getStoryboardViewController("ContactUsViewController") as? ContactUsViewController {
            Common.subNavigationController?.setViewControllers([vc], animated: false)
        }
    }
    
    func didSelectAboutMenu() {
        self.titleLabel.text = "About"
        popupMenuButton.isHidden = true
        popupMenuView.isHidden = true
        
        if let vc = Common.getStoryboardViewController("AboutViewController") as? AboutViewController {
            Common.subNavigationController?.setViewControllers([vc], animated: false)
        }
    }
    
    func didSelectLogMenu() {
        self.titleLabel.text = "Logs"
        popupMenuButton.isHidden = true
        popupMenuView.isHidden = true
        
        if let vc = Common.getStoryboardViewController("LogViewController") as? LogViewController {
            Common.subNavigationController?.setViewControllers([vc], animated: false)
        }
    }
    
    func didSelectPlayVideoFromUrlMenu() {
        Common.ziggeo?.play(fromUris: ["http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4",
                                       "http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/ForBiggerMeltdowns.mp4",
                                       "http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/Sintel.mp4"])
    }
    
    func didSelectPlayLocalVideoMenu() {
        let picker = UIImagePickerController()
        picker.allowsEditing = false
        picker.delegate = self
        picker.mediaTypes = [kUTTypeMovie as String]
        present(picker, animated: true)
    }
}

// MARK: - UIImagePickerControllerDelegate, UINavigationControllerDelegate
extension HomeViewController: UIImagePickerControllerDelegate, UINavigationControllerDelegate {
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        dismiss(animated: false) {
            let videoUrl = (info[.mediaURL] as! URL).path
            Common.ziggeo?.play(fromUri: videoUrl)
        }
    }
}

// MARK: - ZiggeoHardwarePermissionDelegate
extension HomeViewController: ZiggeoHardwarePermissionDelegate {
    func checkCameraPermission(_ granted: Bool) {
    }
    
    func checkMicrophonePermission(_ granted: Bool) {
    }
    
    func checkPhotoLibraryPermission(_ granted: Bool) {
    }
    
    func checkHasCamera(_ hasCamera: Bool) {
    }
    
    func checkHasMicrophone(_ hasMicrophone: Bool) {
    }
}

// MARK: - ZiggeoUploadingDelegate
extension HomeViewController: ZiggeoUploadingDelegate {
    func preparingToUpload(withPath sourcePath: String) {
        Common.addLog("Preparing To Upload: \(sourcePath)")
    }

    func failedToUpload(withPath sourcePath: String) {
        Common.addLog("Failed To Upload: \(sourcePath)")
    }
    
    func uploadStarted(withPath path: String, token: String, streamToken: String, backgroundTask: URLSessionTask) {
        Common.addLog("Upload Started: \(token) - \(streamToken)")
    }
    
    func uploadProgress(withPath sourcePath: String!, token: String, streamToken: String, totalBytesSent bytesSent: Int32, totalBytesExpectedToSend totalBytes: Int32) {
        Common.addLog("Upload Progress: \(bytesSent) - \(totalBytes)")
    }

    func uploadFinished(withPath sourcePath: String, token: String, streamToken: String) {
        Common.addLog("Upload Finished: \(token) - \(streamToken)")
        
        Common.recordingVideosController?.getRecordings()
        Common.recordingAudiosController?.getRecordings()
        Common.recordingImagesController?.getRecordings()
    }
    
    func uploadVerified(withPath sourcePath: String!, token: String, streamToken: String, with response: URLResponse, error: Error, json: [AnyHashable : Any]) {
        Common.addLog("Upload Verified: \(token) - \(streamToken)")
    }
    
    func uploadProcessing(withPath sourcePath: String, token: String, streamToken: String) {
        Common.addLog("Upload Processing: \(token) - \(streamToken)")
    }
    
    func uploadProcessed(withPath sourcePath: String, token: String, streamToken: String) {
        Common.addLog("Upload Processed: \(token) - \(streamToken)")
    }

    func delete(withToken token: String, streamToken: String, with response: URLResponse, error: Error, json: [AnyHashable : Any]) {
        Common.addLog("delete: \(token) - \(streamToken)")
    }
    
    func cancelUpload(byPath sourcePath: String!, deleteFile: Bool) {
    }
    
    func cancelCurrentUpload(_ deleteFile: Bool) {
    }
}

// MARK: - ZiggeoFileSelectorDelegate
extension HomeViewController: ZiggeoFileSelectorDelegate {
    func uploadSelected(_ paths: [String]!) {
        Common.addLog("Upload Selected: \(String(describing: paths))")
    }
    
    func uploadCancelledByUser() {
        Common.addLog("Upload Cancelled By User")
    }
}

// MARK: - ZiggeoRecorderDelegate
extension HomeViewController: ZiggeoRecorderDelegate {
    func recorderReady() {
        Common.addLog("Recorder Ready")
    }

    func recorderCountdown(_ secondsLeft: Int32) {
        Common.addLog("Recorder Countdown left: \(secondsLeft)")
    }

    func recorderStarted() {
        Common.addLog("Recorder Started")
    }
    
    func recorderStopped(_ path: String) {
        Common.addLog("Recorder Stopped")
    }
    
    func recorderCurrentRecordedDurationSeconds(_ seconds: Double) {
        Common.addLog("Recorder Recording Duration: \(seconds)")
    }
    
    func recorderPlaying() {
        Common.addLog("Recorder Playing")
    }
    
    func recorderPaused() {
        Common.addLog("Recorder Paused")
    }
    
    func recorderRerecord() {
        Common.addLog("Recorder Rerecord")
    }
    
    func recorderManuallySubmitted() {
        Common.addLog("Recorder Manually Submitted")
    }
    
    func streamingStarted() {
        Common.addLog("Streaming Started")
    }
    
    func streamingStopped() {
        Common.addLog("Streaming Stopped")
    }
    
    func recorderCancelledByUser() {
        Common.addLog("Recorder Cancelled By User")
    }
}

// MARK: - ZiggeoSensorDelegate
extension HomeViewController: ZiggeoSensorDelegate {
    func luxMeter(_ luminousity: Double) {
    }
    
    func audioMeter(_ audioLevel: Double) {
    }

    func faceDetected(_ faceID: Int32, rect: CGRect) {
    }
}

// MARK: - ZiggeoPlayerDelegate
extension HomeViewController: ZiggeoPlayerDelegate {
    func playerPlaying() {
        Common.addLog("Player Playing")
    }
    
    func playerPaused() {
        Common.addLog("Player Paused")
    }
    
    func playerEnded() {
        Common.addLog("Player Ended")
    }
    
    func playerSeek(_ positionMillis: Double) {
        Common.addLog("Player Seek: \(positionMillis)")
    }
    
    func playerReadyToPlay() {
        Common.addLog("Player Ready To Play")
    }
    
    func playerCancelledByUser() {
        Common.addLog("Player Cancelled By User")
    }
}

// MARK: - ZiggeoScreenRecorderDelegate
extension HomeViewController: ZiggeoScreenRecorderDelegate {
    
}
