//
//  GLMapAnimation.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 9/12/17.
//  Copyright © 2017 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "GLMapViewTypes.h"

@class GLMapDrawable;
@class GLMapView;

/**
 * `GLMapAnimation` defines animation of objects parameters that will be executed synchronously.
 */
@interface GLMapAnimation : NSObject

/**
 Initializes GLMapAnimation
 */
- (instancetype)init;

/**
 Transition of animation. Default transition is Ease In - Ease Out
 */
@property (assign) GLMapTransitionFunction transition;

/**
 Duration of animation. Default duration is 0.5 seconds.
 */
@property (assign) double duration;

/**
 Focus point of zoom and rotate animations
 */
@property (assign) GLMapPoint focusPoint;

/**
 If YES flyTo animation will be used if new mapCenter is set and previous flyTo animation is not finished yet
 */
@property (assign) BOOL continueFlyTo;

/**
 * Sets new position of drawable
 * @param drawable drawable to modify
 * @param position new position
 */
- (void)setPosition:(GLMapPoint)position forDrawable:(GLMapDrawable *)drawable;

/**
 * Sets new scale of drawable
 * @param drawable drawable to modify
 * @param scale new scale
 */
- (void)setScale:(double)scale forDrawable:(GLMapDrawable *)drawable;

/**
 * Sets new angle of drawable
 * @param drawable drawable to modify
 * @param angle new angle
 */
- (void)setAngle:(float)angle forDrawable:(GLMapDrawable *)drawable;

/**
 * Sets new offset of drawable
 * @param offset new offset
 * @param drawable drawable to modify
 */
- (void)setOffset:(CGPoint)offset forDrawable:(GLMapDrawable *)drawable;

/**
 Moves to new center with animation optimized for long distances.
 @param point Target location.
 */
- (void)flyToPoint:(GLMapPoint)point;

/**
 Moves to new center with animation optimized for long distances.
 @param geoPoint Target location.
 */
- (void)flyToGeoPoint:(GLMapGeoPoint)geoPoint;

/**
 Defines the scrolling speed at the end of map scrolling movement.

 @param velocity Initial velocity of deceleration
 */
- (void)decelerate:(GLMapPoint) velocity;

/**
 Cancels anmation
 @param setFinalValues if YES aimatied values will be set to it's final values.
 */
- (void)cancel:(BOOL)setFinalValues;

@end
