//
//  GLMapViewTypes.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 1/15/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#ifndef GLMapViewSDK_GLMapViewTypes_h
#define GLMapViewSDK_GLMapViewTypes_h

#include <stdint.h>

#ifdef __OBJC__
#   import <Foundation/Foundation.h>
#else
#   define CF_SWIFT_NAME(x)
#   define NS_ENUM(_type, _name) enum _name : _type _name; enum _name : _type
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     State of the vector map. `GLMapInfo` tracks state of the vector map.
     */
    typedef NS_ENUM(uint8_t, GLMapInfoState)
    {
        /** Map is deleted and there is no way to download it again because it was removed from map list. */
        GLMapInfoState_Removed,
        /** Map is not downloaded, but available to download. */
        GLMapInfoState_NotDownloaded,
        /** Map is downloaded sucessfully. */
        GLMapInfoState_Downloaded,
        /** New version of map is available to download. */
        GLMapInfoState_NeedUpdate,
        /** User cancelled map downloading. */
        GLMapInfoState_NeedResume,
        /**  Map downloading is in progress. */
        GLMapInfoState_InProgress,
    };
    
    /// Placement of the object on map view. It's used for scale ruler and attribution placement
    typedef NS_ENUM(uint8_t, GLMapPlacement)
    {
        /// Top left corner
        GLMapPlacement_TopLeft,
        /// Top center of the screen
        GLMapPlacement_TopCenter,
        /// Top right corner
        GLMapPlacement_TopRight,
        
        /// Bottom left corner
        GLMapPlacement_BottomLeft,
        /// Bottom center of the screen
        GLMapPlacement_BottomCenter,
        /// Bottom rigth corner
        GLMapPlacement_BottomRight,
        
        /// Object should be hidden
        GLMapPlacement_Hidden
    };
    
    
    /// Type of data inside of the `GLMapVectorObject`
    typedef NS_ENUM(uint8_t, GLMapVectorObjectType)
    {
        /// No geometry loaded yet
        GLMapVectorObjectType_Unknown,
        /// Point object
        GLMapVectorObjectType_Point,
        /// Line object
        GLMapVectorObjectType_Line,
        /// Polygon object
        GLMapVectorObjectType_Polygon
    };
    
    ///Mode for routing
    typedef NS_ENUM(uint8_t, GLMapRouteMode)
    {
        ///Drive mode
        GLMapRouteMode_Drive,
        ///Cycle mode
        GLMapRouteMode_Cycle,
        ///Walk mode
        GLMapRouteMode_Walk,
        ///Straight mode
        GLMapRouteMode_Straight
    };
    
    /// Errors retured by download tasks
    typedef NS_ENUM(uint16_t, GLMapError)
    {
        /// No error
        GLMapError_Success = 0x0000,
        /// Error information is not set
        GLMapError_Empty,
        /// Map download task is cancelled
        GLMapError_Cancelled,
        /// Error occured during tile parsing
        GLMapError_InvalidTileData,
        /// Map list cannot be parsed
        GLMapError_InvalidMapListData,
        /// Invallid response from server
        GLMapError_InvalidResponse,
        /// Can't allocate new objects
        GLMapError_NoMemory,
        
        /// Failed to open output file
        GLMapError_FailedToOpenOutputFile,
        /// Error during writing data into file
        GLMapError_FailedToWrite,
        
        /// Used internally. Check for `[NSError domain]`, if it's equal to `HTTP`, `[NSError code]` is HTTP error code.
        GLMapError_HTTP = 0x1000,
        /// Used internally. Check for `[NSError domain]`, if it's equal to `CURL`, `[NSError code]` is CURL error code. https://curl.haxx.se/libcurl/c/libcurl-errors.html
        GLMapError_CURL = 0x2000,
        /// Used internally. Check for `[NSError domain]`, if it's equal to `XZ`, `[NSError code]` is XZ archiver error code.
        GLMapError_XZ = 0x4000,
        /// Used internally. Check for `[NSError domain]`, if it's equal to `Valhalla`, `[NSError code]` is Valhalla archiver error code.
        GLMapError_Valhalla = 0x8000,
        /// :nodoc:
    };
    
    /// Checks if it's error or success code
    static inline bool GLMapIsSuccess(GLMapError v)
    {
        return v == GLMapError_Success;
    }
    
    /// Supported unit systems
    typedef NS_ENUM(uint8_t, GLUnitSystem)
    {
        /// International System of Units (SI)
        GLUnitSystem_International,
        /// Imperial units
        GLUnitSystem_Imperial,
        /// Nautical units
        GLUnitSystem_Nautical
    };
    
    /// Supported units
    typedef NS_ENUM(uint8_t, GLUnits)
    {
        /// Kilometers
        GLUnits_Kilometers,
        /// Meters
        GLUnits_Meters,
        /// Miles
        GLUnits_Miles,
        /// Foots
        GLUnits_Foots,
        /// Nautical miles
        GLUnits_NauticalMiles
    };
    
    /// Maneuver types
    typedef NS_ENUM(uint8_t, GLManeuverType)
    {
        /// Check https://github.com/valhalla/valhalla-docs/blob/master/turn-by-turn/api-reference.md
        GLManeuverType_None = 0,
        GLManeuverType_Start = 1,
        GLManeuverType_StartRight = 2,
        GLManeuverType_StartLeft = 3,
        GLManeuverType_Destination = 4,
        GLManeuverType_DestinationRight = 5,
        GLManeuverType_DestinationLeft = 6,
        GLManeuverType_Becomes = 7,
        GLManeuverType_Continue = 8,
        GLManeuverType_SlightRight = 9,
        GLManeuverType_Right = 10,
        GLManeuverType_SharpRight = 11,
        GLManeuverType_UturnRight = 12,
        GLManeuverType_UturnLeft = 13,
        GLManeuverType_SharpLeft = 14,
        GLManeuverType_Left = 15,
        GLManeuverType_SlightLeft = 16,
        GLManeuverType_RampStraight = 17,
        GLManeuverType_RampRight = 18,
        GLManeuverType_RampLeft = 19,
        GLManeuverType_ExitRight = 20,
        GLManeuverType_ExitLeft = 21,
        GLManeuverType_StayStraight = 22,
        GLManeuverType_StayRight = 23,
        GLManeuverType_StayLeft = 24,
        GLManeuverType_Merge = 25,
        GLManeuverType_RoundaboutEnter = 26,
        GLManeuverType_RoundaboutExit = 27,
        GLManeuverType_FerryEnter = 28,
        GLManeuverType_FerryExit = 29,
        GLManeuverType_Transit = 30,
        GLManeuverType_TransitTransfer = 31,
        GLManeuverType_TransitRemainOn = 32,
        GLManeuverType_TransitConnectionStart = 33,
        GLManeuverType_TransitConnectionTransfer = 34,
        GLManeuverType_TransitConnectionDestination = 35,
        GLManeuverType_PostTransitConnectionDestination = 36,
    };
    
    /// Resource information filled by `GLMapResourceBlock`
    typedef struct GLMapResource {
        /// Object data
        void *data;
        /// Object data size
        uint32_t dataSize;
        /// Image scale if it's image
        float imageScale;
    }
    /// :nodoc:
    GLMapResource;
    
    /// @return Returns empty resource data.
    static inline GLMapResource GLMapResourceEmpty() 
    {
        return (GLMapResource){0, 0, 0.f};
    }
    
    /// Map tile state
    typedef NS_ENUM(uint8_t, GLMapTileState)
    {
        /// Tile without data
        GLMapTileState_NoData,
        /// Tile data is being loaded
        GLMapTileState_Updating,
        /// Tile already has data
        GLMapTileState_HasData,
    };
    
    /// Transition functions available
    typedef NS_ENUM(uint8_t, GLMapTransitionFunction)
    {
        /// Instant set value. No animation.
        GLMapTransitionInstant = 0,
        /// Linear animation.
        GLMapTransitionLinear,
        /// Ease-in animation.
        GLMapTransitionEaseIn,
        /// Ease-out animation.
        GLMapTransitionEaseOut,
        /// Ease-in-out animation.
        GLMapTransitionEaseInOut,
    };
    
    /// Merkator tile coordinates
    typedef struct GLMapTilePos
    {
        /// X coordinate
        int x;
        /// Y coordinate
        int y;
        /// Z coordinate
        int z;
    }
    /// :nodoc:
    GLMapTilePos;

    /**
     Creates `GLMapTilePos`
     
     @param x X coordinate
     @param y Y coordinate
     @param z Z coordinate
     @return New tile position
     */
    static inline GLMapTilePos GLMapTilePosMake(int x, int y, int z)
    {
        return (GLMapTilePos){x, y, z};
    }
    
    /// Geo point with latitude and longitude
    typedef struct GLMapGeoPoint
    {
        /// Latitude
        double lat;
        /// Longitude
        double lon;
    }
    /// :nodoc:
    GLMapGeoPoint;
    
    /**
     Creates new `GLMapGeoPoint`.
     
     @param lat Latitude
     @param lon Longitude
     @return New geo point
     */
    static inline GLMapGeoPoint GLMapGeoPointMake(double lat, double lon)
    {
        return (GLMapGeoPoint){lat, lon};
    }
    
    /**
     Checks equality of two geo points
     
     @param a First geo point
     @param b Second geo point
     @return `true` if map points is equal
     */
    static inline bool GLMapGeoPointEqual(GLMapGeoPoint a, GLMapGeoPoint b)
    {
        return a.lat == b.lat && a.lon == b.lon;
    }
    
    /// `GLMapPoint` always uses internal map coordinates. From 0 to `GLMapPointMax` for X and Y axis. Origin is at the top left corner.
    typedef struct GLMapPoint
    {
        /// X coordinate
        double x;
        /// Y coordinate
        double y;
    }
    /// :nodoc:
    GLMapPoint;
    
    /// Maximum `GLMapPoint` value. World size in map coordinates is from 0 to `GLMapPointMax`.
    extern const int32_t GLMapPointMax;
    
    /** 
     Creates new `GLMapPoint`
    
     @param x X coordinate
     @param y Y coordinate
     @return New map point
     */
    static inline GLMapPoint GLMapPointMake(double x, double y)
    {
        return (GLMapPoint){x,y};
    }
    
    /**
     Checks equality of two map points
     
     @param a First map point
     @param b Second map point
     @return `true` if map points is equal
     */
    static inline bool GLMapPointEqual(GLMapPoint a, GLMapPoint b)
    {
        return a.x == b.x && a.y == b.y;
    }
    
    /// `GLMapColor` is color type based on `uint32_t`
    typedef uint32_t GLMapColor;
    
    /**
     Creates new color from int chanel values 0 - 255
     
     @param r Red channel value
     @param g Green channel value
     @param b Blue channel value
     @param a Alpha channel value
     
     @return Returns new color object
     */
    static inline GLMapColor GLMapColorMake(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        return (a << 24) | (b << 16) | (g << 8) | r;
    }
    
    /**
     Creates new color from float chanel values 0.0 - 1.0
     
     @param r Red channel value
     @param g Green channel value
     @param b Blue channel value
     @param a Alpha channel value
     
     @return Returns new color object
     */
    static inline GLMapColor GLMapColorMakeF(float r, float g, float b, float a)
    {
        return GLMapColorMake(r * 255, g * 255, b * 255, a * 255);
    }
    
#ifdef __OBJC__
    /// :nodoc:
    @class UIColor;
    
    /**
     Creates `UIColor` object from our `GLMapColor`
     
     @param color Initial color
     @return New `UIColor` object
     */
    UIColor *UIColorFromGLMapColor(GLMapColor color);

    /**
     Convert `UIColor` to `GLMapColor`

     @param color color to conver
     @@return converted value
     */
    GLMapColor GLMapColorMakeFromUIColor(UIColor *color);
#endif    
    
    /// Point of track with color
    typedef struct GLTrackPoint
    {
        /**
         Point of track in framework coordinates
         */
        GLMapPoint pt;
        /**
         Color of point. Specific color could be set for each point.
         */
        GLMapColor color;
    }
    /// :nodoc:
    GLTrackPoint;
    
    /// Point of track with color
    typedef struct GLRoutePoint
    {
        /**
         * Coordinates of route point
         */
        GLMapGeoPoint pt;
        
        /**
         * Heading at given point or NaN
         */
        double heading;
        
        /**
         * If set to true point is a stop. Otherwise it is a waypoint.
         */
        bool isStop;
    }
    /// :nodoc:
    GLRoutePoint;

    /// Creates route point
    CF_SWIFT_NAME(GLRoutePoint.init(pt:heading:isStop:))
    static inline GLRoutePoint GLRoutePointMake(GLMapGeoPoint pt, double heading, bool isStop)
    {
        return (GLRoutePoint){pt, heading, isStop};
    }
    
    /// Bounding box
    typedef struct GLMapBBox
    {
        /// Bounding box origin. Point with minimal coordinates.
        GLMapPoint origin;
        /// Size of the bounding box.
        GLMapPoint size;
    }
    /// :nodoc:
    GLMapBBox;

    /**
     @return Returns empty bounding box
     */
    static inline GLMapBBox GLMapBBoxEmpty()
    {
        return (GLMapBBox) {GLMapPointMake(0, 0), GLMapPointMake(-1, -1)};
    }

    /**
     Adds point into existing bounding box.
     
     @param bbox Bounding box
     @param point Point to add into bounding box
     */
    static inline GLMapBBox GLMapBBoxAddPoint(GLMapBBox bbox, GLMapPoint point)
    {
        if (bbox.size.x < 0 && bbox.size.y < 0)
        {
            bbox.size = GLMapPointMake(0,0);
            bbox.origin = point;
        } else {
            if (point.x < bbox.origin.x)
            {
                bbox.size.x += bbox.origin.x - point.x;
                bbox.origin.x = point.x;
            }
            if (point.x > bbox.origin.x + bbox.size.x)
            {
                bbox.size.x = point.x - bbox.origin.x;
            }
            
            if (point.y < bbox.origin.y)
            {
                bbox.size.y += bbox.origin.y - point.y;
                bbox.origin.y = point.y;
            }
            if (point.y > bbox.origin.y + bbox.size.y)
            {
                bbox.size.y = point.y - bbox.origin.y;
            }
        }
        return bbox;
    }
    
    /**
     Checks if the bbox contains the point
     
     @param bbox Bounding box
     @param point Point to check
     @return true if point is in bbox
     */
    static inline bool GLMapBBoxContains(GLMapBBox bbox, GLMapPoint point)
    {
        if (point.y < bbox.origin.y)
            return false;
        if (point.y > bbox.origin.y + bbox.size.y)
            return false;
        
        if (point.x >= bbox.origin.x && point.x <= bbox.origin.x + bbox.size.x)
            return true;

        if (point.x >= bbox.origin.x - GLMapPointMax && point.x <= bbox.origin.x + bbox.size.x - GLMapPointMax)
            return true;

        if (point.x >= bbox.origin.x + GLMapPointMax && point.x <= bbox.origin.x + bbox.size.x + GLMapPointMax)
            return true;
        
        return false;
    }
    
    /**
     Creates new bounding box
     
     @param origin Origin point
     @param width Width
     @param height Height
     @return New bounding box
     */
    CF_SWIFT_NAME(GLMapBBox.init(origin:width:height:))
    static inline GLMapBBox GLMapBBoxMake(GLMapPoint origin, double width, double height)
    {
        return (GLMapBBox){origin, GLMapPointMake(width, height)};
    }
    
    /**
     Checks equality of two bounding boxes
     
     @param a First bounding box
     @param b Second bounding box
     @return `true` if bounding boxes is equal
     */
    static inline bool GLMapBBoxEqual(GLMapBBox a, GLMapBBox b)
    {
        return GLMapPointEqual(a.origin, b.origin) &&  GLMapPointEqual(a.size, b.size);
    }
    
    /**
     Returns center of bbox
     
     @return center of bbox
     */
    static inline GLMapPoint GLMapBBoxCenter(GLMapBBox a)
    {
        return GLMapPointMake(a.origin.x + a.size.x/2, a.origin.y + a.size.y/2);
    }
    
    /**
     Creates map point from geo coordinates
     
     @param lat Latitude
     @param lon Longitude
     @return New map point
     */
    GLMapPoint GLMapPointMakeFromGeoCoordinates(double lat, double lon);
    
    /**
     Creates map point from geo point
     @param point Geo point
     @return New point
     */
    GLMapPoint GLMapPointFromMapGeoPoint(GLMapGeoPoint point);
    
    /**
     Creates geo point from map coordinates
     
     @param point Map point
     @return New geo point
     */
    GLMapGeoPoint GLMapGeoPointFromMapPoint(GLMapPoint point);
    
    /**
     Calculates distance between two points on map
     
     @param a First point on map
     @param b Second point on map
     @return Distance in meters
     */
    double GLMapDistanceBetweenPoints(GLMapPoint a, GLMapPoint b);
    
    /**
     Calculates distance between two points. Сontains internal conversion to GLMapGeoPoint.
     
     @param a First geo point
     @param b Second geo point
     @return Distance in meters
     */
    double GLMapDistanceBetweenGeoPoints(GLMapGeoPoint a, GLMapGeoPoint b);
    
    /**
     Calculates bearing between two geo points.
     
     @param a First point
     @param b Second point
     @return bearing angle in degrees
     */
    double GLMapBearingBetweenPoints(GLMapPoint a, GLMapPoint b);
    
    /**
     Calculates bearing between two points. Сontains internal conversion to GLMapGeoPoint.
     
     @param a First geo point
     @param b Second geo point
     @return bearing angle in degrees
     */
    double GLMapBearingBetweenGeoPoints(GLMapGeoPoint a, GLMapGeoPoint b);
    
    /// Set of GLMapPoint
    typedef void *GLMapPointSet;
    
    /**
     Creates new empty set
     **/
    GLMapPointSet GLMapPointSetCreate(void);
    
    /**
     Destroys set
     @param set set to destroy
     **/
    void GLMapPointSetDestroy(GLMapPointSet set);
    
    /**
     Adds new point to set. Can add many points with same coordinates.
     @param set set to modify
     @param point point to add
     **/
    void GLMapPointSetInsert(GLMapPointSet set, GLMapPoint point);

    /**
     Inserts new point to set.
     @param set set to modify
     @param point point to insert.
     @return `true` if point is inserted. `false` if point with same coordinates already in set.
     **/
    bool GLMapPointSetInsertUnique(GLMapPointSet set, GLMapPoint point);
    
    /**
     Removes point from set
     @param set set to modify
     @param point point to remove
     @return YES if point was removed
     **/
    bool GLMapPointSetRemove(GLMapPointSet set, GLMapPoint point);
    
    /**
     Checks if set have given point
     @param set set to test
     @param point point to test
     @return YES if point is in set
     **/
    bool GLMapPointSetContains(GLMapPointSet set, GLMapPoint point);

    /**
     Returns nearest point in set
     @param set object created by `GLMapPointSetCreate`
     @param point reference point to calculate distance
     @return Nearest point in set
     **/
    GLMapPoint GLMapPointSetNearestPoint(GLMapPointSet set, GLMapPoint point);
    
    
    /// Allows application to change verbosity of GLMap logs
    extern char GLMapLogMask;
    
    // loglevel
#define VERBOSE_FLAG	1 << 0
#define ERROR_FLAG      1 << 1
#define FATAL_FLAG		1 << 2
#define OPENGL_FLAG     1 << 3
    
    /// :nodoc:
    void SendLogMessage(const char *, ...);
    
#ifdef __cplusplus
}
#endif

#endif

