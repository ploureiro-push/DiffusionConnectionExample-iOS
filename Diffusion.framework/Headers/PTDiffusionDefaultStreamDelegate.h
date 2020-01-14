//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2018 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionStreamDelegate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Default delegate implementation which may be used as an abstract base
 for sub-protocol implementations.

 It logs received closure messages at PTDiffusionLoggingLevel::debug level and
 error messages at PTDiffusionLoggingLevel::warn level.

 @see PTDiffusionLogging

 @since 6.1
 */
@interface PTDiffusionDefaultStreamDelegate : NSObject <PTDiffusionStreamDelegate>

@end

NS_ASSUME_NONNULL_END
