//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2017 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;

@class PTDiffusionRecordV2;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Builds free format PTDiffusionRecordV2 values.
 
 This type of builder may be used to generate free format recordV2 values which
 are not constrained by a PTDiffusionRecordV2Schema.

 Every mutating method returns the builder instance allowing calls to be
 chained.

 @since 6.0.1
 */
@interface PTDiffusionRecordV2Builder : NSObject

/**
 Adds a new record comprising the given fields.
 
 @param fields Field values. This may be an empty array, in which case the new
 record is added with no fields.

 @since 6.0.1
 */
-(instancetype)addRecordWithFields:(NSArray<NSString *> *)fields;

/**
 Adds one or more field values.

 If there is a current record, adds the fields to the end of the current record;
 otherwise, adds a new record and adds the fields to that.

 @param fields Field values. This may be an empty array, in which case nothing
 changes.

 @since 6.0.1
 */
-(instancetype)addFields:(NSArray<NSString *> *)fields;

/**
 Clears all current values from the builder allowing it to be reused to generate new data.
 
 @since 6.0.1
 */
-(instancetype)clear;

/**
 Returns an immutable record from the current state of this builder.
 
 @since 6.0.1
*/
-(PTDiffusionRecordV2 *)build;

@end

NS_ASSUME_NONNULL_END
