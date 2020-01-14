//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2016, 2019 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionTopicType.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The specification of a topic.

 A topic is specified in terms of its topic type and a map of property settings
 which define the behavior of the topic.

 @since 5.9
 */
@interface PTDiffusionTopicSpecification : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Returns a topic specification object initialized with the given topic type and
 an empty properties dictionary.

 @since 6.0
 */
-(instancetype)initWithType:(PTDiffusionTopicType)type;

/**
 Returns a topic specification object initialized with the given topic type and
 properties dictionary.

 @exception NSInvalidArgumentException If properties is `nil`.

 @since 6.0
 */
-(instancetype)initWithType:(PTDiffusionTopicType)type
                 properties:(NSDictionary<NSString *, NSString *> *)properties NS_DESIGNATED_INITIALIZER;

/**
 The type of topic.

 @since 5.9
 */
@property(nonatomic, readonly) PTDiffusionTopicType type;

/**
 The topic properties. May be empty.

 @since 5.9
 */
@property(nonatomic, readonly) NSDictionary<NSString *, NSString *>* properties;

/**
 Compares the receiver to the given topic specification.

 @param topicSpecification The topic specification object with which to compare the receiver.

 @return `YES` if the topic specification is equal to the receiver, otherwise `NO`.

 @since 5.9
 */
-(BOOL)isEqualToTopicSpecification:(nullable PTDiffusionTopicSpecification *)topicSpecification;

/**
 Key of boolean topic property indicating whether a topic should publish only
 values.

 By default, topics with a topic data type that supports deltas will publish a
 delta when doing so is more efficient than publishing the value.
 Setting this property to "true" disables this behavior so that deltas are never
 published. This results in more data being transmitted, but allows the client
 to only have to process values and not deltas.

 If this property is not set (or set to something other than "true") and a topic
 publishes deltas, clients need to use value streams to process the topics.
 If a client uses topic streams, it needs to process the deltas manually.

 If the client is using value streams to process the topics, it is not
 recommended to set this property as it will only lead to higher bandwidth usage.

 For topic data types that do not have delta support this value is irrelevant as
 only values would ever be published anyway.

 @since 5.9
 */
+(NSString *)publishValuesOnlyPropertyKey;

/**
 Key of boolean topic property indicating whether a topic should validate
 inbound values.

 By default, the server does not validate received values before sending them on
 to clients. Invalid or corrupt values will be stored in the topic and passed on
 to clients. If this property is set to "true", the server will perform
 additional validation on values to check that it is a valid instance of the
 data type, and if it is not then it will return an error to the updater and not
 update the topic.

 If this value is not set (or set to something other than "true"), no server
 validation of inbound values is performed. This is the recommended setting as
 there is a performance overhead to validation and a client using a value
 updater could not send invalid values anyway.

 @since 5.9
 */
+(NSString *)validateValuesPropertyKey;

/**
 Key of string topic property that specifies the master topic path for a slave
 topic.

 When creating a slave topic using a topic specification then this must be
 specified. For all other topic types it is ignored.

 @deprecated Since 6.4. Slave topics are deprecated. This value will be removed
 in a future release.

 @since 6.0
 */
+(NSString *)slaveMasterTopicPropertyKey
__deprecated_msg("Will be removed in a future release.");

/**
 Key of boolean topic property that sets the 'tidy on unsubscribe' option for a
 topic.

 By default, if a session unsubscribes from a topic, it will receive any updates
 for that topic that were previously queued but not sent.

 If this property is set to "true", when a client session unsubscribes from the
 topic, any updates for the topic that are still queued for the session are
 removed. There is a performance overhead to using this option as the client
 queue must be scanned to find topic updates to remove, however it may prove
 useful for preventing unwanted data being sent to client sessions.

 @since 6.0
 */
+(NSString *)tidyOnSubscribePropertyKey;

/**
 Key of the string topic property that specifies the event data type for a time
 series topic.

 The value is the type name of a data type.

 @see PTDiffusionDataType

 @since 6.0
 */
+(NSString *)timeSeriesEventValueTypePropertyKey;

/**
 Key of the string topic property that specifies the range of events retained by
 a time series topic, as a time series range expression.

 When a new event is added to the time series, older events that fall outside of
 the range are discarded.

 If this property is not specified, a time series topic will retain the ten most
 recent events.

 The value of this property is a time series range expression string composed of
 one or more constraint clauses. Constraints are combined to provide a range of
 events from the end of the time series.

 <dl>
 <dt>limit constraint</dt>
 <dd>A limit constraint specifies the maximum number of events from the
 end of the time series.</dd>
 <dt>last clause</dt>
 <dd>A last constraint specifies the maximum duration of events from the
 end of the time series. The duration is expressed as an integer followed
 by one of the following time units:
 <ul>
 <li>`MS` &ndash; milliseconds</li>
 <li>`S` &ndash; seconds;</li>
 <li>`H` &ndash; hours.</li>
 </ul>
 </dl>

 If a range expression contains multiple constraints, the constraint that
 selects the smallest range is used.

 <table>
 <tr>
 <th>Property value</th>
 <th>Meaning</th>
 </tr>
 <tr>
 <td>`limit 5`</td>
 <td>The five most recent events</td>
 </tr>
 <tr>
 <td>`last 10s`</td>
 <td>All events that are no more than ten seconds older than the latest
 event</td>
 </tr>
 <tr>
 <td>`last 10s limit 5`</td>
 <td>The five most recent events that are no more than ten seconds older
 than the latest event</td>
 </tr>
 </table>

 Range expressions are not case sensitive: `limit 5 last 10s` is equivalent to
 `LIMIT 5 LAST 10S`.

 @since 6.0
 */
+(NSString *)timeSeriesRetainedRangePropertyKey;

/**
 Key of the string topic property that specifies the range of time series topic
 events to send to new subscribers, as a time series range expression.

 This property value is a time series range expression, following the format
 used for #timeSeriesEventValueTypePropertyKey.

 If this property is not specified, new subscribers will be sent the latest
 event if delta streams are enabled and no events if delta streams are disabled.

 @since 6.0
 */
+(NSString *)timeSeriesSubscriptionRangePropertyKey;

/**
 Key of the string topic property that specifies a schema which constrains topic
 values.

 This property is only used by Diffusion recordV2 topics.
 The property value can be generated using the
 PTDiffusionRecordV2Schema#JSONData property of a schema created using a
 PTDiffusionRecordV2SchemaBuilder.

 @since 6.0
 */
+(NSString *)schemaPropertyKey;

/**
 Key of boolean topic property that specifies a topic should not retain
 its last value. Setting this property to "true" allows the topic to
 behave like a stateless topic, while retaining other properties such
 as its data type.

 By default, a topic (other than a stateless, slave, or routing topic)
 will retain its latest value. The latest value will be sent to new
 subscribers. Setting this property to "true" disables this behavior.
 New subscribers will not be sent an initial value. No value will be
 returned for fetch operations that select the topic. This is useful
 for data streams where the values are only transiently valid.

 Setting this property to "true" disables delta streams, regardless of
 the publishValuesOnlyPropertyKey property value. If subsequent values
 are likely to be related, delta streams can provide a performance
 benefit. Consider not setting this property to benefit from delta
 streams, even if there is no other requirement to retain the last
 value.

 Setting this property affects the default subscription range of a
 time series topic. If set to "true", the default subscription range
 will not provide an initial event to new subscribers. The default
 subscription range can be overridden with the
 timeSeriesSubscriptionRangePropertyKey property. Regardless of
 whether this property is set, a time series topic will continue to
 record events according to the timeSeriesRetainedRangePropertyKey
 property.

 @since 6.0
 */
+(NSString *)dontRetainValuePropertyKey;

/**
 Key of the topic property that can be used to prevent a topic from being
 persisted when the server is configured to enable persistence.

 By default, a topic will be persisted if persistence is enabled at the server
 and the topic type supports persistence.

 Setting to "false" will prevent the topic from being persisted.

 @since 6.1
 */
+(NSString *)persistentPropertyKey;

/**
 Key of the topic property that specifies a removal policy for automatic
 removal of the topic (and/or other topics).

 This property is specified as an expression which defines one or more
 conditions that are to be satisfied before automatic removal occurs.

 The expression takes the form:

     when <conditions> [remove "<selector>"]

 At least one *condition* must be supplied. If more than one is supplied, they
 must be separated by logical operators (`and` or `or`). The natural evaluation
 order of the operators may be changed by surrounding with parentheses (e.g.
 (*condition* `and` *condition*)).

 The `remove` clause is optional. It provides a
 @ref md_topic_selectors "topic selector" expression to be evaluated by the
 server, representing the topics to be removed. If a `remove` clause is
 specified, the topic with the removal policy will only be removed if its path
 matches the selector expression. The selector must be surrounded by either
 double or single quotes.

 The permissions that are applied at the time of removal are those defined by
 the roles of the principal that created the topic at the time of creation. The
 roles of that principal may therefore change before the removal with no effect,
 but if the permissions given to the roles change it may have an effect upon the
 final removal.

 Only one occurrence of each of the following condition types may be included
 within the expression:

 <table>
 <tr>
 <th align="left">Condition&nbsp;Type</th>
 <th align="left">Format</th>
 <th align="left">Usage</th>
 </tr>
 <tr valign="top">
 <td align="left">time after</td>
 <td><code>time&nbsp;after&nbsp;<i>absoluteTime</i></code></td>
 <td>Removal should occur after a specified absolute time. Absolute time may be
 specified as a number of milliseconds since the epoch (00:00:00 on 1 January
 1970) **or** as a quoted date and time formatted in
 <a href="https://docs.oracle.com/javase/8/docs/api/java/time/format/DateTimeFormatter.html#RFC_1123_DATE_TIME">RFC_1123
 date time format</a>. Either single or double quotes may be used.</td>
 </tr>
 <tr valign="top">
 <td align="left">subscriptions less than</td>
 <td><code>subscriptions&nbsp;&lt;&nbsp;<i>n</i>&nbsp;for&nbsp;<i>forPeriod</i>&nbsp;[after&nbsp;<i>afterPeriod</i>]</code></td>
 <td>Removal should occur when the topic has had less than the specified number
 (*n*) of subscriptions for a given period (*forPeriod*) of time. Optionally, an
 initial period (*afterPeriod*) may be specified by which to delay the initial
 checking of this condition. See below for period formats.</td>
 </tr>
 <tr valign="top">
 <td align="left">no updates for</td>
 <td><code>no&nbsp;updates&nbsp;for&nbsp;<i>forPeriod</i>&nbsp;[after&nbsp;<i>afterPeriod</i>]</code></td>
 <td>Removal should occur when the topic has had no updates for a given period
 (*forPeriod*) of time. Optionally, an initial period (*afterPeriod*) may be
 specified by which to delay the initial checking of this condition. See below
 for period formats.</td>
 </tr>
 <tr valign="top">
 <td align="left">no session has</td>
 <td><code>no&nbsp;session&nbsp;has&nbsp;<i>"criteria"</i>&nbsp;[for&nbsp;<i>forPeriod</i>]&nbsp;[after&nbsp;<i>afterPeriod</i>]</code></td>
 <td>Removal should occur when no sessions satisfy certain *criteria*.
 Optionally, the criteria can be required to be satisfied for a period of time
 (*forPeriod*). Optionally, an initial period (*afterPeriod*) can be specified
 to delay the initial check of the criteria. Session selection criteria are
 specified as defined in @ref md_session_filters "session filters" and must be
 surrounded by single or double quotes. See below for period formats.</td>
 </tr>
 <tr valign="top">
 <td></td>
 <td><code>this&nbsp;session&nbsp;closes</code></td>
 <td>This is a shorthand form of 'no session has' that may be used to
 indicate that the topic is to be removed when the session that created it
 closes.</td>
 </tr>
 </table>

 Time periods are specified as a number followed (with no intermediate space) by
 a single letter representing the time unit. The time unit may be 's' (seconds),
 'm' (minutes), 'h' (hours) or 'd' (days). For example, 10 minutes would be
 specified as `10m`.

 If quotes or backslashes (`\`) are required within quoted values such as
 selectors or session criteria then they may be escaped by preceding with `\`.
 The convenience method `PTDiffusionEscape` is provided to escape such
 characters in a value.

 The expression is validated only by the server and therefore if an invalid
 expression is specified it will be reported asynchronously as an error.

 ### Examples

     when time after 1518780068112

 The topic will be removed when the date and time indicated by the specified
 number of milliseconds since the epoch has passed.

     when time after "Tue, 3 Jun 2018 11:05:30 GMT"

 The topic will be removed when the specified date and time has passed.

     when time after "Tue, 3 Jun 2018 11:05:30 GMT" remove "*alpha/beta//"

 The topic alpha/beta and all topics subordinate to it will be removed when the
 specified date and time has passed.

     when subscriptions < 1 for 20m

 The topic will be removed when it has had no subscriptions for a continuous
 period of 20 minutes.

     when subscriptions < 2 for 20m after 1h

 The topic will be removed when it has had less than 2 subscriptions for a
 continuous period of 20 minutes after one hour has passed since its creation.

     when no updates for 3h

 The topic will be removed when it has had no updates for a continuous period of
 3 hours.

     when no updates for 15m after 1d

 The topic will be removed when it has had no updates for a continuous period of
 15 minutes after one day has passed since its creation.

     when this session closes

 The topic will be removed when the session that created it is closed.

     when no session has '$Principal is "Alice"'

 The topic will be removed when there is no session with the principal 'Alice'.

     when no session has '$Principal is "Alice"' for 10m

 The topic will be removed when there have been no sessions with the principal
 'Alice' for a continuous period of 10 minutes.

     when no session has 'Department is "Accounts"' for 30m after 2h

 The topic will be removed when there have been no sessions from the Accounts
 department for a continuous period of 30 minutes after 2 hours have passed
 since its creation.

     when time after "Tue, 3 Jun 2018 11:05:30 GMT" and subscriptions < 1 for 30m

 The topic will be removed when the specified date and time has passed and the
 topic has had no subscriptions for a continuous period of 30 minutes after that
 time.

     when time after "Tue, 3 Jun 2018 11:05:30 GMT" and subscriptions < 2 for 10m after 1h

 The topic will be removed when the specified date and time has passed and the
 topic has had less than 2 subscriptions for a continuous period of 10 minutes
 after that time plus one hour.

     when time after "Tue, 3 Jun 2018 11:05:30 GMT" or subscriptions < 2 for 10m after 1h

 The topic will be removed when the specified date and time has passed or the
 topic has had less than 2 subscriptions for a continuous period of 10 minutes
 after one hour from its creation.

     when time after "Tue, 3 Jun 2018 11:05:30 GMT" and (subscriptions < 2 for 10m after 1h or no updates for 20m)

 The topic will be removed when the specified date and time has passed and
 either the topic has had less than 2 subscriptions for a continuous period of
 10 minutes after that time plus one hour or it has had no updates for a
 continuous period of 20 minutes. Note that the parentheses are significant here
 as without them the topic would be removed if it had had no updates for 20
 minutes regardless of the time and subscriptions clause.

 ### Notes and restrictions on use

 The '`after`' time periods refer to the period since the topic was created or
 restored from persistence store after a server is restarted. They are designed
 as a 'grace' period after the topic comes into existence before the related
 condition starts to be evaluated. When not specified the conditions start to be
 evaluated as soon as the topic is created or restored.

 The server will evaluate conditions on a periodic basis (every few seconds) so
 the exact removal time will not be precise for low periodic granularity.

 The meaning of the '`for`' period on '`no session has`' conditions is subtly
 different from on other conditions. It does not guarantee that there has been
 no session satisfying the condition at some point between evaluations, only that
 when evaluated the given period of time has passed since it was last evaluated
 and found to have no matching sessions.

 Subscriptions is the number of subscriptions to a topic, including those that
 occur through routing or slave topics. When monitoring across a cluster the
 '`subscriptions less than`' condition is first checked on the server that owns
 the topic and if satisfied there then each cluster member is queried to check
 if the condition has also been satisfied there. The topic will only be removed
 if the total number of subscriptions across the cluster is less than that
 specified in the condition.

 Automatic topic removal is supported for both replicated topics and topics
 fanned out to secondary servers using the fan-out feature. A 'subscriptions
 less than' condition for such topics will be evaluated against the total number
 of subscriptions to the topic across the cluster and on all downstream secondary
 servers. A 'no session has' condition will consider all sessions hosted across a
 cluster and hosted by downstream secondary servers.

 @since 6.1
 */
+(NSString *)removalPropertyKey;

/**
 Key of the topic property that describes the conflation policy of the topic.
 The policy specifies how the server manages queued topic updates. Conflation is
 applied individually to each session queue.

 Conflation is the process of merging or discarding topic updates queued for a
 session to reduce the server memory footprint and network data. The server will
 conflate sessions that have a large number of queued messages to meet
 configured queue size targets. The sessions with the largest queues are
 typically slow consumers or have been disconnected – both will benefit from
 conflation. This property allows conflation behaviour to be tuned on a
 topic-by-topic basis.

 Supported policies are:

 - **off**: disables conflation for the topic. This policy disables all
   conflation for the topic, so topic updates will never be merged or discarded.
 - **conflate**: automatically conflates topic updates when back pressure is
   detected by the server. This policy is ignored for stateless topics, and for
   slave and routing topics that reference stateless topics.
 - **unsubscribe**: automatically unsubscribes the topic when back pressure is
   detected by the server. Topic updates will only be discarded if the
   PTDiffusionTopicSpecification#tidyOnSubscribePropertyKey property is set to
   "true".
 - **always**: automatically conflates topic updates as they are queued for the
   session. This is an eager policy that ensures only the latest update is
   queued for the topic, minimising the server memory and network bandwidth used
   by the session. This policy is ignored for stateless topics, and for slave
   and routing topics that reference stateless topics.

 The default policy used when the property is not specified and the topic
 type is not time series is "conflate". The default policy used when the
 property is not specified and the topic type is time series is "off".

 The "conflate" and "unsubscribe" policies are applied when the server detects
 back pressure for a session. The server configuration places limits on the data
 queued for each session. If these limits are breached, the server will conflate
 the session queue to attempt to reduce its size. If the session queue still
 exceeds the limits after conflation, the session will be terminated.

 Conflation of stateless topics is configured using server-side configuration.
 This configuration describes how topic updates should be merged. Like the
 "always" policy conflation specified this way is applied when queuing a topic
 update. The policy "off" prevents this conflation being applied. All other
 policies allow conflation specified this way to happen. The "unsubscribe"
 policy will still unsubscribe topics that use conflation specified this way.

 Conflation can be disabled on a session-by-session basis using the client
 control feature (currently unavailable for this client library). If conflation
 is disabled for a session the policy will not be applied to topic updates
 queued for the session but will be for other sessions that have conflation
 enabled.

 The policies "conflate" and "always" are not supported for
 time series topics as they would cause missing events. Attempts to enable
 these policies with time series topics will cause the creation of the
 topic to fail, reporting that the specification is invalid.

 @since 6.1
 */
+(NSString *)conflationPropertyKey;

/**
 Key of the topic property that allows the creator of a topic to extend
 `READ_TOPIC`, `MODIFY_TOPIC` and `UPDATE_TOPIC` permissions to a specific
 principal, in addition to the permissions granted by the authorisation rules in
 the security store.

 A session that has authenticated using the principal can update and remove the
 topic, so the principal can be considered the topic owner. To fetch or
 subscribe to the topic, the principal must also be granted `SELECT_TOPIC` by
 the security store rules.

 This may be used in the following cases:

 1. A session creates a topic and makes its own principal the owner.
 2. A session creates a topic and makes another principal the owner.

 The format of the property value is:

     $Principal is "<name>"

 where *name* is the name of the principal. Single quotes may be used instead of
 double quotes and special characters must be escaped. The convenience method
 `PTDiffusionEscape` is provided to escape such characters in a value.

 The purpose of this property is to allow a client to create topics on behalf of
 other users. This can be used in conjunction with #removalPropertyKey so that
 such topics are removed when there are no longer any sessions for the named
 principal.

 For example:

     PTDiffusionTopicSpecification *const specification =
         [[PTDiffusionTopicSpecification alloc] initWithType:topicType
                                                  properties:@ {
             [PTDiffusionTopicSpecification ownerPropertyKey] :
                 @"$Principal is 'myPrincipal'",
             [PTDiffusionTopicSpecification removalPropertyKey] :
                 @"when no session has '$Principal is \"myPrincipal\"' for 5s"
         }];

 @since 6.1
 */
+(NSString *)ownerPropertyKey;

/**
 Key of the topic property that allows the compression policy to be set
 on a per-topic basis.

 Compression reduces the bandwidth required to broadcast topic updates to
 subscribed sessions, at the cost of increased server CPU.

 Changes to a topic's value are published to each subscribed session as a
 sequence of topic messages. A topic message can carry the latest value or
 the difference between the latest value and the previous value (a delta).
 The compression policy determines if and how published topic messages
 are compressed. Topic messages are not exposed through the client API;
 the client library handles decompression and decodes deltas
 automatically, passing reconstructed values to the application.

 The compression policy for a topic is specified by setting this property
 to one of several values:

 - `off`
 - `low`
 - `medium`
 - `high`

 The policies are listed in the order of increasing compression and
 increasing CPU cost. `off` disables compression completely for the
 topic and requires no additional CPU; `high` compresses the topic
 messages to the smallest number of bytes, but has the highest CPU cost.
 Generally some compression is beneficial, so the default value for this
 property is `low`.

 Prior to version 6.4, only two values were allowed: `true`
 (equivalent to `medium`, and the previous default policy) and
 `false` (equivalent to `off`). These values are still
 supported.

 This property is only one factor that determines whether a topic message
 will be compressed. Other factors include:

 - Compression must be enabled in the server configuration.

 - The client library must support the server's compression
   scheme. In this release, the server supports zlib
   compression, and also allows compression to be disabled on a
   per-connector basis. From 6.4, all client libraries are
   capable of zlib compression. A JavaScript client may or may
   not support zlib compression, depending on whether the zlib
   library can be loaded. The zlib library is packaged
   separately to reduce the download size of the core library.

 @since 6.2
 */
+(NSString *)compressionPropertyKey;

/**
 Key of the topic property that specifies the topic delivery priority.

 The supported delivery priorities are:
 - **low**
 - **default**
 - **high**

 The delivery priority affects the order of topic updates sent to a
 subscribed client session. When there are multiple topic updates for
 topics with different priorities in a session's outbound queue, updates
 for "high" priority topics will be delivered first, followed by
 updates for "default" priority topics, followed by updates for
 "low" priority topics. Topic subscription and unsubscription
 notifications are also delivered according to the topic delivery
 priority.

 Using different delivery priorities is most beneficial when there is a
 large backlog of queued updates to deliver to a client session. On
 lightly loaded systems, updates typically remain in the outbound queue
 for a few milliseconds and so there is a lower chance of topic updates
 being reordered based on their priority. The backlog will be larger if
 the topic update rate is higher; the server or the client are more
 heavily loaded; the client session becomes temporarily disconnected; or
 if there is poor network connectivity between the server and the client.

 Messages from the server to the client that are not topic updates, for
 example ping requests and responses, are queued with the
 "default" delivery priority.

 @since 6.4
 */
+(NSString *)priorityPropertyKey;

/**
 Constant string representing the value to be used for boolean properties to
 specify "true".

 @since 5.9
 */
+(NSString *)truePropertyValue;

/**
 Constant string representing the value to be used for boolean properties to
 specify "false".

 @since 6.1
 */
+(NSString *)falsePropertyValue;

@end

NS_ASSUME_NONNULL_END
