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


DISCLAIMER:
This is sample code provided by Wowza Media Systems, LLC.  All sample code is intended to be a reference for the
purpose of educating developers, and is not intended to be used in any production environment.

IN NO EVENT SHALL WOWZA MEDIA SYSTEMS, LLC BE LIABLE TO YOU OR ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL,
OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
EVEN IF WOWZA MEDIA SYSTEMS, LLC HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

WOWZA MEDIA SYSTEMS, LLC SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. ALL CODE PROVIDED HEREUNDER IS PROVIDED "AS IS".
WOWZA MEDIA SYSTEMS, LLC HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
