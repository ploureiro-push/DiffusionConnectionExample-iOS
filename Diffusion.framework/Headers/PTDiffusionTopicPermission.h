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
 @brief Permissions protecting access-controlled operations that are evaluated
 for a specific topic path.

 @see PTDiffusionGlobalPermission

 @since 6.3
 */
@interface PTDiffusionTopicPermission : PTDiffusionEnumeration

/**
 Required to receive information from a topic.

 If a session does not have read_topic permission for a topic, the topic will be
 excluded from the results of subscription or fetch operations for the session,
 and the topic's details cannot be retrieved by the session.

 @see #selectTopic

 @since 6.3
 */
+(instancetype)readTopic;

/**
 Update a topic.

 @since 6.3
 */
+(instancetype)updateTopic;

/**
 Add a topic or remove a topic.

 @since 6.3
 */
+(instancetype)modifyTopic;

/**
 Send a message to a handler registered with the server.

 @since 6.3
 */
+(instancetype)sendToMessageHandler;

/**
 Send a message to a client session.

 @since 6.3
 */
+(instancetype)sendToSession;

/**
 Use a topic selector that selects the topic path.

 A session must have this permission for the path prefix of any topic selector
 used to subscribe or fetch.

 When the subscription or fetch request completes, the resulting topics are
 further filtered based on the #readTopic permission.

 A session that has #readTopic but not #selectTopic for a particular topic path
 cannot subscribe directly to topics belonging to the path. However, the session
 can be independently subscribed by a control session that has #modifySession
 permission in addition to the appropriate #selectTopic permission.

 @since 6.3
 */
+(instancetype)selectTopic;

/**
 Evaluate queries that return a non-current view of a time series topic.

 The #readTopic permission is required to evaluate any type of query for a time
 series topic. This permission is additionally required for queries that
 potentially return a non-current view of all or part of a time series. Such
 queries include value range queries that specify an edit range, and all types
 of edit range query.

 @see PTDiffusionTimeSeriesFeature

 @since 6.3
 */
+(instancetype)queryObsoleteTimeSeriesEvents;

/**
 Submit edits to time series topic events.

 The #updateTopic permission is required to update a time series topic. This
 permission is additionally required to submit edits to a time series topic.

 @see PTDiffusionTimeSeriesFeature
 @see #editOwnTimeSeriesEvents

 @since 6.3
 */
+(instancetype)editTimeSeriesEvents;

/**
 Submit edits to time series topic events which have an author which is the same
 as the principal of the calling session.

 This permission is a more restrictive alternative to #editTimeSeriesEvents.

 The #updateTopic permission is required to update a time series topic. This
 permission is additionally required to submit edits to a time series topic
 where the event author is the same as the principal of the calling session.

 @see PTDiffusionTimeSeriesFeature
 @see #editTimeSeriesEvents

 @since 6.3
 */
+(instancetype)editOwnTimeSeriesEvents;

/**
 Acquire a session lock.

 @see PTDiffusionSessionLock

 @since 6.3
 */
+(instancetype)acquireLock;

/**
 A permission that is unsupported by the session.
 
 @since 6.3
 */
+(instancetype)unknownTopicPermission;

@end

NS_ASSUME_NONNULL_END
