//
//  DJIShootPhotoStep.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <DJISDK/DJISDK.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  This class represents a step related to photo-shooting for a custom mission. By creating an object of this class and adding it into a custom mission, user can shoot photo during the custom mission execution.
 */
@interface DJIShootPhotoStep : DJIMissionStep

/**
 *  Initialized step for single shoot photo.
 *
 *  @return Instance of DJIShootPhotoStep.
 */
- (instancetype _Nullable)initWithSingleShootPhoto;

/**
 *  Initialized step for continous shoot photo.
 *
 *  @param count    Photo count.
 *  @param interval Time interval in second between two shooting action.
 *
 *  @return Instance of DJIShootPhotoStep.
 */
- (instancetype _Nullable)initWithPhotoCount:(int)count timeInterval:(double)interval;

@end

NS_ASSUME_NONNULL_END