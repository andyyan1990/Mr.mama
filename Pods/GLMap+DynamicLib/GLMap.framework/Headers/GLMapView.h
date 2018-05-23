//
//  GLMapView.h
//  GLMapView
//
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>

#import "GLMapViewTypes.h"
#import "GLMapMarkerLayer.h"
#import "GLMapVectorImageFactory.h"

@class GLMapAnimation;
@class GLMapDrawable;
@class GLMapTrack;
@class GLMapTrackData;
@class GLMapImageGroup;
@class GLMapMarkerLayer;
@class GLMapVectorObject;
@class GLMapVectorStyle;
@class GLMapVectorCascadeStyle;
@class GLMapRasterTileSource;
@class GLMapMarkerStyleCollection;
@class GLSearchCategories;
@class GLMapLocaleSettings;

/// :nodoc:
extern NSString * _Nonnull GLMapViewErrorDomain;

NS_ASSUME_NONNULL_BEGIN

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     Converts `NSData` objects into `GLMapResources`.
     
     @param data Data object to convert.
     @return Created resource object.
     */
    GLMapResource GLMapResourceWithData(NSData *data);
    
#ifdef __cplusplus
}
#endif

/// `GLMapTapGestureBlock` called, when user tapped or long tapped on map. Add custom tap handling logic inside this block.
typedef void (^GLMapTapGestureBlock)(CGPoint pt);

/// `GLMapBBoxChangedBlock` called every time, when map is moved or zoom is changed.
typedef void (^GLMapBBoxChangedBlock)(GLMapBBox bbox);

/// `GLMapAnimationBlock` called every frame wile `YES` returned. If `NO` returned - animation block will be removed
typedef void (^GLMapAnimationBlock)(GLMapAnimation *animation);

/// `GLMapVisibleTilesChangedBlock` called when set of visible tiles changed
typedef void (^GLMapVisibleTilesChangedBlock)(NSSet *visibleTiles);

/// `GLMapTileErrorBlock` called when there is no data for tile, or map can't download tile. It allows to use custom 'no data' tiles.
typedef UIImage *_Nullable (^GLMapTileErrorBlock)(GLMapTilePos pos, NSError *error);

/// `GLMapCaptureFrameBlock` is called when frame is captured.
typedef void (^GLMapCaptureFrameBlock)(UIImage *_Nullable);

/// `GLMapScaleRulerTextFormatterBlock` is used to change scale ruler format or localize unit name.
typedef NSString *_Nullable(^GLMapScaleRulerTextFormatterBlock)(int value, GLUnits units);

/**
 `GLMapView` is a custom `UIView` that renders and presents vector map.
 */
@interface GLMapView : UIView<CLLocationManagerDelegate>

/**
 Captures frame from `GLMapView` to `UIImage`
 
 @return Current state of the `GLMapView`
 */
-(nullable UIImage *) captureFrame;

/**
 Captures frame from `GLMapView` to `UIImage` when all load operations will finish.
 
 @param block Block callback is called when screenshot is ready.
 
 @see `-captureFrame`
 @see `offscreen`
 */
-(void) captureFrameWhenFinish:(GLMapCaptureFrameBlock) block;

/**
 Allows to render offscreen frames
 
 By default offscreen = `NO`. And GLMapView stop render if there is no superview. But in case you need to capture frames from standalone GLMapView, you need to set offscreen = YES;
 */
@property BOOL offscreen;

/**
 Rendering frame interval. By default frameInterval is 2 (30 fps)
 */
@property NSInteger frameInterval;

/**
 State of tile in center of screen
 
 @see `centerTileStateChangedBlock`
 */
@property (readonly) GLMapTileState centerTileState;

#pragma mark - User Interface

/// Gestures handled by `GLMapView`
typedef NS_OPTIONS(NSUInteger, GLMapViewGestures)
{
    /// Gesture recognition disabled
    GLMapViewGesture_None     = 0,
    /// Pan gesture
    GLMapViewGesture_Pan      = 1,
    /// Zoom gesture
    GLMapViewGesture_Zoom     = 1 << 1,
    /// Rotate gesture
    GLMapViewGesture_Rotate   = 1 << 2,
    /// Zoom in gesture
    GLMapViewGesture_ZoomIn   = 1 << 3,
    /// Zoom out gesture
    GLMapViewGesture_ZoomOut  = 1 << 4,
    /// Tap gesture
    GLMapViewGesture_Tap      = 1 << 5,
    /// Long press gesture
    GLMapViewGesture_LongPress= 1 << 6,
    /// Recognise all gestures
    GLMapViewGesture_All =
        GLMapViewGesture_Pan|
        GLMapViewGesture_Zoom|
        GLMapViewGesture_Rotate|
        GLMapViewGesture_ZoomIn|
        GLMapViewGesture_ZoomOut|
        GLMapViewGesture_Tap|
        GLMapViewGesture_LongPress
};

/**
 Sets mask that defines enabled gestures.
 
 Use `tapGestureBlock` and `longPressGestureBlock` to add your tap and long press handlers.
 */
@property (nonatomic, assign) GLMapViewGestures gestureMask;

/// `tapGestureBlock` called for each tap gesture recognized.
@property (copy) GLMapTapGestureBlock _Nullable tapGestureBlock;

/// `longPressGestureBlock` called for each long press gesture recognized.
@property (copy) GLMapTapGestureBlock _Nullable longPressGestureBlock;

/// `bboxChangedBlock` called when map is moved or zoomed.
@property (copy) GLMapBBoxChangedBlock _Nullable bboxChangedBlock;

/// `mapDidMoveBlock` called when animation or deceleration ends.
@property (copy) GLMapBBoxChangedBlock _Nullable mapDidMoveBlock;

/// `visibleTilesChangedBlock` called when set of visible tiles is changed.
@property (copy) GLMapVisibleTilesChangedBlock _Nullable visibleTilesChangedBlock;

/**
 `tileErrorBlock` called when empty tile without data becomes visible.
 
 This method is used to show custom data inside empty tiles.
 */
@property (copy) GLMapTileErrorBlock _Nullable tileErrorBlock;

/// `centerTileStateChangedBlock` called when centerTileState is changed
@property (copy) dispatch_block_t centerTileStateChangedBlock;

/// Bounding box of the map
@property (readonly) GLMapBBox bbox;

/**
 Sets position of map attribution.
 
 @param position Position to set.
 */
-(void) setAttributionPosition:(GLMapPlacement)position;

/**
 Sets text at the bottom of ruler.
 
 It's used to display map center coordinates or any other useful information
 */
-(void) setScaleRulerBottomText:(NSString *_Nullable)text;

/**
 Sets style of the scale ruler.
 
     //Sets scale ruler position to the bottom center part of screen. And width to half of screen width
     [_mapView setScaleRulerUnits:[AppSettings settings].units placement:GLMapPlacement_BottomLeft paddings:CGPointMake(5, 5) maxWidth:300];
 
 @param unitSystem Unit system used by scale ruler
 @param placement placement of text
 @param paddings paddings of scale ruler
 @param maxWidth maxWidth of scale hit in points
 */
-(void) setScaleRulerStyle:(GLUnitSystem)unitSystem placement:(GLMapPlacement)placement paddings:(CGPoint)paddings maxWidth:(float)maxWidth;

/**
 Sets block that called when ruler value is updated. Block allows to translate units and use custom digit format inside ruler.
 
 @param block New text formatter block
 */
-(void) setScaleRulerTextFormatterBlock:(GLMapScaleRulerTextFormatterBlock)block;

#pragma mark - User Location
/**
 In order to show user location using GLMapView you should create your own CLLocationManager and set GLMapView as CLLocationManager's delegate. Or you could forward `-locationManager:didUpdateLocations:` calls from your location manager delegate to the GLMapView.
 */

/// Last location received by `GLMapView`
@property (readonly) CLLocation *_Nullable lastLocation;

/// Defines if user location is displayed or not. If `YES`, user location is displayed.
@property (assign, nonatomic) BOOL showUserLocation;

/**
 Sets alternative user location images.
 
 @param locationImage new user location image. If `nil`, old image is left unchanged.
 @param movementImage new user movement image. If `nil`, old image is left unchanged.
 */
- (void)setUserLocationImage:(UIImage *_Nullable)locationImage movementImage:(UIImage *_Nullable)movementImage;

#pragma mark - Style

/**
 Loads map style.
 
 By default GLMapView tries to load `[[NSBundle mainBundle] pathForResource:@"DefaultStyle" ofType:@"bundle"];`
 
 @param styleBundle Bundle object with Style.mapcss and images
 @return Returns `YES` if style is loaded without errors
 */
-(BOOL) loadStyleFromBundle:(NSBundle *)styleBundle;

/**
 Allows to modify way framework loads map resources. 
 
 Usually it looks into map style bundle contents, but for some cases it's useful to have all resoureces merged together into one file or even generated programmatically
 
 @param resourceBlock Block that returns style data
 @return YES if style is loaded without errors
 */
-(BOOL) loadStyleWithBlock:(GLMapResourceBlock)resourceBlock;

/**
 Sets scale of font loaded frrom styleBundle. By default fontScale is 1.0
 */
-(void) setFontScale:(float) fontScale;

/**
 Custom raster tile sources. By default mapView have no raster layers.
 */
@property (copy) NSArray<GLMapRasterTileSource *> * rasterTileSources;

/**
 Returns set of names of map options defined in map style.
 
 For example in selector
 
     node|z17-[_optOn=Bar][amenity=bar],
 
 part `[_optOn=Bar]` requires option `Bar` enabled. By default all options is enabled. But you can manage enabled options via `setEnabledStyleOptions:`
 @see `setEnabledStyleOptions:`
 */
- (NSSet<NSString *> *_Nullable) getStyleOptions;

/**
 Sets list of enabled style options
 
 @param opts Set of enabled options
 */
- (void) setEnabledStyleOptions:(NSSet<NSString *> *)opts;

/**
 Forces reloading of all tiles
 */
-(void) reloadTiles;

/**
 Removes all tiles. Useful to reduce memory usage in background mode
 */
-(void) removeAllTiles;

/**
 Starts animation
 @param animation Animation to start.
 */
-(void) startAnimation:(GLMapAnimation *)animation;

#pragma mark - Configuring the Map Position

/**
 Origin point of the map coordinate system (X, Y). 

 Changing the values in this property between 0 and 1 in relative coordinates describes the point of GLMapView which is considered as a center point for `mapCenter` and `setMapCenter:animated:`.
 
 @see `mapCenter`, `setMapCenter:`
 */
@property (assign) CGPoint mapOrigin;

/**
 Coordinates of the origin point of the map.
 @see `mapOrigin`
 */
@property (assign) GLMapPoint mapCenter;

/**
 Coordinates of the origin point of the map.
 @see `mapOrigin`
 */
@property (assign) GLMapGeoPoint mapGeoCenter;

/**
 Current zoom of the map view.
 */
@property (assign) double mapZoom;

/**
 Current zoom level of the map view.
 */
@property (assign) double mapZoomLevel;

/** 
 Maximum possible value of `mapZoom`. Map won't zoom closer.
 */
@property (assign) double maxZoom;

/**
 Map rotation angle form 0° to 360°.
 */
@property (assign) double mapAngle;

/**
 Starts animation described in block.
 
 @param animations Block with animations. You could set animation params using block param.
 */
- (GLMapAnimation *)animate:(GLMapAnimationBlock)animations;

/**
 Calculates map zoom to fit bbox in view with given size.
 
 @warning If bbox size is 0, returns +inf.
 */
-(double) mapZoomForBBox:(GLMapBBox)bbox viewSize:(CGSize)size;

/**
 Calculates map zoom to fit current view.
 
 @warning If bbox size is 0, returns +inf.
 */
-(double)mapZoomForBBox:(GLMapBBox)bbox;

#pragma mark - Converting map coordinates

/**
 Converts a point on the screen to an internal map coordinate.
 
 @param displayPoint The point you want to convert.
 @return The internal map coordinate of the specified point.
 */
-(GLMapPoint) makeMapPointFromDisplayPoint:(CGPoint)displayPoint;

/**
 Converts a distance between two points on the screen to an internal map coordinate at current map zoom.
 
 @param displayDelta The delta you want to convert.
 @return The delta in internal map coordinates.
 */
-(GLMapPoint) makeMapPointFromDisplayDelta:(CGPoint)displayDelta;

/**
 Converts a distance between two points on the screen to an internal map coordinate.
 
 @param displayDelta The delta you want to convert.
 @param mapZoom Zoom of map
 @return The delta in internal map coordinates.
 */
-(GLMapPoint) makeMapPointFromDisplayDelta:(CGPoint)displayDelta andMapZoom:(double)mapZoom;

/**
 Converts a geo point to the point on the screen.
 
 @param geoPoint The geo point you want to convert.
 @return Coresponding point on the screen.
 */
-(CGPoint) makeDisplayPointFromGeoPoint:(GLMapGeoPoint)geoPoint;

/**
 Converts a point on the screen to the geo point.
 
 @param displayPoint Point on screen you want to convert.
 @return Coresponding geo point.
 */
-(GLMapGeoPoint) makeGeoPointFromDisplayPoint:(CGPoint)displayPoint;

/**
 Converts an internal map coordinate to the point on the screen.
 
 @param mapPoint The map point you want to convert.
 @return Coresponding point on the screen.
 */
-(CGPoint) makeDisplayPointFromMapPoint:(GLMapPoint)mapPoint;

/**
 Converts geo coordinates to the internal point.
 
 @param geoPoint Geo point you want to convert.
 @return Corresponding point in map coordinates.
 */
+(GLMapPoint) makeMapPointFromGeoPoint:(GLMapGeoPoint)geoPoint;

/**
 Converts an internal point to geo coordinates.
 
 @param mapPoint Point in map coordinates.
 @return Corresponding point in geo coordinates.
 */
+(GLMapGeoPoint) makeGeoPointFromMapPoint:(GLMapPoint)mapPoint;

/**
 Converts distance in meters to pixels on the screen
 
 @param meters Distance in meters
 @return Distance in pixels
 */
-(double) makePixelsFromMeters:(double)meters;

/**
 Converts distance in pixels on the screen to meters
 
 @param pixels Distance in pixels
 @return Distance in meters
 */
-(double) makeMetersFromPixels:(double)pixels;

/**
 Converts distance in meters to map coordinates
 
 @param meters Distance in meters
 @return Distance in map coordinates
 */
-(double) makeInternalFromMeters:(double)meters;

/**
 Converts distance in map coordinates to meters
 
 @param internal Distance in map coordinates
 @return Distance in meters
 */
-(double) makeMetersFromInternal:(double)internal;

/**
 Converts distance in pixels to map coordinates
 
 @param pixels Distance in pixels
 @return Distance in map coordinates
 */
-(double) makeInternalFromPixels:(double)pixels;

/**
 Converts distance in map coordinates to pixels
 
 @param internal Distance in map coordinates
 @return Distance in pixels
 */
-(double) makePixelsFromInternal:(double)internal;

#pragma mark - Styles

/**
 Adds style for map.
 
 @param style Style to be added
 */
-(void) addStyle:(GLMapVectorCascadeStyle *)style;

/**
 Removes style from map.
 
 @param style Style to be removed
 */
-(void) removeStyle:(GLMapVectorCascadeStyle *)style;

#pragma mark - Vector Objects

/**
 Returns object near some point on map
 
 @param point Point on map
 @param maxDistance Distance in points
 @param categories Possible categories
 @return Vector object on map
 */
-(GLMapVectorObject *_Nullable) mapObjectNearPoint:(GLMapPoint)point maxDistance:(double)maxDistance categories:(GLSearchCategories *)categories;

/**
 Adds the `GLMapDrawObject` to the map view.
 
 @param drawObject object to add
 */
-(void) add:(GLMapDrawObject *)drawObject;

/**
 Removes previsously added `GLMapMarkerLayer` from the map view.
 
 @param drawObject object to be removed.
 */
-(void) remove:(GLMapDrawObject *)drawObject;

/**
 Removes all previsously added tracks from the map view.
 */
-(void) removeAllTracks;

/**
 Map locale settings
 
 Set of supported locales is returned by `[GLMapLocaleSettings supportedLocales]`
 
 E.g. to set map languages priority to English, Deutsch, native
 
     [_mapView setLocaleSettings:[[GLMapLocaleSettings alloc] initWithLocalesOrder:@[@"en", @"de", @"native"]]];
     // Then reload tiles to apply new locale settings
     [_mapView reloadTiles];
 
 Default value is supported languages from `[NSLocale preferredLanguages]`
 */
@property (strong) GLMapLocaleSettings *localeSettings;


@end

NS_ASSUME_NONNULL_END
