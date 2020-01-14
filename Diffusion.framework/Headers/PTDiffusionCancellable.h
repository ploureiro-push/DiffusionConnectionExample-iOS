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

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A cancellable handle to an asynchronous operation.

 @since 6.3
 */
@protocol PTDiffusionCancellable

/**
 Attempts to cancel execution of the operation. Does nothing if the operation
 has already completed, has already been cancelled, or could not be cancelled
 for some other reason.

 @return If this attempt to cancel the operation was viable then `YES`, or if it
 did nothing then `NO`.

 @since 6.3
 */
-(BOOL)cancel;

@end

NS_ASSUME_NONNULL_END
