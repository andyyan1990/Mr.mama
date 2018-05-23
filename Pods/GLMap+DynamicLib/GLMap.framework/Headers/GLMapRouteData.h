//
//  GLMapRouteData.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 1/28/17.
//  Copyright © 2017 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "GLMapViewTypes.h"

@class GLMapRouteData;
@class GLMapTrackData;
@class GLMapRouteManeuver;
@class GLMapHeightData;

/**
 * Block that will be called when request is finished
 * @param result instance of GLMapRouteData with information about the route
 * @param error contains error if request is failed
 */
typedef void(^GLMapRouteDataCompletionBlock)(GLMapRouteData * _Nullable result, NSError * _Nullable error);

/**
 * Block that will be called to make gradients for track
 * @param index index of point
 * @return color in this point
 **/
typedef GLMapColor(^GLMapTrackDataColorBlock)(uint32_t index);

/**
 * Class to load route data
 */
@interface GLMapRouteData : NSObject

/**
 * Cancels request that was started
 * @param requestID ID of request to cancel
 */
+(void) cancelRequest:(uint64_t)requestID;

/**
 * Requests route data for given points
 *
 * @param points points of the route
 * @param count number of points
 * @param mode mode of the route
 * @param completionBlock block to be called when results are ready
 * @return requestID that can be used to cancel request
 */
+(int64_t) requestRouteWithPoints:(const GLRoutePoint *_Nonnull)points count:(NSInteger)count mode:(GLMapRouteMode)mode locale:(NSString *_Nonnull)locale units:(GLUnitSystem)units completionBlock:(GLMapRouteDataCompletionBlock _Nullable)completionBlock;

/**
 Finds index where given point must be inserted to array of reference points. It's used, for example, to add waypoint to route.
 
 @param point At input defines point to insert. At output contains point that is located on route.
 @param points Array of reference GLMapPoints
 @param pointsCount Number of points in array
 @return NSNotFound if given point is too far from track.
 */
+(NSUInteger) findInsertionIndex:(GLMapPoint *_Nonnull)point points:(const GLMapPoint *_Nonnull)points pointsCount:(NSInteger)pointsCount;

/**
 Initializes route with custom maneuvers;
 @param maneuvers Custom maneuvers of route
 */
-(instancetype _Nullable) initWithManeuvers:(NSArray<GLMapRouteManeuver *> *_Nonnull)maneuvers language:(NSString *_Nullable)language;

/**
 * Returns track data that can be used to display track of route
 * @param trackColor color of route track
 * @return track data of route
 */
-(GLMapTrackData *_Nullable) trackDataWithColor:(GLMapColor) trackColor;

/**
 * Returns track data that can be used to display track of route
 * @param colorBlock block to generate gradient
 * @return track data of route
 */
-(GLMapTrackData *_Nullable) trackDataWithCallback:(GLMapTrackDataColorBlock _Nonnull) colorBlock;

/**
 * Total length of track
 */
@property (readonly) double length;

/**
 * Estimated duration of the track
 */
@property (readonly) double duration;

/**
 * Finds maneuver that go after given manuver
 * @param maneuver refrence maneuver
 * @return next maneuver of the route
 */
-(GLMapRouteManeuver *_Nullable) getNextManeuver:(GLMapRouteManeuver *_Nonnull)maneuver;

/**
 * Finds maneuver that go before given manuver
 * @param maneuver refrence maneuver
 * @return previous maneuver of the route
 */
-(GLMapRouteManeuver *_Nullable) getPreviousManeuver:(GLMapRouteManeuver *_Nonnull)maneuver;

/**
 * Finds nearest point on route
 * @param point on input contains refrence point. on output contains nearest point
 * @param height height in result point or NAN if heightData is nil
 **/
- (void)findNearestPoint:(GLMapPoint *_Nonnull)point height:(CGFloat *_Nullable)height;

/**
 * All maneuvers of the route
 */
@property (readonly) NSArray<GLMapRouteManeuver *> *_Nullable allManeuvers;

/**
 * Unparsed server response
 */
@property (readonly) NSString *_Nullable serverResponse;

/**
 * Language of instructions in maneuvers
 */
@property (readonly) NSString *_Nullable language;

/**
 * Height data
 */
@property (readonly) GLMapHeightData *_Nullable heightData;

@end
