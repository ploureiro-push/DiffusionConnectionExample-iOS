//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2016 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief An immutable delta describing the differences between two binary values.
 
 A `diff` of two binary values creates a binary delta. The binary delta can
 later `apply` to the first value to calculate the second value.

 @since 5.9
 */
@interface PTDiffusionBinaryDelta : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Whether the two values used to create this instance are different.

 @since 5.9
 */
@property(nonatomic, readonly, getter=hasChanges) BOOL changes;

/**
 Compares the receiver to the given binary delta.

 @param binaryDelta The binary delta object with which to compare the receiver.

 @return `YES` if the data in binary delta is equal to the contents of the receiver, otherwise `NO`.

 @note Two binary delta objects are equal if they carry the same information.

 @since 5.9
 */
-(BOOL)isEqualToBinaryDelta:(nullable PTDiffusionBinaryDelta *)binaryDelta;

@end

NS_ASSUME_NONNULL_END
