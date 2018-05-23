//
//  GLMapVectorStyle.h
//  GLMap
//
//  Created by Evgen Bodunov on 3/31/14.
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GLMapView;

/** `GLMapVectorStyle` is used to define appearance of text inside `GLMapMarkerLayer` or `GLMapView`.
 
 Style is used to render a map, which is stored inside DefaultStyle.bundle/Style.mapcss file. Detailed MapCSS specification is located at: http://www.mapcss.org
 */
@interface GLMapVectorStyle : NSObject

/// Plain -init is disabled
-(instancetype _Nonnull) init __attribute__((unavailable("Please use `[GLMapVectorStyle createStyle:]` and `[GLMapVectorStyle createStyle:error:]`")));

NS_ASSUME_NONNULL_BEGIN

/**
 Creates style object.
 
 `GLMapVectorStyle *style = [GLMapVectorStyle createStyle(@"{font-size:12;}"];`
 
 @param style NSString with style rule in MapCSS format
 @return New `GLMapVectorStyle` object
 */
+(nullable instancetype) createStyle:(NSString *_Nonnull)style;

/**
 Creates style object.
 
 @param style NSString with style rule in MapCSS format
 @param error Error is filled if object cannot be created
 
 @return New `GLMapVectorStyle` object
 */
+(nullable instancetype) createStyle:(NSString *_Nonnull)style error:(NSError **)error;

NS_ASSUME_NONNULL_END

@end
