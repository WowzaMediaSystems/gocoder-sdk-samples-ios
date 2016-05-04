WowzaGoCoderSDK Sample Apps

There are 4 sample app projects contained within this "sample-apps" folder:

1. WowzaGoCoderSDKSampleApp.xcodeproj
This is an Objective-C application that demonstrates how to use the SDK to
capture and broadcast video using the device's internal cameras. The Settings
screen in the app allows you to modify various video, audio, capture and
broadcast settings. 

2. WowzaGoCoderSDKSampleApp.swift.xcodeproj
This is a Swift application that demonstrates how to use the SDK. It shares
the exact same functionality as the Objective-C counterpart described
above.

3. WowzaGoCoder.SceneKitReel.xcodeproj
This is Apple's SceneKitReel sample application, modified to support
broadcasting the SceneKit app's frame buffer to Wowza servers. Most of the
code in this app is Apple's; look for "#pragma mark - WowzaGoCoder" to
see the WowzaGoCoder related code. This example makes use of the WZBroadcast
and WZBroadcastComponent (and related) classes/protocols, which provide
lower-level access to the various components involved in a Wowza broadcast.

4. WowzaGoCoderMP4PlayerSample.swift.xcodeproj
This is a Swift application that demonstrates how to broadcast the frames
from a local MP4 file using the WZBroadcast and WZBroadcastComponent
(and related) classes/protocols, which provide lower-level access to the
various components involved in a Wowza broadcast.


In all sample apps, the relevant GoCoder-related sources are the first
files (.h and .m) or file (.swift) listed in the Project Navigator.

To facilitate working with the various sample apps, an Xcode workspace named
'AllSampleApps.xcworkspace' is included. This workspace includes the projects
listed above.
