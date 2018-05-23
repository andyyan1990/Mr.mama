//
//  GLMapRouteTracker.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 12/11/17.
//  Copyright © 2017 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GLMapRouteManeuver;
@class GLMapRouteData;

/**
 * Class to get information about maneuvers while user move by route
 */
@interface GLMapRouteTracker : NSObject

/// Plain -init is disabled
-(instancetype _Nonnull) init __attribute__((unavailable("GLMapRouteTracker should be created with [GLMapRouteTracker initWithData:]")));

/**
 * Initializes tracker with data
 */
-(instancetype _Nonnull) initWithData:(GLMapRouteData *_Nonnull)data;

/**
 * Finds next maneuver and update information about it
 * @param location Internal coordinates of current user location
 * @return next maneuver of the route
 */
-(GLMapRouteManeuver *_Nullable) updateLocation:(GLMapGeoPoint)location userBearing:(double)userBearing;

/**
 * Checks if user pass the point
 * @param point Point to check
 * @param maxDistance Max distance from route to point in meters
 * @return YES if user pass the point.
 */
-(BOOL) didPassPoint:(GLMapGeoPoint)point maxDistance:(double)maxDistance;

/**
 * True if user on route
 */
@property (readonly) BOOL onRoute;

/**
 * Location of user at route
 */
@property (readonly) GLMapPoint locationOnRoute;

/**
 * Bearing angle of current route segment
 */
@property (readonly) double bearingAngleOnRoute;

/**
 * Distance to the next manuver in meters
 */
@property (readonly) double distanceToNextManeuver;

/**
 * Distance to the last point of route (in meters)
 */
@property (readonly) double distanceToLastPoint;

/**
 * Distance from location of user to the route
 */
@property (readonly) double distanceFromRoute;

/**
 * First non empty array of streetNames from next maneuver to the end of route
 */
@property (readonly) NSArray<NSString *> *_Nullable nextStreetNames;

/**
 * Distance to the target location in meters
 */
@property (readonly) double remainingDistance;

/**
 * Estimated time to the end of the route
 */
@property (readonly) double remainingDuration;

@end
