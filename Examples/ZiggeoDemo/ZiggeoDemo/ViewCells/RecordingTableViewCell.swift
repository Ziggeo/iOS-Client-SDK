import UIKit
import ZiggeoMediaSDK

class RecordingTableViewCell: UITableViewCell {

    @IBOutlet weak var containerView: UIView!
    @IBOutlet weak var iconImageView: UIImageView!
    @IBOutlet weak var tokenLabel: UILabel!
    @IBOutlet weak var stateLabel: UILabel!
    @IBOutlet weak var dateLabel: UILabel!
    
    func setData(icon: String, content: ContentModel) {
        containerView.setShadow(radius: 10, offset: CGSize(width: 0, height: 0), cornerRadius: 5)
        iconImageView.image = UIImage(named: icon)?.withRenderingMode(UIImage.RenderingMode.alwaysTemplate)
        iconImageView.tintColor = UIColor.black
        
        tokenLabel.text = content.token
        stateLabel.text = content.stateString
        dateLabel.text = Double(content.date).toDate
    }
}
