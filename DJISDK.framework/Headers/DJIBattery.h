//
//  DJIBattery.h
//  DJISDK
//
//  Copyright (c) 2015 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIObject.h>

@interface DJIBattery : DJIObject

/**
 *  The battery's design volume (mAh)
 */
@property(nonatomic) NSInteger designedVolume;

/**
 *  The battery's full charge volume (mAh)
 */
@property(nonatomic) NSInteger fullChargeVolume;

/**
 *  The current electricity volume of battery (mAh)
 */
@property(nonatomic) NSInteger currentElectricity;

/**
 *  The current voltage of battery (mV)
 */
@property(nonatomic) NSInteger currentVoltage;

/**
 *  The current current of battery (mA), The negative value is indicate that the battery is in discharge
 */
@property(nonatomic) NSInteger currentCurrent;

/**
 *  Remain life percentage of battery.
 */
@property(nonatomic) NSInteger remainLifePercent;

/**
 *  Remain power percentage of battery.
 */
@property(nonatomic) NSInteger remainPowerPercent;

/**
 *  The temperature of battery between -128 to 127 (Centigrade).
 */
@property(nonatomic) NSInteger batteryTemperature;

/**
 *  The total discharge count of battery.
 */
@property(nonatomic) NSInteger dischargeCount;

/**
 *  Update battery's information once, if successed, the property value of battery will be update.
 *
 *  @param block Remote exeucte result
 */
-(void) updateBatteryInfo:(DJIExecuteResultBlock)block;

@end
