//
//  GLMapTrack.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 1/28/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import "GLMapDrawObject.h"

@class GLMapTrackData;
@class GLMapView;
@class GLMapVectorStyle;

/**
 `GLMapTrack` is a container class for track objects. Main difference from line - data generalization function is used for tracks to remove data points redundant for current zoom level.
 */
@interface GLMapTrack : GLMapDrawObject

/// Plain -init is disabled
-(instancetype _Nonnull) init __attribute__((unavailable("GLMapTrack should be created with [GLMapTrack initWithDrawOrder:]")));

/**
 Initializes new GLMapTrack
 @param drawOrder order of object
 @param data optional track data
 */
-(instancetype _Nonnull) initWithDrawOrder:(uint32_t)drawOrder andTrackData:(GLMapTrackData *_Nullable)data;

/**
 Sets track width and other properties
 @param style New track style
 */
-(void) setStyle:(GLMapVectorStyle *_Nullable) style;

/**
 Sets track data
 @param data New track data
 */
-(void) setTrackData:(GLMapTrackData *_Nullable)data;

/**
 Finds nearest point of track, to given point. Useful to find nearest point of track whe user tap.
 
 @param point Point on map. If point was found this value will be set to nearest point
 @param distance Max distance from track allowed

 @return YES if point found, otherwise NO.
 */
-(BOOL) findNearestPoint:(GLMapPoint *_Nonnull)point atMapView:(GLMapView *_Nonnull)mapView maxDistance:(CGFloat)distance;

/**
 * Hidden track will prepare data to draw but will not draw anything
 */
 @property (assign) BOOL hidden;

@end
