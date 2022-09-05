#
# Be sure to run `pod lib lint iOS-Client-SDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |spec|
  spec.name             = 'iOS-Client-SDK'
  spec.version          = '1.1.38'
  spec.summary          = 'Ziggeo iOS Client SDK'
  spec.description      = 'Ziggeo iOS recording and playback SDK'

  spec.homepage         = 'http://ziggeo.com'
  spec.license          = { :type => 'Confidential', :file => 'LICENSE' }
  spec.author           = { 'Ziggeo Inc' => 'support@ziggeo.com' }
  spec.source           = { :git => 'https://github.com/Ziggeo/iOS-Client-SDK.git', :tag => spec.version.to_s }
  
  spec.platform         = :ios, "11.0"

  spec.ios.deployment_target = '10.0'
  spec.vendored_frameworks = 'ZiggeoSDK/Ziggeo.framework'
  
end
