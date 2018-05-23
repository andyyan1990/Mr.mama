//
//  GLSearchCategory.h
//  GLMap
//
//  Created by Arkadiy Tolkun on 12/7/16.
//  Copyright © 2016 Evgen Bodunov. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GLMapLocaleSettings;
/**
 `GLSearchCategory` class holds information about category that can be displayed to user.
 */
@interface GLSearchCategory : NSObject

/// Plain -init is disabled
-(instancetype _Nonnull) init __attribute__((unavailable("Please use `GLSearchCategories` to work with `GLSearchCategory` objects.")));

/**
 Returns name of the category according language priority settings. It checks for translated name from first language in priority list to the last one until first translated name is found.
 
 @param settings language order settings
 
 @return localised name of the category.
 */
- (NSString *_Nullable) localizedName:(GLMapLocaleSettings *_Nonnull)settings;

/**
 Returns name of the category according language priority settings. It checks for aviability of translated name from first language in priority list to the last one until first translated name is found. If category was found by search request matched part of text will be highlighted by given color.
 
 @param normal Normal attributes
 @param highlight Highlight attributes
 @param localeSettings language order settings
 @return localised name of the category.
 */
- (NSAttributedString *_Nullable) attributedName:(NSDictionary *_Nonnull)normal highlight:(NSDictionary *_Nonnull)highlight localeSettings:(GLMapLocaleSettings *_Nonnull)localeSettings;

/**
 Icon name of the category.
 */
@property (readonly) NSString *_Nonnull iconName;

/**
 Child categories of the category.
 */
@property (readonly) NSArray<GLSearchCategory *> *_Nonnull childs;

@end
