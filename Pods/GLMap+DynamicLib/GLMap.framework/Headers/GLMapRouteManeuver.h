//
//  GLMapRouteManeuver.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 3/6/17.
//  Copyright © 2017 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Class that holding data for the route manuver
 */
@interface GLMapRouteManeuver : NSObject

/**
 * Initializes custom maneuver
 * @param type type of maneuver
 * @param streets street names that are consistent along the entire maneuver.
 * @param preInstruction Text suitable for use as a verbal message immediately prior to the maneuver transition.
 * @param transitionInstruction Text suitable for use as a verbal alert in a navigation application.
 * @param postInstruction Text suitable for use as a verbal message immediately after the maneuver transition.
 * @param points points of maneuver
 * @param numberOfPoints number of points
 * @param previousManeuver previous maneuver
 */
-(instancetype) initWithType:(GLManeuverType) type
                        time:(double) time
                     streets:(NSArray *) streets
              preInstruction:(NSString *) preInstruction
       transitionInstruction:(NSString *) transitionInstruction
             postInstruction:(NSString *) postInstruction
                      points:(GLMapPoint *) points
              numberOfPoints:(NSUInteger) numberOfPoints
            previousManeuver:(GLMapRouteManeuver *) previousManeuver;

/**
 * Type of the maneuver see https://github.com/valhalla/valhalla-docs/blob/master/api-reference.md for details
 */
@property(readonly) GLManeuverType type;

/**
 * Start point of the maneuver
 */
@property(readonly) GLMapPoint startPoint;

/**
 * End point of the maneuver
 */
@property(readonly) GLMapPoint endPoint;

/**
 * Number of points in maneuver track.
 */
@property(readonly) NSUInteger countOfPoints;

/**
 * First point equals to startPoint. Last point equals to endPoint
 * @param index index of point to return
 * @return point of maneuver track at givenIndex
 */
-(GLMapPoint) pointAtIndex:(NSUInteger)index;

/**
 * List of street names that are consistent along the entire maneuver.
 */
@property(readonly) NSArray<NSString *> *streetNames;

/**
 * Text suitable for use as a verbal message immediately after the maneuver transition.
 * For example "Continue on U.S. 2 22 for 3.9 miles".
 */
@property(readonly) NSString *verbalPostTransitionInstruction;

/**
 * Text suitable for use as a verbal message immediately prior to the maneuver transition.
 * For example "Turn right onto North Prince Street, U.S. 2 22".
 */
@property(readonly) NSString *verbalPreTransitionInstruction;

/**
 * Text suitable for use as a verbal alert in a navigation application.
 * The transition alert instruction will prepare the user for the forthcoming transition.
 * For example: "Turn right onto North Prince Street".
 */
@property(readonly) NSString *verbalTransitionInstruction;

/**
 * Maneuver length in meters
 */
@property(readonly) double length;

/**
 * Estimated time along the maneuver in seconds.
 */
@property(readonly) double time;

@end
