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
#import <Diffusion/PTDiffusionEnumeration.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Indicates whether the operation caused a topic to be created or if it
 already existed.

 @see PTDiffusionTopicUpdateFeature
 @see PTDiffusionUpdateStream

 @since 6.3
 */
@interface PTDiffusionTopicCreationResult : PTDiffusionEnumeration

/**
 A new topic was created.

 @since 6.3
 */
+(instancetype)created;

/**
 A topic with the same specification already exists.

 @since 6.3
 */
+(instancetype)exists;

@end

NS_ASSUME_NONNULL_END
