//
//  GLMapVectorObjectArray.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 3/30/17.
//  Copyright © 2017 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GLMapVectorObject;

/**
 `GLMapVectorObjectArray` is fast and compact container for vector objects. It uses C++ vector of C++ objects inside.
 */
@interface GLMapVectorObjectArray : NSObject

NS_ASSUME_NONNULL_BEGIN

/**
 Initializes empty array
 **/
-(instancetype) init;

/**
 Initializes empty array with given initial capacity
 **/
-(instancetype) initWithCapacity:(NSUInteger)capacity;

/**
 Returns the object located at the specified index.
 If index is beyond the end of the array (that is, if index is greater than or equal to the value returned by count), an NSRangeException is raised.
 
 @param index An index within the bounds of the array.
 @return The object located at index.
 */
- (GLMapVectorObject *) objectAtIndex:(NSUInteger)index;

/**
 Returns the object at the specified index.
 This method has the same behavior as the `objectAtIndex:` method.
 If index is beyond the end of the array (that is, if index is greater than or equal to the value returned by count), an `NSRangeException` is raised.
 You shouldn’t need to call this method directly. Instead, this method is called when accessing an object by index using subscripting.
 
 @param index An index within the bounds of the array.
 @return The object located at index.
 */
- (GLMapVectorObject *) objectAtIndexedSubscript:(NSUInteger)index;

/**
 The number of objects in the array.
 */
@property (readonly) NSUInteger count;

/**
 Calculates bbox of all objects in array
 @return bbox of all objects in array
 */
@property (readonly) GLMapBBox bbox;

/**
 Adds object to array
 **/
-(void) addObject:(GLMapVectorObject *) object;

/**
 Inserts object to array at given index
 **/
-(void) insertObject:(GLMapVectorObject *) object atIndex:(NSUInteger)index;

/**
 Inserts objects to array at given indexes
 **/
-(void) insertObjects:(NSArray<GLMapVectorObject *> *) objects atIndexes:(NSIndexSet *)indexSet;

/**
 Removes object at given index
 **/
-(void) removeObjectAtIndex:(NSUInteger) index;

/**
 Removes object at given indexes
 **/
-(void) removeObjectsAtIndexes:(NSIndexSet *) indexSet;

/**
 Removes all objects from array
 **/
-(void) removeAllObjects;

NS_ASSUME_NONNULL_END

@end
