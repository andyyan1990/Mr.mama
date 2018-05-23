//
//  VectorMapInfo.h
//  GLMap
//
//  Created by Evgen Bodunov on 12/6/13.
//  Copyright (c) 2014 Evgen Bodunov. All rights reserved.
//

#import "GLMapViewTypes.h"

@class GLMapLocaleSettings;

/**
 Notification is sent when GLMapInfo.state property is changed
 */
extern NSString *_Nonnull kGLMapInfoStateChanged;
/**
 Notification is sent when GLMapInfo.downloadProgress or GLMapInfo.processedProgress property is changed
 */
extern NSString *_Nonnull kGLMapInfoDownloadProgress;
/**
 Notification is sent when map is downloaded
 */
extern NSString *_Nonnull kGLMapInfoDownloadFinished;

/**
 `GLMapInfo` is a class with general information about vector map. Returned by `-[GLMapManager cachedMapList]`
 */
@interface GLMapInfo : NSObject

/// Plain -init is disabled
-(instancetype _Nonnull) init __attribute__((unavailable("GLMapInfo returned by `[GLMapInfo cachedMapList]`")));

#pragma mark - Properties

/**
 An offline map state
 */
@property (readonly) GLMapInfoState state;

/**
 A dictonairy with names of this map (read-only).
 
 Key value is a language code
 */
@property (readonly) NSDictionary *_Nullable names;

/**
 Identification number of the offline map (read-only).
*/
@property (readonly) int64_t mapID;

/**
 The timestamp of the offline map on the server (read-only).
 */
@property (readonly) NSTimeInterval serverTimestamp;

/**
 The latitude and longtitude of the centre of the map (read-only).
 */
@property (readonly) GLMapGeoPoint location;

/**
 The array contains sub-regions of the current offline map (read-only).
 
 Sub-regions are used for the offline maps with the large file size (approximitaly more than 300 MB)
 */
@property (readonly) NSArray<GLMapInfo *> *_Nonnull subMaps;

/**
 Parent of sub-region or nil if not a sub-region.
 */
@property (readonly) GLMapInfo *_Nullable parent;

/**
 The path to the offline map on the disk (read-only).
 */
@property (readonly) NSString *_Nullable path;

/**
 The size of the decompressed offline map on the disk (read-only).
 */
@property (readonly) int64_t sizeOnDisk;

/**
 The size of the offline map on the server (read-only).
 
 Maps are stored on the server in compresed format
 */
@property (readonly) int64_t sizeOnServer;

/**
 The timestamp of the offline map on the disk (read-only).
 
 Timestamp on the disk and timestamp on the server differs in case of a map update on the server appears.
 */
@property (readonly) NSTimeInterval timestamp;

/**
 Indicates progress of downloading of the offline map in percents (read-only).
 */
@property (readonly) float downloadProgress;

#pragma mark - Static Methods

/**
 Changes storage path
 
 @param storagePath A path to folder where offline maps is stored
 */
+ (void) setStoragePath:(NSString *_Nonnull)storagePath;

/**
 A path to folder where offline maps is stored
 */
+ (NSString *_Nonnull) storagePath;

#pragma mark - Methods

/**
 Returns name of the map in requested language.
 
 @param language preffered language
 
 @return localised name of the map.
 */
- (NSString *_Nullable) nameInLanguage:(NSString *_Nonnull)language;

/**
 @return name of the map in native language.
 */
- (NSString *_Nonnull) name;

/**
 Returns name of the map according language priority settings. It checks for aviability of translated name from first language in priority list to the last one until first translated name is found.
 
 @param settings language order settings
 
 @return localised name of the map.
 */
- (NSString *_Nullable) localizedName:(GLMapLocaleSettings *_Nonnull)settings;

/**
 Distance from center of the map to the given location.
 
 @param location Some location
 
 @return distance in meters
 */
- (double) distanceFrom:(GLMapGeoPoint)location;

/**
 Distance from border of the map to the given point.
 
 @param location Point on the map
 
 @return Distance to the map border measured in internal units. Returns 0 if point is inside map border.
 */
- (double) distanceFromBorder:(GLMapPoint)location;

@end