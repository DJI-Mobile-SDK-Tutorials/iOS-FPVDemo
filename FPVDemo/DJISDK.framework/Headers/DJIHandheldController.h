//
//  DJIHandheldController.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIBaseComponent.h>

@class DJIWiFiLink;

NS_ASSUME_NONNULL_BEGIN

//-----------------------------------------------------------------
#pragma mark DJIHandheldWiFiFrequency Type
//-----------------------------------------------------------------
/**
 *  Handheld WiFi Frequency Type.
 */
typedef NS_ENUM (uint8_t, DJIHandheldWiFiFrequencyType){
    /**
     *  The Handheld WiFi frequency is 2.4G
     */
    DJIHandheldWiFiFrequency2Dot4G,
    /**
     *  The Handheld WiFi frequency is 5.8G
     */
    DJIHandheldWiFiFrequency5Dot8G,

};

/**
 *  Handheld Power Mode
 */
typedef NS_ENUM (uint8_t, DJIHandheldPowerMode){
    /**
     *  The Handheld Power Mode is awake.
     *  For OSMO, when it is in this mode, all the components in DJIHandheld are accessible.
     */
    DJIHandheldPowerModeAwake,
    /**
     *  The Handheld Power Mode is sleeping. The handheld controller keeps the WiFi connection
     *  to the Mobile device alive but most other components are off. The power consumption is low
     *  in this mode.
     *  For OSMO, when it is in this mode, only the DJIHandheldController, DJIAirLink and DJIBattery
     *  are accessible.
     */
    DJIHandheldPowerModeSleeping,
    /**
     *  The Handheld Power Mode is power-off. Once this mode is set the delegate will receive this mode until the handheld device is
     *  shut down completely.
     */
    DJIHandheldPowerModePowerOff,
    /**
     *  The Handheld Power Mode in unkown.
     */
    DJIHandheldPowerModeUnknown = 0xFF
};

@class DJIHandheldController;

/*********************************************************************************/
#pragma mark - DJIHandheldControllerDelegate
/*********************************************************************************/

/**
 *
 *  This protocol provides a delegate method to receive the updated power mode of the handheld controller.
 *
 */
@protocol DJIHandheldControllerDelegate <NSObject>

@optional

/**
 *  Tells the delegate that a handheld controller's power mode is updated.
 *
 *  @param controller   the handheld controller that updates the power mode
 *  @param powerMode    handheld controller's current power mode
 *
 */
- (void)handheldController:(DJIHandheldController *)controller didUpdatePowerMode:(DJIHandheldPowerMode)powerMode;

@end

/*********************************************************************************/
#pragma mark - DJIHandheldController
/*********************************************************************************/
/**
 *
 *  This class contains interfaces to control a handheld device. You can make the handheld device enter sleep mode, awake from sleep mode or shut it down.
 */
@interface DJIHandheldController : DJIBaseComponent

/**
 *  Returns the DJIHandheldController delegate
 */
@property(nonatomic, weak) id <DJIHandheldControllerDelegate> delegate;

/**
 *  Set the power mode for handheld.
 *
 *  @param mode     The power mode to set.
 *                  CAUTION: when the mode is DJIHandheldPowerModePowerOff, the handheld device will be shut down and
 *                  the connection will be broken. User then needs to power on the device manually.
 *  @param block    Remote execution result callback block.
 */
- (void)setHandheldPowerMode:(DJIHandheldPowerMode)mode withCompletion:(DJICompletionBlock)block;

@end
NS_ASSUME_NONNULL_END