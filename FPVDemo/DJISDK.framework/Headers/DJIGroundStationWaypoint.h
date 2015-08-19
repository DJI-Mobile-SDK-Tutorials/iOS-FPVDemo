//
//  DJIGroundStationWaypoint.h
//  DJISDK
//
//  Copyright (c) 2015 DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <DJISDK/DJIFoundation.h>

/**
 *  Maximum action count for each waypoint. current supported max actions is 16.
 */
DJI_API_EXTERN const int DJIMaxActionCount;
/**
 *  Maximum repeat times for waypoint action. current supported max repeat times is 16.
 */
DJI_API_EXTERN const int DJIMaxActionRepeatTimes;

/**
 *  Turn mode of drone when adjust the aircraft's heading.
 */
typedef NS_ENUM(NSUInteger, DJIWaypointTurnMode){
    /**
     *  Clockwise
     */
    WaypointTurnModeClockwise,
    /**
     *  Anti clockwise
     */
    WaypointTurnModeAntiClockwise,
};

/**
 *  Waypoint Action Type
 */
typedef NS_ENUM(NSUInteger, DJIWaypointActionType){
    /**
     *  No action. Stay at point
     */
    WaypointActionNone,
    /**
     *  Start take photo
     */
    WaypointActionStartTakePhoto,
    /**
     *  Start record
     */
    WaypointActionStartRecord,
    /**
     *  Stop record
     */
    WaypointActionStopRecord,
    /**
     *  Rotate aircraft's yaw [0, 360], 0 : North
     */
    WaypointActionRotateAircraft,
    /**
     *  Rotate gimbal's yaw
     */
    WaypointActionRotateGimbalYaw,
    /**
     *  Rotate gimbal's pitch
     */
    WaypointActionRotateGimbalPitch,
};

@interface DJIWaypointAction : NSObject

/**
 *  Type of action
 */
@property(nonatomic, assign) DJIWaypointActionType actionType;

/**
 *  Param of action
 */
@property(nonatomic, assign) int16_t actionParam;

-(id) initWithActionType:(DJIWaypointActionType)type param:(int16_t)param;

@end

@interface DJIGroundStationWaypoint : NSObject

/**
 *  Coordinate of waypoint (degree)
 */
@property(nonatomic) CLLocationCoordinate2D coordinate;

/**
 *  Altitude of waypoint (meters)
 */
@property(nonatomic) float altitude;

/**
 *  Heading of waypoint. range in [-180, 180], 0 is the true north
 */
@property(nonatomic) float heading;

/**
 *  Horizontal velocity at waypoint (m/s), [0, 7]
 */
@property(nonatomic) float horizontalVelocity;

/**
 *  Staying time at waypoint (second)
 */
@property(nonatomic) int stayTime;

/**
 *  Max time for reach to the target waypoint. if time out then the aircraft go to the next waypoint directly
 */
@property(nonatomic) int maxReachTime;

/**
 *  How the aircraft turn to the target direction.
 */
@property(nonatomic) DJIWaypointTurnMode turnMode;

/**
 *  Waypoint's action list. The action will perform one by one while the aircraft reached to this waypoint.
 */
@property(nonatomic, readonly) NSArray* waypointActions;

/**
 *  Repeat times for action. All actions completed is one times. Defaule is one times.
 */
@property(nonatomic, assign) NSUInteger actionRepeatTimes;

-(id) initWithCoordinate:(CLLocationCoordinate2D)coordinate;

/**
 *  Add action for waypoint. action count should not be large than DJIMaxActionCount
 *
 *  @param action Action for waypoint
 *
 *  @return Result of adding waypoint action. if waypoint action count is over DJIMaxActionCount or waypoint has existed in the action list, return NO
 */
-(BOOL) addWaypointAction:(DJIWaypointAction*)action;

/**
 *  Remove an action from waypoint
 *
 *  @param action Action to be removed
 *
 *  @return Result of remove waypoint action
 */
-(BOOL) removeWaypointAction:(DJIWaypointAction*)action;
@end
