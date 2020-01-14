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
#import <Diffusion/PTDiffusionStream.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A response stream represents an asynchronous, variable length feed of
 messaging responses from other sessions.

 @see PTDiffusionMessagingControlFeature
 @see PTDiffusionBinary
 @see PTDiffusionJSON
 @see PTDiffusionPrimitive
 @see PTDiffusionRecordV2

 @since 6.1
 */
@interface PTDiffusionSessionResponseStream : PTDiffusionStream

@end

NS_ASSUME_NONNULL_END
