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
#import <Diffusion/PTDiffusionEnumeration.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The type of topic notification received.

 @see PTDiffusionTopicNotificationListener

 @since 6.1
 */
@interface PTDiffusionTopicNotificationType : PTDiffusionEnumeration

/**
 The topic has been added.

 @since 6.1
 */
+(instancetype)added;

/**
 The topic has been removed.

 @since 6.1
 */
+(instancetype)removed;

/**
 The topic existed at the time of the selector registration.

 @since 6.1
 */
+(instancetype)selected;

/**
 The topic is no longer selected due to the removal of a selector.

 @since 6.1
 */
+(instancetype)deselected;

@end

NS_ASSUME_NONNULL_END
