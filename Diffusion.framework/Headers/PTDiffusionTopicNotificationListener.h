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

@class PTDiffusionTopicNotificationType;
@class PTDiffusionTopicSpecification;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Methods implemented by classes handling streamed topic notifications.

 This protocol defines methods to be implemented by classes wishing to receive
 streamed topic notifications.

 @see PTDiffusionTopicNotificationsFeature

 @since 6.1
 */
@protocol PTDiffusionTopicNotificationListener <PTDiffusionStreamDelegate>

/**
 Notification for an immediate descendant of a selected topic path.
 This notifies the presence or absence of a descendant topic that may
 subsequently be explicitly selected.

 @param stream The stream that received the update.

 @param type The type of notification.

 @param topicPath The path of the immediate descendant that is not selected.

 @since 6.1
 */
-(void)                      diffusionStream:(PTDiffusionStream *)stream
    didReceiveDescendantNotificationWithType:(PTDiffusionTopicNotificationType *)type
                                   topicPath:(NSString *)topicPath;

/**
 Notification for a selected topic.

 @param stream The stream that received the update.

 @param type The type of notification.

 @param topicPath The path of the topic that this notification is for.

 @param specification The specification of the topic that this notification is
 for.

 @since 6.1
 */
-(void)            diffusionStream:(PTDiffusionStream *)stream
    didReceiveNotificationWithType:(PTDiffusionTopicNotificationType *)type
                         topicPath:(NSString *)topicPath
                     specification:(PTDiffusionTopicSpecification *)specification;

@end

NS_ASSUME_NONNULL_END
