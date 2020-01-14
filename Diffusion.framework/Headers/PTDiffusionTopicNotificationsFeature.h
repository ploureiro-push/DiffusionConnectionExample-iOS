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
#import <Diffusion/PTDiffusionFeature.h>

@class PTDiffusionStream;
@class PTDiffusionTopicNotificationRegistration;

@protocol PTDiffusionTopicNotificationListener;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The Topic Notifications feature allows a client session to receive
 notifications about changes to selected topics.

 The Topic Notifications feature for a session can be obtained from the
 session's `topicNotifications` property.

 ### Notifications

 Sessions receive notifications by implementing a
 PTDiffusionTopicNotificationListener. The listener will be provided with a
 PTDiffusionTopicSpecification for all topics bound to paths that match
 registered selectors, and any subsequent notifications for the selected
 topics on those paths. Notifications will only be emitted for paths where a
 topic is bound.

 For example, with a registered selector `"?a//"`, if a topic is added at path
 `a/b/c/d` with no topics bound to paths higher in the hierarchy
 `diffusionStream:didReceiveNotificationWithType:topicPath:specification:`
 will be called once with a topic path of `"a/b/c/d"`, a notification type of
 PTDiffusionTopicNotificationType::added, and the topic's associated
 PTDiffusionTopicSpecification.

 The nature of the notification is provided by the
 PTDiffusionTopicNotificationType enum. PTDiffusionTopicNotificationType::added
 and PTDiffusionTopicNotificationType::removed represent structural changes to
 the topic tree; PTDiffusionTopicNotificationType::selected indicates that a
 pre-existing topic has been selected by a new registered selector, and
 similarly PTDiffusionTopicNotificationType::deselected indicates that a topic
 is no longer selected because of changes to the set of registered selectors for
 the listener.

 ### Selection and deselection

 Registered PTDiffusionTopicNotificationListener implementations will receive
 notifications for all topics matching registered selections. Selection of
 topics using @ref md_topic_selectors "topic selector" expressions is provided
 via the PTDiffusionTopicNotificationRegistration associated for a specific
 listener.

 A session can request selections at any time, even if the topics do not exist
 at the server. Selections are stored on the server and any subsequently added
 topics that match registered selectors will generate notifications.

 ### Immediate descendant notifications

 Listeners will be informed about the presence or absence of unselected
 immediate descendants via
 `diffusionStream:didReceiveDescendantNotificationWithType:topicPath:`. This
 allows listeners to determine whether to select deeper topic paths in order to
 walk the topic tree. An immediate descendant is defined as the first bound
 topic on any branch below a given topic path.

 For example, for topics at `"a/b", "a/c", "a/c/d", "a/e/f/g"`, the immediate
 descendants of `"a"` would be `"a/b", "a/c", "a/e/f/g"`.

 Immediate descendant notifications provide a PTDiffusionTopicNotificationType
 to indicate the reason for the notification in the same manner as for
 topic notifications.

 For example, with a registered selector `">a"`, if a topic is added at path
 `"a/b"` then a descendant notification will be received with a topic path of
 `"a/b"` and a notification type of PTDiffusionTopicNotificationType::added
 If a topic was subsequently added at path `"a/b/c"`, no further notifications
 will be received until
 PTDiffusionTopicNotificationRegistration::selectWithTopicSelectorExpression:completionHandler:
 was used to select the deeper topic path `">a/b"`.

 ### Access control

 A listener will only be notified about topics for which the session has
 `SELECT_TOPIC SELECT_TOPIC` and `READ_TOPIC READ_TOPIC` permissions.
 `SELECT_TOPIC SELECT_TOPIC` determines which selectors a listener may register;
 `READ_TOPIC READ_TOPIC` determines which selected topics the client may receive
 notifications for.

 @see PTDiffusionSession

 @since 6.1
 */
@interface PTDiffusionTopicNotificationsFeature : PTDiffusionFeature

/**
 Register a listener to receive topic notifications.

 @param listener The object which will handle the incoming notifications. It
 will be sent messages asynchronously on the main dispatch queue. A weak
 reference is maintained to this object.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil` and the `registration` argument will point to a
 registration object which can be used to manage the registration. The
 completion handler will be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any arguments are `nil`.

 @since 6.1
 */
-(PTDiffusionStream *)addListener:(id<PTDiffusionTopicNotificationListener>)listener
                completionHandler:(void (^)(PTDiffusionTopicNotificationRegistration * _Nullable registration, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
