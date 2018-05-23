//
//  GLRasterTileSource.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 11/10/15.
//  Copyright © 2015 Evgen Bodunov. All rights reserved.
//

#import "GLMapViewTypes.h"

/**
 GLMapRasterTileSource is used to setup custom raster tile source.
 */
@interface GLMapRasterTileSource : NSObject

/**
 Initializes tile source. If cachePath==nil no caching will happens.
 */
-(instancetype _Nullable) initWithCachePath:(NSString *_Nullable) cachePath;

/**
 Gets url of tile. Default implementation reuturns nil.
 */
-(NSURL *_Nullable) urlForTilePos:(GLMapTilePos)pos;

/**
 Gets image of tile. Default implementation reuturns nil.
 */
-(UIImage *_Nullable) imageForTilePos:(GLMapTilePos)pos expired:(BOOL *_Nonnull)expired;

/**
 Gets image of tile. Default implementation reuturns nil.
 */
-(void) saveTileData:(NSData * _Nonnull)data forTilePos:(GLMapTilePos)pos;

/**
 Cached tile will be refreshed if it will stay in cache more than given time.
 
 By default tileRefreshTimeInterval = -1. If tileRefreshTimeInterval < 0  no tile refreshing will be triggered.
 */
@property (assign) int64_t tileRefreshTimeInterval;

/**
 Defines valid zooms for tile source. Default is 0xFFFFFFFF.
 */
@property (assign) uint32_t validZoomMask;

/**
 Size of tile in points. Could be used to magnify raster tiles. Default is 256.
 */
@property (assign) uint32_t tileSize;

/**
 Sets attribution text for map source. Default is @"© OpenStreetMap"
 */
@property (strong) NSString *_Nullable attributionText;

/**
 Gets size of cache file
 */
@property (readonly) uint64_t cacheSize;

/**
 Removes all cached data
 */
-(void) dropCache;

@end
