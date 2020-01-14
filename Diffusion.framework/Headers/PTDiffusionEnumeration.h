//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2016, 2017 Push Technology Ltd., All Rights Reserved.
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
 @brief Base class for objects offering a selection of predefined constant values.
 
 Classes inheriting from this class share more in common with Java's `enum` type than
 they do with C's `enum` (even using Core Foundation's `NS_ENUM` macro) in that they
 are object-based. Benefits of this include:
 
 - Ability to use `nil` in a meaningful way - e.g. to indicate 'not set'.
 - Standard `description` method to aid logging clarity during debug sessions.
 - Extensible to include additional properties.

 @since 5.7
 */
@interface PTDiffusionEnumeration : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Returns the constant values offered by this enumeration.

 @since 5.7
 */
+(NSSet<PTDiffusionEnumeration *> *)elements;

/**
 Compares the receiver to the given enumeration.

 @param enumeration The enumeration object with which to compare the receiver.

 @return `YES` if the enumeration is equal to the receiver, otherwise `NO`.

 @since 5.7
 */
-(BOOL)isEqualToEnumeration:(nullable PTDiffusionEnumeration *)enumeration;

@end

NS_ASSUME_NONNULL_END
