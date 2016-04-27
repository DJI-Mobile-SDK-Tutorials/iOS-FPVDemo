# Creating a Camera Application

<!-- toc -->

*If you come across any mistakes or bugs in this tutorial, please let us know using a Github issue, a post on the DJI forum, or commenting in the Gitbook. Please feel free to send us Github pull request and help us fix any issues. However, all pull requests related to document must follow the [document style](https://github.com/dji-sdk/Mobile-SDK-Tutorial/issues/19)*

---

This tutorial is designed for you to gain a basic understanding of the DJI Mobile SDK. It will implement the FPV view and two basic camera functionalities: **Take Photo** and **Record video**.

   You can download the entire project for this tutorial from this **Github Page**.
   
   We use Phantom 3 Professional as an example to make this demo.
   
## Downloading the SDK

You can download the latest iOS SDK from here: <https://developer.dji.com/mobile-sdk/downloads/>

Minimum Requirement: iOS 8.0 or above

## Importing the SDK

**1**. Create a new project in Xcode, choose **Single View Application** template for your project and press "Next", then enter "FPVDemo" in the **Product Name** field and keep the other default settings.

 Once the project is created, let's navigate to the "FPVDemo" folder of the project and create a new folder named "Frameworks". Next copy the **DJISDK.framework**, which you just download from DJI Developer website to this folder.
 
  ![copyFramework](./Images/copyFramework.png)
  
 Moreover, let's come back to the Xcode project navigator and right click on the "FPVDemo" and select "Add Files to "FPVDemo"..." to add the "Frameworks" folder to the Xcode Project.  
 
  ![addFrameworksFolder](./Images/addFrameworksFolder.png)
  
 Furthermore, let's select the "FPVDemo" target and open the "General" tab. In the "Embedded Binaries" section, press "+" to add the "DJISDK.framework" as shown below:
 
  ![sdkFramework](./Images/sdkFramework.png)

**2**. In order to enable your app to connect to the MFI remote controller, you must add "Supported external accessory protocols" items in the info.plist file, let's modify it by adding the following content:

  ![MFI](./Images/MFIProtocol.png)
   
**3**. Since in iOS 9, App Transport Security has blocked a cleartext HTTP (http://) resource load since it is insecure. You must add **App Transport Security Settings** items in the info.plist file as shown below too:

   ![appTransportSecurity](./Images/appTransportSecurity.png)

## Implementing the First Person View

### Importing the VideoPreviewer

 **1**. We use the **FFMPEG** decoding library (found at http://ffmpeg.org) to do software video decoding here. For the hardware video decoding, we provide a **DJIH264Decoder** decoding library. You can find them in the **VideoPreviewer** folder, which you can download it from [DJI iOS SDK Github Repository](https://github.com/dji-sdk/Mobile-SDK-iOS/tree/master/Sample%20Code/VideoPreviewer). Download and copy the entire **VideoPreviewer** folder to your Xcode project's "Frameworkds" folder and then add the "VideoPreviewer.xcodeproj" to the "Frameworks" folder in Xcode project navigator, as shown below:
  
 ![projectNavigator](./Images/projectNavigator.png)
 
> Note: Please Make sure the **VideoPreviewer** folder and **DJISDK.framework** are in the same **Frameworks** folder like this:
> 
> ![frameworksFolderStruct](./Images/frameworksFolderStruct.png)
 
 **2**. Next, let's select the "FPVDemo" target and open the "General" tab. In the "Embedded Binaries" section, press "+" button to add the "VideoPreviewer.framework" as shown below:
 
  ![addFrameworks](./Images/addFrameworks.png)
  ![addFrameworksResult](./Images/addFrameworksResult.png)
  
### Working on the DJICameraViewController
   
 **1**. Now let's delete the "ViewController.h" and "ViewController.m" files created by Xcode by default. Create a new ViewController named "DJICameraViewController". Open Main.storyboard, add a new View Controller and set **DJICameraViewController** as the **Class** for it:
  
  ![rootController](./Images/rootController.png)
  
Add a UIView inside the View Controller. Then, add two UIButtons and one UISegmentedControl at the bottom of the View Controller as shown below:
  
  ![Storyboard](./Images/Storyboard.png)
  
  Go to DJICameraViewController.m file and import the **DJISDK** and **VideoPreviewer** header files. Next implement two delegate protocols and set the IBOutlets and IBActions for the UI we just create in Main.storyboard as shown below:
  
~~~objc
#import <DJISDK/DJISDK.h>
#import <VideoPreviewer/VideoPreviewer.h>

@interface DJICameraViewController ()<DJICameraDelegate, DJISDKManagerDelegate, DJIBaseProductDelegate>

@property (weak, nonatomic) IBOutlet UIButton *recordBtn;
@property (weak, nonatomic) IBOutlet UISegmentedControl *changeWorkModeSegmentControl;
@property (weak, nonatomic) IBOutlet UIView *fpvPreviewView;

- (IBAction)captureAction:(id)sender;
- (IBAction)recordAction:(id)sender;
- (IBAction)changeWorkModeAction:(id)sender;
~~~

 **2**. In the `viewDidAppear` method, set the `fpvPreviewView` instance variable as the view of **VideoPreviewer** to show the Video Stream and reset it to nil in the `viewWillDisappear` method:
 
~~~objc
- (void)viewDidAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [[VideoPreviewer instance] setView:self.fpvPreviewView];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [[VideoPreviewer instance] setView:nil];   
}
~~~

 **3**. Moreover, implement the "DJISDKManagerDelegate" and "DJIBaseProductDelegate" delegate methods to fetch DJICamera object and set its delegate to "self" as shown below:
  
~~~objc

- (DJICamera*) fetchCamera {

    if (![DJISDKManager product]) {
        return nil;
    }
    
    if ([[DJISDKManager product] isKindOfClass:[DJIAircraft class]]) {
        return ((DJIAircraft*)[DJISDKManager product]).camera;
    }else if ([[DJISDKManager product] isKindOfClass:[DJIHandheld class]]){
        return ((DJIHandheld *)[DJISDKManager product]).camera;
    }

    return nil;
}

#pragma mark DJISDKManagerDelegate Method

-(void) sdkManagerProductDidChangeFrom:(DJIBaseProduct* _Nullable) oldProduct to:(DJIBaseProduct* _Nullable) newProduct
{
    if (newProduct) {
        [newProduct setDelegate:self];
        DJICamera* camera = [self fetchCamera];
        if (camera != nil) {
            camera.delegate = self;
        }
    }
}

#pragma mark - DJIBaseProductDelegate Method

-(void) componentWithKey:(NSString *)key changedFrom:(DJIBaseComponent *)oldComponent to:(DJIBaseComponent *)newComponent {
    
    if ([key isEqualToString:DJICameraComponentKey] && newComponent != nil) {
        __weak DJICamera* camera = [self fetchCamera];
        if (camera) {
            [camera setDelegate:self];
        }
    }
}
  
~~~
  
  Firstly, we create the `- (DJICamera*) fetchCamera` method to fetch the updated DJICamera object. Before we get return the DJICamera object, we need to check if the product object of DJISDKManager is kind of **DJIAircraft** of **DJIHandheld** class. Since the camera component of the aircraft or handheld device may be changed or disconnected, we need to fetch the camera object everytime we want to use it to ensure we get the correct camera object. 
  
  Next, we invoke the `sdkManagerProductDidChangeFrom:to:` delegate method to get the `newProduct` and set the DJIICamera object's delegate here. This delegate method will invoke when the product connection status changes.
  
  Moverover, let's invoke the `componentWithKey:changedFrom:to:` delegate method to fetch the camera object and set its delegate too. Since the camera component of the aircraft may change to another type, we should invoke this delegate method to check the component changes too.
        
 **4**. Lastly, let's implement the "DJICameraDelegate" method, as shown below:
  
~~~objc

#pragma mark - DJICameraDelegate Method

-(void)camera:(DJICamera *)camera didReceiveVideoData:(uint8_t *)videoBuffer length:(size_t)size
{
    [[VideoPreviewer instance] push:videoBuffer length:(int)size];
}

-(void) camera:(DJICamera*)camera didUpdateSystemState:(DJICameraSystemState*)systemState
{
}

~~~

 Here, we use the `-(void)camera:(DJICamera *)camera didReceiveVideoData:(uint8_t *)videoBuffer length:(size_t)size` method to get the live H264 video feed data and send them to the **VideoPreviewer** to decode.
   
  Moreover, the `-(void) camera:(DJICamera*)camera didUpdateSystemState:(DJICameraSystemState*)systemState` method is used to get the camera state from the camera on your aircraft. It will be invoked frequently, so you can update your user interface or camera settings accordingly here.
 
## Activating the SDK

Now, let's create a new method `registerApp` and invoke it in the `viewDidAppear` method as shown below:

~~~objc
- (void)registerApp
{
    NSString *appKey = @"Enter Your App Key Here";
    [DJISDKManager registerApp:appKey withDelegate:self];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [[VideoPreviewer instance] setView:self.fpvPreviewView];
    [self registerApp];
}
~~~

>**Note**: For the **App Key**, you may need to obtain it from the DJI Developer website >**(<http://developer.dji.com/en/user/apps>)**.  If you are not familiar with the App Key, please check [Creating an DJI App Tutorial](http://developer.dji.com/mobile-sdk/get-started/Register-Download).

>The **App Key** we generate for you is associated with the Xcode project's **Bundle Identifier**, so you will not be able to use the same App Key in a different Xcode project. Each project must be submitted individually and will receive a unique App Key.

If you register the app failed, you can check the **error** variable in the following `sdkManagerDidRegisterAppWithError` delegate method to figure out the problem. For more details, please check the DJISDKRegistrationError in "NSError+DJISDK.h" file. Now let's implement the following two methods:

~~~objc

- (void)showAlertViewWithTitle:(NSString *)title withMessage:(NSString *)message
{
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:title message:message preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil];
    [alert addAction:okAction];
    [self presentViewController:alert animated:YES completion:nil];
}

- (void)sdkManagerDidRegisterAppWithError:(NSError *)error
{
    NSString* message = @"Register App Successed!";
    if (error) {
        message = @"Register App Failed! Please enter your App Key and check the network.";
    }else
    {
        NSLog(@"registerAppSuccess");
    
        [DJISDKManager startConnectionToProduct];
        [[VideoPreviewer instance] start];
    }
    
    [self showAlertViewWithTitle:@"Register App" withMessage:message];
}
~~~

In the code above, firstly, we create an `showAlertViewWithTitle:withMessage` method to show alert view. Then in the `sdkManagerDidRegisterAppWithError:` method, we invoke the `startConnectionToProduct` method of DJISDKManager to start connecting to the aircraft and call the `start` method of **VideoPreviewer**'s instance object to start the video decode when we register the app successfully. Finally, we create a UIAlertView to inform the register App state to the user.

**3**. Build and Run the project in Xcode. If everything is OK, you will see a "Register App Success!" alert once the application loads. 
  
  ![Screenshot](./Images/Screenshot.png)

## Connecting to the Aircraft or Handheld Device

After you finish the steps above, you can now connect your mobile device to your DJI Aircraft to use the application, like checking the FPV View. Here are the guidelines:

* In order to connect to a DJI Phantom 4, Inspire 1, Phantom 3 Professional, etc:

  **1**. First, turn on your remote controller.
  
  **2**. Then, turn on the power of the DJI aircraft.
  
  **3**. Connect your iOS device to the remote controller using the lightning cable.
  
  **4**. Run the application and wait for a few seconds, you will be able to view the live video stream from your aircraft's camera based on what we've finished of the application so far!
  
* In order to connect to Phantom 3 Standard, Phantom 3 4K, or OSMO:

  **1**. First, turn on your remote controller or OSMO.
   
  **2**. Then, turn on the power of the DJI aircraft. (If you are using Phantom 3 Standard or Phantom 3 4K)
  
  **3**. Search for the WiFi of the aircraft's remote controller or OSMO and connect your iOS device to it.
  
  **4**. Run the application and wait for a few seconds, you will be able to view the live video stream from your aircraft or OSMO's camera based on what we've finished of the application so far!
  
## Enjoying the First Person View

If you can see the live video stream in the application, congratulations! Let's move forward.

  ![fpv](./Images/fpv.jpg)

## Implementing the Capture function

Let's implement the `captureAction` IBAction method as shown below:

~~~objc
- (IBAction)captureAction:(id)sender {
    
    __weak DJICameraViewController *weakSelf = self;
    __weak DJICamera* camera = [self fetchCamera];
    if (camera) {
        [camera startShootPhoto:DJICameraShootPhotoModeSingle withCompletion:^(NSError * _Nullable error) {
            if (error) {
                [weakSelf showAlertViewWithTitle:@"Take Photo Error" withMessage:error.description];
            }
        }];
    }
}
~~~

In the code above, we invoke the following method of DJICamera to shoot photo.
   
`- (void)startShootPhoto:(DJICameraShootPhotoMode)shootMode withCompletion:(DJICompletionBlock)block;`

  Here we set the "shootMode" to **DJICameraShootPhotoModeSingle**. You can check the shoot photo result from the "DJICompletionBlock".
  
  Build and run your project and then try the shoot photo function. If the screen flash after your press the **Capture** button, your capture fuction should work now.
  
## Implementing the Record function
  
### 1. Switching Camera Mode

   Before we implementing the record function, we need to switch the camera work mode firstly.
   
   Let's check the DJICameraMode enum in **DJICameraSettingsDef.h** file.
   
~~~objc
/**
 *  Camera work modes.
 */
typedef NS_ENUM (NSUInteger, DJICameraMode){
    /**
     *  Capture mode. In this mode, the user can capture pictures.
     */
    DJICameraModeShootPhoto = 0x00,
    /**
     *  Record mode. In this mode, the user can record videos.
     */
    DJICameraModeRecordVideo = 0x01,
    /**
     *  Playback mode. In this mode, the user can preview photos and videos, and
     *  they can delete files.
     *
     *  Not supported by OSMO, Phantom 3 Standard.
     */
    DJICameraModePlayback = 0x02,
    /**
     *  In this mode, user can download media to Mobile Device.
     *
     *  Supported by Phantom 3 Professional, Phantom 3 Advanced, Phantom 3 Standard, X3.
     */
    DJICameraModeMediaDownload = 0x03,
    
    /**
     *  The camera work mode is unknown.
     */
    DJICameraModeUnknown = 0xFF
};
~~~

   You can see from above that there are 5 types of **DJICameraMode**. Here we use the first two types.
      
   Remember we create a UISegment Control in the storyboard? We can update the state of the segmented control when switching between **DJICameraModeShootPhoto** and **DJICameraModeRecordVideo** using the previous delegate method like this:
   
~~~objc
-(void) camera:(DJICamera*)camera didUpdateSystemState:(DJICameraSystemState*)systemState
{        
    //Update UISegmented Control's state
    if (systemState.mode == DJICameraModeShootPhoto) {
        [self.changeWorkModeSegmentControl setSelectedSegmentIndex:0];
    }else if (systemState.mode == DJICameraModeRecordVideo){
        [self.changeWorkModeSegmentControl setSelectedSegmentIndex:1];
    }
}

~~~

 Now we can implement the `changeWorkModeAction` IBAction method as follows:
 
~~~objc

- (IBAction)changeWorkModeAction:(id)sender {
    
    __weak DJICameraViewController *weakSelf = self;
    UISegmentedControl *segmentControl = (UISegmentedControl *)sender;
    
    __weak DJICamera* camera = [self fetchCamera];
    
    if (camera) {
        if (segmentControl.selectedSegmentIndex == 0) { //Take photo
            [camera setCameraMode:DJICameraModeShootPhoto withCompletion:^(NSError * _Nullable error) {
                if (error) {
                    [weakSelf showAlertViewWithTitle:@"Set DJICameraModeShootPhoto Failed" withMessage:error.description];
                }
            }];
            
        }else if (segmentControl.selectedSegmentIndex == 1){ //Record video
            [camera setCameraMode:DJICameraModeRecordVideo withCompletion:^(NSError * _Nullable error) {
                if (error) {
                    [weakSelf showAlertViewWithTitle:@"Set DJICameraModeRecordVideo Failed" withMessage:error.description];
                }
                
            }];
            
        }
    }
    
}

~~~

 In the code above, we invoke the 
 `- (void)setCameraMode:(DJICameraMode)mode withCompletion:(DJICompletionBlock)block;` method of DJICamera to change the camera mode.  Here we add two UIAlertViews to show warnings when the user set DJICameraMode failed.
 
### 2. Working on the Record Action

  Firstly, let's go to Main.storyboard and drag a UILabel on top of the screen, set up the Autolayout constraints for it and create an IBOutlet named `currentRecordTimeLabel` in the **DJICameraViewController.m** file.
  
  Then add a BOOL variable `isRecording` in the class extension part of **DJICameraViewController**. Be sure to hide the `currentRecordTimeLabel` in the `viewDidLoad` method.

~~~objc
- (void)viewDidLoad {
    [super viewDidLoad];
    [self.currentRecordTimeLabel setHidden:YES];
}
~~~  
  
We can update the bool value for `isRecording` and `currentRecordTimeLabel`'s text value in the following delegate method:
   
~~~objc

-(void) camera:(DJICamera*)camera didUpdateSystemState:(DJICameraSystemState*)systemState
{
    self.isRecording = systemState.isRecording;
    
    [self.currentRecordTimeLabel setHidden:!self.isRecording];
    [self.currentRecordTimeLabel setText:[self formattingSeconds:systemState.currentVideoRecordingTimeInSeconds]];
    
    if (self.isRecording) {
        [self.recordBtn setTitle:@"Stop Record" forState:UIControlStateNormal];
    }else
    {
        [self.recordBtn setTitle:@"Start Record" forState:UIControlStateNormal];
    }
    
    //Update UISegmented Control's state
    if (systemState.mode == DJICameraModeShootPhoto) {
        [self.changeWorkModeSegmentControl setSelectedSegmentIndex:0];
    }else if (systemState.mode == DJICameraModeRecordVideo){
        [self.changeWorkModeSegmentControl setSelectedSegmentIndex:1];
    }   
}
   
~~~
   
   Because the text value of `currentRecordingTime` is counted in seconds, so we need to convert it to "mm:ss" format like this:
   
~~~objc
- (NSString *)formattingSeconds:(int)seconds
{
    NSDate *date = [NSDate dateWithTimeIntervalSince1970:seconds];
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"mm:ss"];
    [formatter setTimeZone:[NSTimeZone timeZoneForSecondsFromGMT:0]];
    
    NSString *formattedTimeString = [formatter stringFromDate:date];
    return formattedTimeString;
}
~~~
   
   Next, add the following codes to the `recordAction` IBAction method as follows:
   
~~~objc
- (IBAction)recordAction:(id)sender {
    
    __weak DJICameraViewController *weakSelf = self;
    __weak DJICamera* camera = [self fetchCamera];
    if (camera) {
    
        if (self.isRecording) {
            [camera stopRecordVideoWithCompletion:^(NSError * _Nullable error) {
                if (error) {
                    [weakSelf showAlertViewWithTitle:@"Stop Record Video Error" withMessage:error.description];
                }
            }];
            
        }else
        {
            [camera startRecordVideoWithCompletion:^(NSError * _Nullable error) {
                if (error) {
                    [weakSelf showAlertViewWithTitle:@"Start Record Video Error" withMessage:error.description];
                }
            }];
        }
    }
}
~~~

  In the code above, we implement the `startRecordVideoWithCompletion` and `stopRecordVideoWithCompletion` methods of the **DJICamera** class based on the `isRecording` property value. And show an alertView when an error occurs.
   
  Now, let's build and run the project and check the functions. You can try to play with the **Record** and **Switch Camera WorkMode** functions, if everything goes well, you should see the screenshot like this:
   
  ![Screenshot](./Images/record_screenshot.jpg)
   
  Congratulations! Your Aerial FPV iOS app is complete, you can now use this app to control the camera of your Phantom 3 Professional. 

## Summary
   
   In this tutorial, you’ve learned how to use DJI Mobile SDK to show the FPV View from the aircraft's camera and control the camera of DJI's Aircraft to shoot photo and record video. These are the most basic and common features in a typical drone mobile app: **Capture** and **Record**. However, if you want to create a drone app which is more fancy, you still have a long way to go. More advanced features should be implemented, including previewing the photo and video in the SD Card, showing the OSD data of the aircraft and so on. Hope you enjoy this tutorial, and stay tuned for our next one!
   
