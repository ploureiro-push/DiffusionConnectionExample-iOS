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

NS_ASSUME_NONNULL_BEGIN

/**
 Key used in the `userInfo` dictionary of an array of NSError objects, having
 the potential to convey more than one error encountered by an underlying
 implementation.

 The associated value is an array of one or more NSError objects.

 @since 6.0
 */
extern NSString *const PTDiffusionUnderlyingErrorsKey;

NS_ASSUME_NONNULL_END
