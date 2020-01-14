//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2015, 2019 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;

/**
 The type of a topic.

 @see PTDiffusionTopicSpecification

 @since 5.6
 */
typedef NS_ENUM(NSUInteger, PTDiffusionTopicType) {
    /**
     Slave Topic.

     A topic that references another topic (the master topic). It re-publishes
     the master topic's data through an alternative topic path.

     A session cannot tell that it is subscribed to a slave topic. A session
     requesting details of a slave topic will receive the details of the
     master topic. A session subscribing to the slave topic will receive all
     updates to the master topic. The slave topic itself can not be updated.

     Any number of slave topics may reference the same master topic.

     The master topic may not be another slave topic, a routing topic, a
     stateless topic or any topic created using the classic Publisher API.
     If any such topic exists at the master path when creating a slave topic,
     the slave is created in an 'unbound' state (see below).

     From release 6.0 the master topic does not need to exist at the time a
     slave topic is created. In this case, the slave topic is created in an
     'unbound' state and is not visible to subscribers. If the master topic is
     then created, all unbound slaves that reference it become bound to it, and
     sessions that have requested subscription to the slave become unsubscribed.
     If an incompatible topic type is created at a path which unbound slaves
     refer to, the slaves remain unbound.

     Slave topics are not removed when a master topic that they are bound to is
     removed. If a master topic is removed that has bound slaves, those slaves
     become unbound and any sessions subscribing to them would be unsubscribed.
     Such an unbound slave can rebind to another topic created with the same
     master path later. Slave topics must be explicitly removed.

     The session creating a slave topic must have READ_TOPIC permission to the
     master topic path.

     @note The [PTDiffusionTopicSpecification slaveMasterTopicPropertyKey]
     property must be provided when creating a slave topic using a topic
     specification.

     @deprecated Since 6.4. Topic views should be used in preference to slave
     topics. Individual topics can be mirrored by creating a slave topic, but
     maintaining slave topics for a branch of the topic tree quickly becomes
     tedious. A topic view will maintain such a branch automatically, and
     provides more sophisticated mapping options. Slave topics will be removed
     in a future release.

     @since 5.7
     */
    PTDiffusionTopicType_Slave __deprecated_enum_msg("Will be removed in a future release.") = 7,

    /**
     Routing Topic.

     A topic that can reference different source topics for different sessions.

     Each subscription to a routing topic is routed to a source topic. Updates
     to the source topic are routed back to the subscriber and appear to come
     from the routing topic.

     The result is that a session may subscribe to a topic which is in reality
     supported by another topic and the mapping of the routing topic to the
     actual topic can be different for each session.

     As an example, you may wish for all sessions to subscribe to a topic
     called "Prices" but depending upon the client type the actual topic could
     differ (Prices/Discount, Prices/Standard etc).

     An instance of this topic may map any number of sessions to any number of
     different 'real' topics. Each real topic must be either a topic that
     maintains state or a Stateless topic.

     From the point of view of a session subscribing to such a topic, a
     routing topic appears to be a normal topic but it has no state of its own
     and cannot be updated.

     The mapping of sessions to source topics is performed by a control client
     session using the Subscription Control feature. When a session subscribes
     to the routing topic the control client is requested to provide the topic
     that the client is to be subscribed to. If there is no control client
     available to handle subscriptions at the time a session subscribed, the
     session will not be subscribed to the topic.

     Alternatively, the routing can be determined by a user-written Java class
     (deployed on the server) which will be invoked to define the mapping of
     the topic to another data topic when a session subscribes.

     When a source topic is removed that is mapped to from a routing topic then
     any session that were mapped to that source topic will be unsubscribed from
     the routing topic.

     @since 5.7
     */
    PTDiffusionTopicType_Routing = 12,

    /**
     Topic that stores and publishes binary values. Based on the
     PTDiffusionBinary data type.

     Supports delta-streams.

     @since 5.7
     */
    PTDiffusionTopicType_Binary = 13,

    /**
     Topic that stores and publishes JSON (JavaScript Object Notation) values.
     Based on the PTDiffusionJSON data type.

     Supports delta-streams.

     @since 5.7
     */
    PTDiffusionTopicType_JSON = 14,

    /**
     Topic that stores and publishes IEEE 754 double-precision floating point
     numbers. Based on the double data type.

     Supports `nil` values.

     The topic does not support delta-streams — only complete values are
     transmitted.

     @since 6.0
     */
    PTDiffusionTopicType_Double = 15,

    /**
     Topic that stores and publishes 64-bit integer values. Based on the int64
     data type.

     Supports `nil` values.

     The topic does not support delta-streams — only complete values are
     transmitted.

     @since 6.0
     */
    PTDiffusionTopicType_Int64 = 16,

    /**
     Topic that stores and publishes string values. Based on the string data
     type.

     Supports `nil` values.

     Supports delta-streams.

     @since 6.0
     */
    PTDiffusionTopicType_String = 17,

    /**
     A time series is a sequence of events. Each event contains a value and has
     server-assigned metadata comprised of a sequence number, timestamp, and
     author.

     A time series topic allows sessions to access a time series that is
     maintained by the server. A time series topic has an associated event data
     type that determines the type of value associated with each event.

     ## Retained range

     The [PTDiffusionTopicSpecification timeSeriesSubscriptionRange] property
     configures the range of historic events retained by a time series topic.
     If the property is not specified, a time series topic will retain the ten
     most recent events.

     ## Subscription range

     The [PTDiffusionTopicSpecification timeSeriesSubscriptionRange] property
     configures a time series topic to send a range of historic events from the
     end of the time series to new subscribers. This is a convenient way to
     synchronize new subscribers without requiring the use of a range query.

     By default, new subscribers will be sent the latest event if delta streams
     are enabled and no events if delta streams are disabled.

     ## Mandatory properties

     The [PTDiffusionTopicSpecification timeSeriesEventValueType] property must
     be provided when creating a time series topic.

     @since 6.0
     */
    PTDiffusionTopicType_TimeSeries = 18,

    /**
     Topic that stores and publishes data in the form of records and fields.

     Supports delta-streams.

     @since 6.0
     */
    PTDiffusionTopicType_RecordV2 = 19,

    /**
     A topic type that is unsupported by the session.

     @since 6.1
     */
    PTDiffusionTopicType_Unknown = 20,
};

NS_ASSUME_NONNULL_BEGIN

/**
 Returns a localized string representation of the given topic type.

 @param topicType The topic type for which a description is to be returned.

 @since 5.7
 */
NSString* PTDiffusionTopicTypeToString(PTDiffusionTopicType topicType);

/**
 Returns the name of this topic type constant, exactly as declared in its
 enum declaration in the Diffusion API for Java.

 @param topicType The topic type for which the name is to be returned.

 @since 5.9
 */
NSString* PTDiffusionTopicTypeToName(PTDiffusionTopicType topicType);

NS_ASSUME_NONNULL_END
