# iOS-FPVDemo

## Introduction

This FPVDemo is design for you to gain a basic understanding of the DJI Mobile SDK. It will implement the FPV view and two basic camera functionalities: **Take Photo** and **Record Video**.

## Requirements

 - iOS 9.0+
 - Xcode 8.0+
 - DJI iOS SDK 3.4

## SDK Installation with CocoaPods

Since this project has been integrated with [DJI iOS SDK CocoaPods](https://cocoapods.org/pods/DJI-SDK-iOS) now, please check the following steps to install **DJISDK.framework** using CocoaPods after you downloading this project:

**1.** Install CocoaPods

Open Terminal and change to the download project's directory, enter the following command to install it:

~~~
sudo gem install cocoapods
~~~

The process may take a long time, please wait. For further installation instructions, please check [this guides](https://guides.cocoapods.org/using/getting-started.html#getting-started).

**2.** Install Git Large File Storage (Git LFS)

Since the **DJISDK.framework** file exceeds the 100 MB limitation of Github file upload, you need to use [Git Large File Storage](https://git-lfs.github.com) to download the SDK file. Enter the following command to install it:

~~~
brew install git-lfs
git lfs install
~~~

Be sure to **restart** your terminal after installing the Git LFS.

**3.** Install SDK with CocoaPods in the Project

Run the following command in the project's directory:

~~~
pod install
~~~

If you install it successfully, you may get the messages similar to the followings:

~~~
Analyzing dependencies
Downloading dependencies
Installing DJI-SDK-iOS (3.4)
Generating Pods project
Integrating client project

[!] Please close any current Xcode sessions and use `FPVDemo.xcworkspace` for this project from now on.
Pod installation complete! There is 1 dependency from the Podfile and 1 total pod
installed.
~~~

## Tutorial

For this demo's tutorial: **Creating a Camera Application**, please refer to <https://developer.dji.com/mobile-sdk/documentation/ios-tutorials/index.html>.

## Feedback

We’d love to hear your feedback for this demo and tutorial.

Please use **Github Issue** or **email** [oliver.ou@dji.com](oliver.ou@dji.com) when you meet any problems of using this demo. At a minimum please let us know:

* Which DJI Product you are using?
* Which iOS Device and iOS version you are using?
* A short description of your problem includes debug logs or screenshots.
* Any bugs or typos you come across.

## License

iOS-FPVDemo is available under the MIT license. Please see the LICENSE file for more info.
