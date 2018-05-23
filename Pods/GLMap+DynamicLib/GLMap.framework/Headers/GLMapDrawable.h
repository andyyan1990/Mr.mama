//
//  GLMapDrawable.h
//  GLMap
//
//  Created by Evgen Bodunov on 3/16/14.
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import "GLMapDrawObject.h"

@class GLMapVectorStyle;
@class GLMapVectorObject;
@class GLMapVectorCascadeStyle;
@class GLMapView;

/**
 `GLMapDrawable` is a bridge class, to work with GLMap internal representation of object that must be rendered on map. This can be single image, text or vector object.
 `GLMapDrawable` can be rendered as a separate object or injected into tile data.
 Check `GLMapImageGroup` for big groups of images. Or `GLMapMarkerLayer` to display map markers with clustering.
 
 @see `[GLMapView addDrawable:]`
 @see `GLMapMarkerLayer`
 @see `GLMapImageGroup`
 */

/**
 Normal drawable:
 0, GLMapPointMax                   GLMapPointMax, GLMapPointMax
  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
  ┃                                             ┃
  ┃           ╭────────────────────T            ┃
  ┃           │                    │            ┃
  ┃           │←╍╍╍╍╍╍╍╍╍╍╍╍╍P     │            ┃
  ┃           │              ╏     │            ┃
  ┃           │              ╏     │            ┃
  ┃           │              ↓     │            ┃
  ┃           O──────────────┴─────╯            ┃
  ↑                                             ┃
  ┗━→━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 0,0                                GLMapPointMax,0

 P = position (GLMapPoint)
 O = position - offset * scale (pt)
 T = O + size * scale (pt)

 Drawable that uses transform:
 0, GLMapPointMax                   GLMapPointMax, GLMapPointMax
 ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
 ┃                                              ┃
 ┃           ╭────────────────────T             ┃
 ┃           │                    │             ┃
 ┃           │                    │             ┃
 ┃           │                    │             ┃
 ┃           │                    │             ┃
 ┃           │                    │             ┃
 ┃           P────────────────────╯             ┃
 ↑                                              ┃
 ┗━━→━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
 0,0                                GLMapPointMax,0

 P = position (GLMapPoint)
 T = position + size * scale (GLMapPoint)
 **/

@interface GLMapDrawable : GLMapDrawObject

/**
 Initializes empty image that will be displayed with given drawOrder
 @param drawOrder drawOrder of object
 */
-(instancetype _Nonnull) initWithDrawOrder:(int)drawOrder;

/**
 Initializes image that will be injected into map tile data (for example you can set vector object that can be displayed under map elements)
 */
-(instancetype _Nonnull) init;

#pragma mark - Properties

/**
 When set to `YES` image rotates with map. Default value is 'NO'
 */
@property (assign) BOOL rotatesWithMap;

/**
 A Boolean value that determines whether the image is hidden. Default value is 'NO'
 */
@property (assign) BOOL hidden;

/**
 If image contains vector object set this to `YES` if you will use position and scale to transform vector object.
 */
@property (assign) BOOL useTransform;

/**
 A position that sets image position in map internal coordinates
 For vector object adds translation
 Animatable.
 */
@property (assign) GLMapPoint position;

/**
 Image offset from `position` point.
 Can be used for image and text
 When offset is (0,0), bottom left corner of image is displayed at `position`
 Animatable.
 */
@property (assign) CGPoint offset;

/**
 A size of image in pixels
 Can be used for image and text
 */
@property (readonly) CGSize size;

/**
 Scale of object. (by default is 1.0)
 Animatable.
 */
@property (assign) double scale;

/**
 A float variable that defines image angle
 Animatable.
 */
@property (assign) float angle;

#pragma mark - Methods

/**
 Loads image into `GLMapDrawable`
 This variant will not load anything into OpenGL util `GLMapDrawable` will be added to some mapView that will try to render it.
 `UIImage` will be retained by `GLMapDrawable`.
 
 @param image New image to display on map
 @param completion A block called when image is replaced.
 */
-(void) setImage:(UIImage * _Nonnull)image completion:(dispatch_block_t _Nullable)completion;

/**
 Loads image into `GLMapDrawable`
 This variant of function loads OpenGL data into given mapView and does not retain image itself
 You must call this function for every mapView where you will display the image
 
 @param image New image to laod
 @param mapView where to load openGL resources
 @param completion A block called when image is replaced.
 */
-(void) setImage:(UIImage * _Nonnull)image forMapView:(GLMapView *_Nonnull)mapView completion:(dispatch_block_t _Nullable)completion;

/**
 Sets text to draw
 
 @param text New text
 @param style A style object used for text
 @param completion A block called when text is replaced.
 
 @see `GLMapVectorStyle`
 */
-(void) setText:(NSString * _Nonnull)text withStyle:(GLMapVectorStyle * _Nonnull)style completion:(dispatch_block_t _Nullable)completion;

/**
 Sets vector object to draw
 
 @param object object to draw
 @param mapView mapView that contains information for proper work of MapCSS functions
 @param style A style of object
 @param completion A block called when object ready to draw
 
 @see `GLMapVectorStyle`
 */
-(void) setVectorObject:(GLMapVectorObject * _Nonnull)object forMapView:(GLMapView *_Nonnull)mapView withStyle:(GLMapVectorCascadeStyle * _Nonnull)style completion:(dispatch_block_t _Nullable)completion;

/**
 * Tests if point is inside of image
 * @param mapView mapView where images is displayed
 * @param point point to check
 * @param paddings paddings of image
 * @return `true` if point is inside image
 */
-(BOOL) hitTest:(CGPoint)point onMap:(GLMapView * _Nonnull)mapView withPaddings:(UIEdgeInsets)paddings;

@end
