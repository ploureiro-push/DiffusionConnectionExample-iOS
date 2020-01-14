//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2016, 2018 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionTopicTreeRegistrationDelegate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Listener for topic events from the server.
 
 @see PTDiffusionTopicControlFeature

 @deprecated Since 6.1. The main use case for this protocol was the removal of
 unused topics. That use case is now much better satisfied using the
 PTDiffusionTopicSpecification#removalPropertyKey to remove a topic using the
 `subscriptions < n for` condition. The older pattern adopting this protocol
 does not work across a cluster, so this protocol will be removed in a future
 release.

 @since 5.7
 */
__deprecated_msg("Will be removed in a future release.")
@protocol PTDiffusionTopicEventListener <PTDiffusionTopicTreeRegistrationDelegate>

/**
 A topic that previously had no subscribers now has at least one.

 @param registration The topic tree registration for which this listener applies.

 @param topicPath The path of the topic.

 @since 5.7
 */
-(void)diffusionTopicTreeRegistration:(PTDiffusionTopicTreeRegistration *)registration
           hasSubscribersForTopicPath:(NSString *)topicPath;

/**
 A topic that previously had some subscribers now has none.

 @param registration The topic tree registration for which this listener applies.

 @param topicPath The path of the topic.

 @since 5.7
 */
-(void)diffusionTopicTreeRegistration:(PTDiffusionTopicTreeRegistration *)registration
         hasNoSubscribersForTopicPath:(NSString *)topicPath;

@end

NS_ASSUME_NONNULL_END
