# Wowza GoCoder SDK for iOS Sample Apps
This repository contains sample applications that demonstrate the capabilities of the [Wowza GoCoder™ SDK for iOS](https://www.wowza.com/products/gocoder/sdk) and is provided for developer educational purposes. To build your own application, you must use the GoCoder SDK.

## Prerequisites
- GoCoder SDK for iOS v1.5.1.0949

     **NOTE:** The GoCoder SDK binaries necessary to build the sample apps aren't provided here. To get free trial of the SDK, complete the [GoCoder SDK trial sign-up form](https://www.wowza.com/products/gocoder/sdk/trial) to receive a link where you can download the SDK along with a free trial license key.

- iOS SDK 8.01 or later
- Xcode 7 or later

## Sample Apps
| App  | Description  |
| ------------- | ------------- |
| WowzaGoCoderSDKSampleApp.xcodeproj  | This Objective-C application demonstrates how to use the GoCoder SDK to capture and broadcast video using internal cameras on a device. Use the Settings screen in the app to modify various video, audio, capture, and broadcast settings.  |
| WowzaGoCoderSDKSampleApp.swift.xcodeproj  | This Swift application demonstrates how to use the SDK. It shares the same functionality as the Objective-C application (WowzaGoCoderSDKSampleApp.xcodeproj) described above.  |
| WowzaGoCoder.SceneKitReel.xcodeproj  | This SceneKitReel sample application from Apple is modified to support broadcasting the SceneKit app's frame buffer to Wowza media servers. Most of the code in this app is Apple's. To see the Wowza GoCoder-related code, look for the following comment:<pre>#pragma mark - WowzaGoCoder</pre>This example uses the **WZBroadcast**, **WZBroadcastComponent**, and related classes and protocols, which provide lower-level access to the various components involved in a Wowza streaming broadcast.  |
| WowzaGoCoderMP4PlayerSample.swift.xcodeproj  | This Swift application demonstrates how to broadcast the frames from a local MP4 file using the **WZBroadcast**, **WZBroadcastComponent**, and related classes and protocols, which provide lower-level access to the various components involved in a Wowza streaming broadcast.  |

In all of the sample apps, the relevant GoCoder-related sources are the first files (.h and .m) or file (.swift) listed in the Project Navigator.

To facilitate working with the various sample apps, an Xcode workspace called **AllSampleApps.xcworkspace** is included. This workspace includes the projects listed above.

## More Resources
- [Wowza GoCoder SDK Technical Articles](https://www.wowza.com/docs/wowza-gocoder-sdk)
- [Wowza GoCoder SDK for iOS Reference Docs](https://www.wowza.com/resources/gocodersdk/docs/1.0/api-reference-ios/)
- [Wowza GoCoder SDK for iOS Release Notes](https://www.wowza.com/docs/wowza-gocoder-sdk-release-notes-for-ios)
- [Wowza GoCoder SDK Community Forum](https://www.wowza.com/community/spaces/36/wowza-gocoder-sdk.html)

Wowza Media Systems™ provides developers with a platform to create streaming applications and solutions. See [Wowza Developer Tools](https://www.wowza.com/resources/developers) to learn more about our APIs and SDK.

## Contact
[Wowza Media Systems, LLC](https://www.wowza.com/contact)

## License
This code is distributed under the [BSD 3-Clause License](https://github.com/WowzaMediaSystems/gocoder-sdk-samples-ios/blob/master/LICENSE.txt).

![alt tag](http://wowzalogs.com/stats/githubimage.php?plugin=gocoder-sdk-samples-ios)
