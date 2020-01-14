//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2019 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionUpdateConstraint.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A constraint requiring the current value of a JSON topic to match the
 partially described value.

 The Swift code:

     let constraint = try PTDiffusionUpdateConstraint
         .jsonValue()
         .withStringValue(idValue, atPointer: "/id")
         .without("/cancellation")

 creates a constraint for a JSON object with a specific ID value and no value
 for a "cancellation" property.

 Missing keys are matched differently to keys that are present with `null`
 values.

 @since 6.3
 */
@interface PTDiffusionPartialJSONUpdateConstraint : PTDiffusionUpdateConstraint

/**
 Require a `null` value at a specific position in the JSON object.

 @param pointer A [JSON Pointer](https://tools.ietf.org/html/rfc6901) syntax
 reference locating the `null` value in the JSON object.

 @param error Location to store a reason in case of failure. May be `nil`.

 @return A new constraint or `nil` if there was an error.

 @exception NSInvalidArgumentException If pointer is `nil`.

 @since 6.3
 */
-(nullable instancetype)withNullAt:(NSString *)pointer
                             error:(NSError **)error;

/**
 Require a specific position in the JSON object to be absent. This does not
 match positions that have `null` values.

 @param pointer A [JSON Pointer](https://tools.ietf.org/html/rfc6901) syntax
 reference that should have no value in the JSON object.

 @param error Location to store a reason in case of failure. May be `nil`.

 @return A new constraint or `nil` if there was an error.

 @exception NSInvalidArgumentException If the pointer argument is `nil`.

 @since 6.3
 */
-(nullable instancetype)without:(NSString *)pointer
                          error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
