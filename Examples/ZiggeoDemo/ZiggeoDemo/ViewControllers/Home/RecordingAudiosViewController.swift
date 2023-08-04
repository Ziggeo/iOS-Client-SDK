//
//  RecordingAudiosViewController.swift
//  ZiggeoDemo
//
//  Created by Dragon on 6/24/22.
//

import UIKit
import ZiggeoMediaSDK
import SVProgressHUD

class RecordingAudiosViewController: UIViewController {
    
    // MARK: - Outlets
    @IBOutlet weak var recordingsTableView: UITableView!
    
    // MARK: - Private variables
    var recordings: [ContentModel] = []
    private let refreshControl = UIRefreshControl()
    private let reuseIdentifier = "RecordingTableViewCell"
    
    // MARK: - Lifecycle
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        Common.recordingAudiosController = self
        
        recordingsTableView.delegate = self
        recordingsTableView.dataSource = self
        recordingsTableView.estimatedRowHeight = 120
        recordingsTableView.rowHeight = UITableView.automaticDimension
        recordingsTableView.register(UINib(nibName: reuseIdentifier, bundle: nil), forCellReuseIdentifier: reuseIdentifier)
        
        refreshControl.attributedTitle = NSAttributedString(string: "Pull to refresh")
        refreshControl.addTarget(self, action: #selector(refresh(_:)), for: .valueChanged)
        recordingsTableView.addSubview(refreshControl)
        
        getRecordings()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)

        Common.currentTab = MEDIA_TYPE_AUDIO
    }
    
    // MARK: - Functions
    @objc func refresh(_ sender: AnyObject) {
       getRecordings()
    }
    
    func getRecordings() {
        SVProgressHUD.show()
        Common.ziggeo?.audios().index([:], callback: { array, error in
            SVProgressHUD.dismiss()
            self.refreshControl.endRefreshing()
            
            self.recordings.removeAll()
            if (array != nil) {
                for i in 0..<array!.count {
                    if let item = array![i] as? ContentModel {
                        if item.stateString != ZIGGEO_STATUS_EMPTY && item.stateString != ZIGGEO_STATUS_DELETED {
                            self.recordings.append(item)
                        }
                    }
                }
            }
            self.recordingsTableView.reloadData()
        })
    }
}

// MARK: - UITableViewDelegate, UITableViewDataSource
extension RecordingAudiosViewController: UITableViewDelegate, UITableViewDataSource {
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return recordings.count
    }

    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let recording = recordings[indexPath.row]
        let cell = tableView.dequeueReusableCell(withIdentifier: reuseIdentifier, for: indexPath) as! RecordingTableViewCell
        cell.setData(icon: "ic_tab_audio", content: recording)
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        
        SVProgressHUD.show()
        Common.ziggeo?.audios().get(self.recordings[indexPath.row].token, data: [:], callback: { content, response, error in
            SVProgressHUD.dismiss()
            if let vc = Common.getStoryboardViewController("RecordingDetailViewController") as? RecordingDetailViewController {
                vc.mediaType = MEDIA_TYPE_AUDIO
                vc.recording = content
                vc.recordingDelegate = self
                Common.mainNavigationController?.pushViewController(vc, animated: true)
            }
        })
    }
}

// MARK: - RecordingDelegate
extension RecordingAudiosViewController: RecordingDelegate {
    func recordingDeleted(_ token: String) {
        self.recordings = self.recordings.filter({ recording in
            return recording.token != token
        })
        self.recordingsTableView.reloadData()
    }
}
