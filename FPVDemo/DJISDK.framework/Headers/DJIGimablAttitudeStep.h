/*
 *  DJI iOS Mobile SDK Framework
 *  DJIGimbalAttitudeStep.h
 *
 *  Copyright (c) 2015, DJI.
 *  All rights reserved.
 *
 */

#import <DJISDK/DJISDK.h>

NS_ASSUME_NONNULL_BEGIN

@interface DJIGimablAttitudeStep : DJIMissionStep

/**
 *  Completion time in second for gimbal go to target attitude from current attitude. default is 1s.
 */
@property(nonatomic, assign) double completionTime;

/**
 *  Target gimbal attitude.
 */
@property(nonatomic, readonly) DJIGimbalAttitude targetAttidue;

/**
 *  Initialized instance with gimbal target attitude.
 *
 *  @param attitude  Gimbal target attitude.
 *
 *  @return Instance of DJIGimablAttitudeStep.
 */
-(instancetype _Nullable) initWithAttitude:(DJIGimbalAttitude)attitude;

@end

NS_ASSUME_NONNULL_END
