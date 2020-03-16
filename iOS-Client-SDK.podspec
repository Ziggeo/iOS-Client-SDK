#
# Be sure to run `pod lib lint iOS-Client-SDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'iOS-Client-SDK'
  s.version          = '1.1.8'
  s.summary          = 'Ziggeo iOS Client SDK'
  s.description      = 'Ziggeo iOS recording and playback SDK'

  s.homepage         = 'http://ziggeo.com'
  s.license          = { :type => 'Confidential', :file => 'LICENSE' }
  s.author           = { 'Ziggeo Inc' => 'support@ziggeo.com' }
  s.source           = { :git => 'https://github.com/Ziggeo/iOS-Client-SDK.git', :tag => s.version.to_s }

  s.ios.deployment_target = '9.0'
  s.vendored_frameworks = 'Ziggeo/Output/Release-universal/Ziggeo.framework'
  
end
