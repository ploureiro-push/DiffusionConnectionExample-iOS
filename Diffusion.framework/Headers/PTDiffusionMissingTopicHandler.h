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
#import <Diffusion/PTDiffusionTopicTreeRegistrationDelegate.h>

@class PTDiffusionMissingTopicNotification;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Handler called when a client session subscribes or fetches using a topic
 selector that matches no topics.
 
 @see PTDiffusionTopicControlFeature

 @since 5.7
 */
@protocol PTDiffusionMissingTopicHandler <PTDiffusionTopicTreeRegistrationDelegate>

/**
 Called when a client session requests a topic that does not exist, and the topic
 path belongs to part of the topic tree for which this handler was registered.

 The handler implementation should take the appropriate action (for example,
 create the topic), and then call proceed on the supplied notification.
 This allows the client request to continue and successfully resolve against the
 topic if it was created.
 
 Alternatively, the handler can call cancel to discard the request.
 A handler should always call proceed or cancel, otherwise resources will continue
 to be reserved on the server and the client's request will not complete.
 
 @param registration The topic tree registration for which this handler applies.

 @param notification The missing topic notification, providing proceed and cancel
 methods to be used as required.

 @since 5.7
 */
-(void)diffusionTopicTreeRegistration:(PTDiffusionTopicTreeRegistration *)registration
          hadMissingTopicNotification:(PTDiffusionMissingTopicNotification *)notification;

@end

NS_ASSUME_NONNULL_END
