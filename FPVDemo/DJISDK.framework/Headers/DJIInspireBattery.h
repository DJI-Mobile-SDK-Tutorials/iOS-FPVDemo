//
//  DJIInspireBattery.h
//  DJISDK
//
//  Copyright (c) 2015 DJI. All rights reserved.
//

#import <DJISDK/DJIBattery.h>

/**
 *   DJIBatteryState is used for record the history status of battery. The dji's battery could keep the state in latest 30 days.
 */
@interface DJIBatteryState : NSObject
/**
 *  Over current in discharge.
 */
@property(nonatomic, readonly) BOOL dischargeOverCurrent;
/**
 *  Over heat in discharge.
 */
@property(nonatomic, readonly) BOOL dischargeOverHeat;
/**
 *  Low temperature in discharge.
 */
@property(nonatomic, readonly) BOOL dischargeLowTemperature;
/**
 *  Short cut in discharge.
 */
@property(nonatomic, readonly) BOOL dischargeShortCut;
/**
 *  Self-discharge in storage.
 */
@property(nonatomic, readonly) BOOL selfDischarge;
/**
 *  Cell Under voltage.
 */
@property(nonatomic, readonly) uint8_t underVoltageCellIndex;
/**
 *  Damaged cell index.
 */
@property(nonatomic, readonly) uint8_t damagedCellIndex;

@end

/**
 *  Description The battery cell
 */
@interface DJIBatteryCell : NSObject

/**
 *  The voltage battery cell.
 */
@property(nonatomic, readonly) uint16_t voltage;

-(id) initWithVolgate:(uint16_t)voltage;

@end

/**
 *  Description DJIInspireBattery is one type of dji battery. the designed volume is 4500mAh, 22.2V
 */
@interface DJIInspireBattery : DJIBattery

/**
 *  Get battery's history state, The dji's battery could keep the state in latest 30 days. Object in 'history' parameters is kind of class DJIBatteryState.
 *
 *  @param result Remote execute result.
 */
-(void) getBatteryHistoryState:(void(^)(NSArray* history, DJIError* error))result;

/**
 *  Get battery's current state.
 *
 *  @param result Remote execute result.
 */
-(void) getBatteryCurrentState:(void (^)(DJIBatteryState* state, DJIError *))result;

/**
 *  Set battery's self-discharge day.
 *
 *  @param day    Day for self-discharge
 *  @param result Remote execute result
 */
-(void) setBatterySelfDischargeDay:(uint8_t)day withResult:(DJIExecuteResultBlock)result;

/**
 *  Get battery self-discharge day
 *
 *  @param result Remote execute result
 */
-(void) getBatterySelfDischargeDayWithResult:(void(^)(uint8_t day, DJIError* error))result;

/**
 *  Get battery's cell voltage. The object in 'cellArray' is kind of class DJIBatteryCell
 *
 *  @param block Remote execute result
 */
-(void) getCellVoltagesWithResult:(void(^)(NSArray* cellArray, DJIError* error))block;

@end
