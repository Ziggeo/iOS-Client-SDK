#
# Be sure to run `pod lib lint ZiggeoMediaSDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |spec|
  spec.name             = 'ZiggeoMediaSDK'
  spec.version          = '1.1.44-blurring'
  spec.summary          = 'Ziggeo iOS Client SDK'
  spec.description      = 'Ziggeo iOS recording and playback SDK'

  spec.homepage         = 'http://ziggeo.com'
  spec.license          = { :type => 'Confidential', :file => 'LICENSE' }
  spec.author           = { 'Ziggeo Inc' => 'support@ziggeo.com' }
  spec.source           = { :git => 'https://github.com/Ziggeo/iOS-Client-SDK.git', :tag => spec.version.to_s }
  
  spec.platform         = :ios, "11.0"
  spec.dependency       'GoogleAds-IMA-iOS-SDK', '3.13.0'

  spec.ios.deployment_target  = '11.0'
  spec.vendored_frameworks    = 'Frameworks/SelfieSegmentation.framework', 'Frameworks/ZiggeoMediaSDK.framework'
end
