# Wowza GoCoder SDK for iOS Sample Apps

**Wowza Player, Wowza GoCoder SDK, and the technology powering the Ultra Low Latency (ULL) service in Wowza Streaming Cloud will no longer be available on August 31, 2021. [Learn more](https://info.wowza.com/product-notification-april-2020).**

This repository contains sample applications that demonstrate the capabilities of the [Wowza GoCoder™ SDK for iOS](https://www.wowza.com/products/gocoder/sdk) and is provided for developer educational purposes. To build your own application, you must use the GoCoder SDK.

## Prerequisites
- GoCoder SDK for iOS v1.9.0.1377

>**Notes:** 
> - The GoCoder SDK binaries necessary to build the sample apps aren't provided here. To get the free SDK, complete the [GoCoder SDK sign-up form](https://www.wowza.com/products/gocoder/sdk/license) to receive a link to allow you to download the SDK along with a license key. If you already have a license key, you can download the current SDK release [here](https://www.wowza.com/pricing/installer#gocodersdk-downloads). Be sure to add your ```WowzaGoCoderSDK.framework``` as an Embedded Binary at the bottom of your General project seettings.
> - Be sure to update the bundle identifier in the Xcode project to the one you entered to get your GoCoder SDK license. If you don't have the bundle identifier, you can find it listed as the App ID in the "Your Wowza GoCoder SDK License" email.
> - Be sure to replace the SDKSampleAppLicenseKey value with your license key as needed in the project files. The license key can appear in more than one file in a project. All instances of the license key need to be replaced with your license key.

- iOS SDK 8.01 or later
- Xcode 7 or later
- Access to a [Wowza Streaming Engine](https://www.wowza.com/products/streaming-engine)™ media server or a [Wowza Streaming Cloud](https://www.wowza.com/products/streaming-cloud)™ account. You can request a free 180-day Wowza Streaming Engine developer license by completing the [Wowza Streaming Engine Developer License form](https://www.wowza.com/media-server/developers/license) or sign up for a Wowza Streaming Cloud developer trial by completing the [Wowza Streaming Cloud Developer Free Trial form](https://www.wowza.com/pricing/cloud-developer-free-trial).

## Sample Apps
The sample apps include an all-in-one app, **All-in-OneSampleApp.objc.xcodeproj**, that demonstrates all of the individual sample apps in one app. The individual sample apps demonstrate the features of the GoCoder SDK, including:

- **LiveStreamSampleApp.swift.xcodeproj**, which demonstrates how to use the GoCoder SDK to capture and broadcast video using internal cameras on a device
- **MetaDataSampleApp.objc.xcodeproj**, which uses the GoCoder SDK to inject timed metadata into a live stream
- **PlayerSampleApp.objc.xcodeproj**, which shows how to use the SDK to play a live stream, including an ultra low latency stream from the Wowza Streaming Cloud™ service

In all of the sample apps, the relevant GoCoder-related sources are the first files (.h and .m) or file (.swift) listed in the Project Navigator.

To facilitate working with the various sample apps, an Xcode workspace called **AllSampleApps.xcworkspace** is included. This workspace includes the projects listed above.

## More Resources
- [Wowza GoCoder SDK Technical Articles](https://www.wowza.com/docs/wowza-gocoder-sdk)
- [Wowza GoCoder SDK for iOS Reference Docs](https://www.wowza.com/resources/gocodersdk/docs/api-reference-ios/)
- [Wowza GoCoder SDK for iOS Release Notes](https://www.wowza.com/docs/wowza-gocoder-sdk-release-notes-for-ios)
- [Wowza GoCoder SDK Community Forum](https://www.wowza.com/community/spaces/36/wowza-gocoder-sdk.html)

Wowza Media Systems™ provides developers with a platform to create streaming applications and solutions. See [Wowza Developer Tools](https://www.wowza.com/developer) to learn more about our APIs and SDKs.

## Contact
[Wowza Media Systems, LLC](https://www.wowza.com/contact)

## License
This code is distributed under the [BSD 3-Clause License](/LICENSE.txt).
