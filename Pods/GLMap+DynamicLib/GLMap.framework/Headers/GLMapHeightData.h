//
//  GLMapHeightData.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 3/13/18.
//  Copyright © 2018 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GLMapHeightData;
@class GLMapRouteData;
struct GLMapGeoPoint;

/**
 * Block that will be called when request is finished
 * @param result instance of GLMapHeightData with information about height
 * @param error contains error if request is failed
 */
typedef void(^GLMapHeightDataCompletionBlock)(GLMapHeightData * _Nullable result, NSError * _Nullable error);

/**
 * Class to load height data
 **/
@interface GLMapHeightData : NSObject
/**
 * Requests height profile
 * @param points where height is needed
 * @param count number of points
 * @completionBlock block that is called when request is finished of cancelled
 **/
+(int64_t) requestHeightWithPoints:(GLMapGeoPoint *_Nonnull)points count:(NSUInteger)count completionBlock:(GLMapHeightDataCompletionBlock _Nonnull)completionBlock;

/**
 * Requests height for points in route
 * @param routeData route to update with height information
 * @completionBlock block that is called when request is finished of cancelled
 **/
+(int64_t) requestHeightForRoute:(GLMapRouteData *_Nonnull)routeData completionBlock:(GLMapHeightDataCompletionBlock _Nullable)completionBlock;

/**
 * Cancels request that was started
 * @param requestID ID of request to cancel
 */
+(void) cancelRequest:(uint64_t)requestID;

/**
 Minimal value
 **/
@property (readonly) double min;

/**
 Maximum value
 **/
@property (readonly) double max;

/**
 Returns height at given point index
 @param index index of point
 @returns height at given point
 **/
- (double)heightAtIndex:(uint32_t)index;

@end
