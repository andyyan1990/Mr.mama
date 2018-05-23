//
//  GLMapVectorImage.h
//  GLMap
//
//  Created by Evgen Bodunov on 12/16/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "GLMapViewTypes.h"

/// `GLMapResourceBlock` is used to load resources from custom place.
typedef GLMapResource (^GLMapResourceBlock)(NSString *_Nonnull name);

/// `GLMapTimestampBlock` is used to get timestamp of resource from custom place. Return NAN if no resurces with such name exit.
typedef double (^GLMapTimestampBlock)(NSString *_Nonnull name);

/**
 `GLMapVectorImageFactory` used to render images from svgpb files. Image factory caches rendered images for future use. 
 
 SVGPB - is preprocessed small and fast SVG files. SVG tags saved into protocol buffer files to maximize parsing speed. Resulting files 5 times smaller and 10x times faster to parse.
 
 To create svgpb files from your svg images please use open source util from https://github.com/molind/svgpb
 */
@interface GLMapVectorImageFactory : NSObject

/// Plain -init is disabled
-(instancetype _Nonnull) init __attribute__((unavailable("It's singleton object. Use `[GLMapVectorImageFactory sharedFactory]`")));

NS_ASSUME_NONNULL_BEGIN

/// Disables disk caching if set to `YES`. Default value is `NO`
@property (assign) BOOL disableCaching;

/// Returns singleton factory object
@property(class, nonatomic, readonly) GLMapVectorImageFactory *_Nonnull sharedFactory;

/// If not nil - GLMapVectorImageFactory will try to get image data using this block. If no data returned it will fallback to direct file reading
@property (strong) GLMapResourceBlock resourceBlock;

/// If timestamp is changed - image will be updated.
@property (strong) GLMapTimestampBlock timestampBlock;

/// Removes all memory cached images
-(void) clearCaches;

/// Delete all cached images files
-(void) deleteCachedFiles;

/**
 Renders `UIImage` from svgpb file.
 
 @param imagePath Path to the svgpb file
 
 @return Returns rendered image
 */
-(nullable UIImage *) imageFromSvgpb:(NSString *)imagePath;
/**
 Renders `UIImage` from svgpb file.
 
 @param imagePath Path to the svgpb file
 @param scale Scale applied during render. 1.0 - original image size.
 
 @return Returns rendered image
 */
-(nullable UIImage *) imageFromSvgpb:(NSString *)imagePath withScale:(double)scale;
/**
 Renders `UIImage` from svgpb file.
 
 @param imagePath Path to the svgpb file
 @param scale Scale applied during render. 1.0 - original image size.
 @param tintColor Tint color applied to the image. Use `0`, when no tint required.
 
 @return Returns rendered image
 */
-(nullable UIImage *) imageFromSvgpb:(NSString *)imagePath withScale:(double)scale andTintColor:(uint32_t)tintColor;
/**
 Renders `UIImage` from svgpb file.
 
 @param imagePath Path to the svgpb file
 @param size Target image size
 @param tintColor Tint color applied to the image. Use `0`, when no tint required.
 
 @return Returns rendered image
 */
-(nullable UIImage *) imageFromSvgpb:(NSString *)imagePath withSize:(CGSize)size andTintColor:(uint32_t)tintColor;

/**
 Renders `UIImage` from svgpb file.
 
 @param imagePath Path to the svgpb file
 @param size Target image size
 @param contentMode Image placement inside the canvas
 @param tintColor Tint color applied to the image. Use `0`, when no tint required.
 
 @return Returns rendered image
 */
-(nullable UIImage *) imageFromSvgpb:(NSString *)imagePath withSize:(CGSize)size contentMode:(UIViewContentMode)contentMode andTintColor:(uint32_t)tintColor;

/**
 Returns cached image for key

 @param key key of cached image
 @param timestamp timestamp to check modifications
 @return caceded image or nil if no image cached for key or timestamp are not equal
 **/
-(UIImage *) cachedImageWithKey:(NSString *)key timestamp:(double) timestamp;

/**
 Caches image

 @param img image to cache
 @param key key of image
 @param timestamp timestamp of image
 **/
-(void) cacheImage:(UIImage *)img withKey:(NSString *)key timestamp:(double) timestamp;

NS_ASSUME_NONNULL_END

@end
