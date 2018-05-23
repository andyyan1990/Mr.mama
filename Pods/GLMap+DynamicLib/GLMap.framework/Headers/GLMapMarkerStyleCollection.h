//
//  GLMapMarkerStyleCollection.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 1/19/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GLMapVectorStyle.h"

/// `GLMapMarkerData` is type used to reference an internal object.
typedef void* GLMapMarkerData;

#ifdef __cplusplus
extern "C" {
#endif
/**
 Changes map marker style
 
 @param data Marker object to be changed
 @param style Style identifier
 */
void GLMapMarkerSetStyle(GLMapMarkerData _Nonnull data, unsigned int style);

/**
 Sets text for map marker.
 
 @param data Marker object to be changed
 @param text Text for marker object
 @param offset offset on screen in points
 @param style Text style
 */
void GLMapMarkerSetText(GLMapMarkerData _Nonnull data, NSString *_Nonnull text, CGPoint offset, GLMapVectorStyle * _Nonnull style);

#ifdef __cplusplus
}
#endif
    
/**
 `GLMapMarkerDataFillBlock` is called for each marker to fill needed data
 
 @see `GLMapMarkerSetStyle`
 @see `GLMapMarkerSetText`
 */
typedef void (^GLMapMarkerDataFillBlock)(NSObject * _Nonnull marker, GLMapMarkerData _Nonnull data);

/**
 `GLMapMarkerPositionBlock` is called for each marker to get location of marker
 */
typedef GLMapPoint (^GLMapMarkerLocationBlock)(NSObject * _Nonnull marker);

/**
 `GLMapMarkerUnionBlock` called when marker layer needs style for union of `count` markers
 */
typedef void (^GLMapMarkerUnionFillBlock)(uint32_t count, GLMapMarkerData _Nonnull data);

/**
 `GLMapMarkerStyleCollection` class holds collection of styles, used to draw marker layer.
 */
@interface GLMapMarkerStyleCollection : NSObject

/// @return Returns new instance of `GLMapMarkerStyleCollection`
-(instancetype _Nonnull) init;

/**
 Adds block used to fill data for markers. `GLMapMarkerDataFillBlock` is called for each marker, is should set marker information into `GLMapMarkerData` variable using `GLMapMarkerSetLocation`, `GLMapMarkerSetStyle`, `GLMapMarkerSetText` functions.
 
 @param block A marker data fill block
 */
-(void) setMarkerDataFillBlock:(GLMapMarkerDataFillBlock _Nullable)block;

/**
 Sets block used to get location for markers.
 @param block A marker location block
 */
-(void) setMarkerLocationBlock:(GLMapMarkerLocationBlock _Nullable)block;

/**
 `GLMapMarkerUnionBlock` called when marker layer needs style for union of `count` markers. It should return number
 
 @param block A cluster data fill block
 */
-(void) setMarkerUnionFillBlock:(GLMapMarkerUnionFillBlock _Nullable)block;

/**
 Adds new style to collection that have only one image

 @param image Image that will have default offset (center of image)
 @retun index in collection for this style
 */
-(uint32_t) addStyleWithImage:(UIImage *_Nonnull)image;

/**
 Adds new style to collection that have several images

 @param images array of images that will have default offset (center of image)
 @retun index in collection for this style
 */
-(uint32_t) addStyleWithImages:(NSArray<UIImage *> *_Nonnull)images;

/**
 Adds new style to collection that have images with offsets
 
 @param images array of images
 @param offsets offsets of images
 @retun index in collection for this style
 */
-(uint32_t) addStyleWithImages:(NSArray<UIImage *> *_Nonnull)images andOffsets:(NSArray<NSValue *> *_Nullable)offsets;

/**
 * Set name for style that can be used from mapcss
 * @param styleIndex index of style
 * @param name name to set
 */
-(void) setStyleName:(NSString *_Nonnull)name forStyleIndex:(uint32_t)styleIndex;

@end
