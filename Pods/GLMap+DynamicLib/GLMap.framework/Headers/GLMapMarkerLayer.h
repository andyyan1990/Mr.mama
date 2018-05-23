//
//  GLMapMarkerLayer.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 1/15/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import "GLMapDrawObject.h"

@class GLMapView;
@class GLMapMarkerStyleCollection;
@class GLMapVectorObjectArray;
@class GLMapVectorCascadeStyle;

/**
 `GLMapMarkerLayer` displays big number of markers with given style. It supports marker clustering.
 */
@interface GLMapMarkerLayer : GLMapDrawObject

NS_ASSUME_NONNULL_BEGIN

/// Plain -init is disabled
-(instancetype _Nonnull) init __attribute__((unavailable("Please use inits with data.")));

/**
 Initializes `GLMapMarkerLayer` with given markers and `style`
 
 @param markers Array of marker objects. Usually you set objects with data, that you need to display on map.
 @param styleCollection A style collection object used to display markers.
 @param clusteringRadius Radius of clustering in points (0 will disable clustering)
 @param drawOrder draw order of layer
 
 @return A new marker layer
 */
-(instancetype) initWithMarkers:(NSArray<id> *)markers
                      andStyles:(GLMapMarkerStyleCollection *)styleCollection
              clusteringRadius:(double)clusteringRadius
                      drawOrder:(int)drawOrder;

/**
 Initializes `GLMapMarkerLayer` with given array of vector objects and `style`.
 When using this constructor location of markers is filled from vector object. It can be modified in style together with style and text.

 @param vectorObjects Array of vector objects.
 @param styleCollection A style collection object used to display markers.
 @param clusteringRadius Radius of clustering in points (0 will disable clustering)
 @param drawOrder draw order of layer
 @return A new marker layer
 */
-(instancetype) initWithVectorObjects:(GLMapVectorObjectArray *)vectorObjects
                            andStyles:(GLMapMarkerStyleCollection *)styleCollection
              clusteringRadius:(double)clusteringRadius
                            drawOrder:(int)drawOrder;

/**
 Initializes `GLMapMarkerLayer` with given markers and `style`
 
 @param objects Array of vector objects.
 @param cascadeStyle A cascade style used to select image for marker.
 @param styleCollection A style collection object used to display markers.
 @param clusteringRadius Radius of clustering in points (0 will disable clustering)
 @param drawOrder draw order of layer
 @return A new marker layer
 */
-(instancetype) initWithVectorObjects:(GLMapVectorObjectArray *)objects
                         cascadeStyle:(GLMapVectorCascadeStyle *)cascadeStyle
                      styleCollection:(GLMapMarkerStyleCollection *)styleCollection
                     clusteringRadius:(double)clusteringRadius
                            drawOrder:(int)drawOrder;

/**
 Copies markers from other layer
 @param layer other layer with markers to copy
 */
-(void) copyMarkersFromLayer:(GLMapMarkerLayer *)layer;

/**
 Adds or removes markers on layer
 
 @param markersToAdd markers that should be added
 @param markersToRemove markers that should be removed (compared by pointer)
 @param markersToReload markers that should be reloaded
 @param animated if `YES` modification will be animated
 @param completion block that will be called when modification is finished
 */
-(void) add:(NSArray<id> *_Nullable)markersToAdd remove:(NSArray<id> *_Nullable)markersToRemove reload:(NSArray<id> *_Nullable)markersToReload animated:(BOOL)animated completion:(dispatch_block_t _Nullable)completion;

/**
 Changes style of marker layer
 
 @param style New style
 @param completion block that will be called when modification is finished
 */
-(void) changeStyle:(GLMapMarkerStyleCollection *)style completion:(dispatch_block_t _Nullable)completion;

/**
 Searchs nearest object or cluster of objects at given mapView
 
 @param mapView map view where layer is displayed
 @param point point where object(s) will be searched
 @param distanceInPoints maximum hit distance in points
 
 @return An array of objects that meets search criteria
 */
-(NSArray<id> * _Nullable) objectsAtMapView:(GLMapView *)mapView nearPoint:(GLMapPoint)point distance:(double)distanceInPoints;

/**
 Animation duraration
 */
@property (assign) double animationDuration;

NS_ASSUME_NONNULL_END

@end
