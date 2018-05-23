//
//  GLMapManager.h
//  GLMap
//
//  Created by Arkadi Tolkun on 3/11/14.
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import <GLMap/GLMapViewTypes.h>

@class GLMapDownloadTask;
@class GLMapInfo;

/**
 Blocks what has been called on the main thread when task is completed or cancelled
 */
typedef void(^GLMapDownloadCompletionBlock)(GLMapDownloadTask *_Nonnull);

/**
 GLMapListUpdateBlock is used to notify about map list updates.
 
 Map list is stored at server and sometimes it takes some time to fetch latest map list. It is downloaded only if updated. If no changes happened block called almost immidiately.
 */
typedef void(^GLMapListUpdateBlock)(NSArray<GLMapInfo *> *_Nullable result, BOOL mapListUpdated, NSError *_Nullable error);

/**
 GLMapTileDownloadProgressBlock is called when tile downloaded.
 @return if NO returned downloading will be cancelled.
 */
typedef BOOL(^GLMapTileDownloadProgressBlock)(uint64_t tile, NSError *_Nullable error);

/**
 Map manager used to work with list of offline maps
 */
@interface GLMapManager : NSObject

/// Plain -init is disabled
-(instancetype _Nonnull) init __attribute__((unavailable("It's singleton object. Use `[GLMapManager sharedManager]`")));

#pragma mark - Properties

/**
 Allows to download map tiles one by one
 
 By default `tileDownloadingAllowed` = NO. GLMapView checks tile in world offline map first, then in embed and downloaded offline maps, then in downloaded earlier tiles and at last step if tile downloading is allowed it tries to download map tile.
 */
@property (assign) BOOL tileDownloadingAllowed;

/**
 Cached tile will be refreshed if it will stay in cache more than given time. Time interval is measured in seconds.
 
 By default `tileRefreshTimeInterval` = -1. If `tileRefreshTimeInterval` < 0  no tile refreshing will be triggered.
 */
@property (assign) int64_t tileRefreshTimeInterval;

/**
 Number of donwloded maps
 */
@property (readonly) uint64_t downloadedMapsCount;

/**
 An API key used to download vector maps and tiles
 */
@property (strong) NSString *_Nullable apiKey;

#pragma mark - Shared Methods

/**
 Singleton manager object
 */
@property(class, nonatomic, readonly) GLMapManager *_Nonnull sharedManager;

#pragma mark - Methods

/**
 @return Returns array of `GLMapInfo` objects downloaded earlier and cached by `GLMapManager`
 */
-(NSArray<GLMapInfo *> *_Nullable)cachedMapList;

/**
 @return Returns dictionary of all `GLMapInfo` objects (including submaps) downloaded earlier and cached by `GLMapManager`
 */
-(NSDictionary<NSNumber *, GLMapInfo *> *_Nullable)cachedMaps;

/**
 Updates map list
 
 @param block A block called when map list is downloaded
 */
-(void) updateMapListWithCompletionBlock:(GLMapListUpdateBlock _Nullable)block;

/**
 Sorts maps by distance from border.
 @param maps maps to sort
 @param point point to meashure distance
 **/
- (void)sortMaps:(NSMutableArray<GLMapInfo *> *_Nonnull)maps fromPoint:(GLMapPoint)point;

/**
 Starts map download task
 
 It's up to you save download task or not. Active map download task could be received later from -downloadTaskForMap:.
 
 @param map map object
 @param block completion block

 @return A new download task object
 */
-(GLMapDownloadTask *_Nullable) downloadMap:(GLMapInfo *_Nonnull)map withCompletionBlock:(GLMapDownloadCompletionBlock _Nullable)block;

/**
 Used to check if there is a download task for a given map
 
 @param map A map info object
 
 @return Returns `GLMapDownloadTask` previously created for a map
*/
-(GLMapDownloadTask *_Nullable) downloadTaskForMap:(GLMapInfo *_Nonnull)map;

/**
 Map download task is removed from array when map downloading is finished
 
 @return Returns all tasks created by `[GLMapManager downloadMap:withCompletionBlock]`
 */
-(NSArray<GLMapDownloadTask *> *_Nullable) allDownloadTasks;

/**
 Adds vector map. Could be used for maps embed into the app resources.
 
 When map is added, it becomes available for all `GLMapView` objects.

 @param path Path to the vector map
 @return `YES` if file exists and was added to list of custom maps.
 */
-(BOOL) addMap:(NSString *_Nonnull)path;

/**
 Removes vector map from map manager. When removed is safe to delete map file.
 
 @param path Path to the embed map
 */
-(void) removeMap:(NSString *_Nonnull)path;

/**
 Returns downloaded map at given point
 
 @param point Some point in internal format
 @return `GLMapInfo` of downloaded map
 */
-(GLMapInfo *_Nullable) downloadedMapAtPoint:(GLMapPoint) point;

/**
 Returns map at given point
 
 @param point Some point in internal format
 @return `GLMapInfo` of map
 */
-(GLMapInfo *_Nullable) mapAtPoint:(GLMapPoint) point;

/**
 Deletes downloaded map
 
 @param map Map info to delete
 */
-(void) deleteMap:(GLMapInfo *_Nonnull)map;

/**
 Removes GLMap cached objects and closes opened databases
 
 `clearCaches` called automatically on `UIApplicationDidEnterBackgroundNotification`
 */
-(void) clearCaches;

/**
 Saves state for downloading tasks. It allows to resume downloads in case of crash or unexpected behavior
 
 Called automatically when app is minimized
 */
-(void) saveDownloadsState;

/**
 Returns vector tiles that bbox contains or intersects
 @param bbox bbox of area
 @return vector tiles that bbox contains or intersects
 */
-(NSArray<NSNumber*> *_Nonnull) vectorTilesAtBBox:(GLMapBBox) bbox;

/**
 Returns not cached vector tiles that bbox contains or intersects
 @param bbox bbox of area
 @returns not cached vector tiles that bbox contains or intersects
 */
-(NSArray<NSNumber*> *_Nonnull) notCachedVectorTilesAtBBox:(GLMapBBox) bbox;

/**
 Check if tiles cached. If not tile will be downloaded.
 @param tiles tiles to check
 @param progressBlock block that will be called when one tile is checked.
 */
-(void) cacheTiles:(NSArray<NSNumber*> *_Nonnull)tiles progressBlock:(GLMapTileDownloadProgressBlock _Nullable) progressBlock;

/**
 Returns bbox for given tile
 @param tile tile to calculate bbox
 @return bbox of tile
 */
-(GLMapBBox) bboxForTile:(uint64_t) tile;

@end
