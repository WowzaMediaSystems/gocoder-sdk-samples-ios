Wowza GoCoder SDK Sample Apps

The *sample-apps* folder contains the following sample projects:

1. All-in-OneSampleApp.objc.xcodeproj
An Objective-C application that demonstrates all of the individual Objective-C sample applications in one application. This app also includes a bitmap overlay sample app.

2. LiveStreamSampleApp.swift.xcodeproj
A Swift application that demonstrates how to use the SDK to capture and broadcast video using the device's internal cameras. The Settings screen in the app allows you to modify various video, audio, capture, and broadcast settings. This app also includes a bitmap overlay feature.

3. MetaDataSampleApp.objc.xcodeproj
An Objective-C application that demonstrates how to use the GoCoder SDK to send a data event (onGetPingTime) to a Wowza Streaming Engine server module that is created and configured to receive the event.

4. PlayerSampleApp.objc.xcodeproj
An Objective-C application that demonstrates how to use the SDK to play a live stream, including an ultra low latency stream from the Wowza Streaming Cloud™ service. This application uses WOWZBroadcast and WOWZPlayer, which decompresses audio and video, and supports HLS fallback when the primary connection fails.

5. PlayerSampleApp.swift.xcodeproj
A Swift application that demonstrates how to use the SDK to play a live stream, including an ultra low latency stream from the Wowza Streaming Cloud™ service. This application uses WOWZBroadcast and WOWZPlayer, which decompresses audio and video, and supports HLS fallback when the primary connection fails.

6. SceneKitReelSampleApp.objc.xcodeproj
An Apple SceneKitReel application modified to support broadcasting the SceneKit app's frame buffer to a Wowza Streaming Engine server. Most of the code is written by Apple; search for "#pragma mark - WowzaGoCoder" to find GoCoder code. This application uses WOWZBroadcast, WOWZBroadcastComponent, and related classes and protocols.

7. StreamMP4SampleApp.swift.xcodeproj
A Swift application that demonstrates how to broadcast the frames from a local MP4 file using WOWZBroadcast, WOWZBroadcastComponent, WOWZPlayer, and related classes and protocols.

In all sample apps, the relevant GoCoder-related sources are the first files (.h and .m) or file (.swift) listed in the Project navigator.

To facilitate working with the various sample apps, an Xcode workspace named 'AllSampleApps.xcworkspace' is included. This workspace includes the projects listed above.
