//
//  NSValue+GLMap.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 1/28/17.
//  Copyright © 2017 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GLMapViewTypes.h"

/// Extensions to store `GLMapPoint` and `GLMapGeoPoint` inside `NSValue`
@interface NSValue (GLMapViewAdditions)

/**
 Creates `NSValue` object with `GLMapPoint`.
 
 @param pt Point
 @return Returns new `NSValue` object with `GLMapPoint` inside.
 */
+(NSValue *) valueWithGLMapPoint:(GLMapPoint) pt;
/**
 Creates `NSValue` object with `GLMapGeoPoint`.
 
 @param pt Point
 @return Returns new `NSValue` object with `GLMapGeoPoint` inside.
 */
+(NSValue *) valueWithGLMapGeoPoint:(GLMapGeoPoint) pt;

/**
 Returns `GLMapPoint` object from `NSValue`. 
 
 It automatically converts value from `GLMapGeoPoint` to `GLMapPoint` if needed.
 If there is no `GLMapPoint` or `GLMapGeoPoint` inside (NaN, NaN) is returned.
 
 @return Returns `GLMapPoint` object from `NSValue`.
 */
-(GLMapPoint) glMapPoint;

/**
 Returns `GLMapGeoPoint` object from `NSValue`.
 
 It automatically converts value from `GLMapPoint` to `GLMapGeoPoint` if needed.
 If there is no `GLMapGeoPoint` or `GLMapPoint` inside (NaN, NaN) is returned.
 
 @return Returns `GLMapGeoPoint` object from `NSValue`.
 */
-(GLMapGeoPoint) glMapGeoPoint;
@end
