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
#import <Diffusion/PTDiffusionFeature.h>

@class PTDiffusionTopicView;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief This feature allows a client session to manage topic views.

 A topic view maps one part of the server's topic tree to another. It
 dynamically creates a set of <em>reference topics</em> from a set of
 <em>source topics</em>, based on a declarative <em>topic view
 specification</em>. The capabilities of topic views range from simple
 mirroring of topics within the topic tree to advanced capabilities that
 include publication of partial values, expanding a single topic value into
 many topics and throttling the rate of publication.

 Each reference topic has a single source topic and has the same topic type as
 its source topic. Reference topics are read-only (they cannot be updated),
 nor can they be created or removed directly. Otherwise, they behave just like
 standard topics. A client session can subscribe to a reference topic, and can
 fetch the reference topic's current value if it has one.

 The source topics of a topic view are defined by a topic selector. One or
 more reference topics are created for each source topic, according to the
 topic view. If a source topic is removed, reference topics that are derived
 from it will automatically be removed. If a topic is added that matches the
 source topic selector of a topic view, corresponding reference topics will be
 created. Removing a topic view will remove all of its reference topics.

 ### Topic view specifications

 The following is a simple topic view specification that mirrors all topics
 below the path `a` to reference topics below the path
 `b`.

 <pre>
 map ?a// to b/&lt;path(1)&gt;
 </pre>

 A topic view with this specification will map a source topic at the path
 `a/x/y/z` to a reference topic at the path `b/x/y/z`.
 The specification is simple, so the reference topic will exactly mirror the
 source topic.

 A general topic view specification comprises several parts:

 <ul>
 <li>The <em>source topic</em> clause identifies the source topics.
 <li>The <em>path mapping</em> clause determines how reference topic paths are
 derived from the source topic paths, and when expanding to more than one
 reference topic, from where the values are obtained.
 <li>The optional <em>topic property mapping</em> clause determines how
 reference topic properties are derived from source topic properties.
 <li>The optional <em>value mapping</em> clause determines how reference topic
 values are derived from source topic or expanded values.
 <li>The optional <em>throttle</em> clause constrains the rate at which each
 reference topic is updated when its source topic is updated.
 </ul>

 ### Source topic clause

 The source topic clause begins with the `map` keyword and is followed
 by a topic selector. These topic selectors follow the same parsing rules as
 other topic selectors.

 When evaluating a topic view, topics in the topic tree that match the source
 topic selector are considered, with the following exceptions:
 <ul>
 <li>Topics created through the Publisher API;
 <li>Routing topics.
 </ul>

 Both slave and reference topics are valid source topics. In paerticular,
 chaining of topic views is supported; that is, a reference topic
 created by one topic view can be the source topic of another topic view.
 Additionally, a reference topic can be the master topic of a
 slave topic, or the source topic of a routing topic subscription.

 <blockquote><em>Prefer topic views to slave topics which are now
 deprecated</em>. Individual topics can be mirrored by creating a slave topic,
 but maintaining slave topics for a branch of the topic tree quickly becomes
 tedious. A topic view will maintain such a branch automatically, and provides
 more sophisticated mapping options.
 </blockquote>

 ### Path mapping clause

 The paths of reference topics are derived from the source topic according to
 the topic view path mapping. The path mapping allows the source topic path
 and the value of the source topic to determine the path of the reference
 topic. In addition the path mapping can include <em>expand</em> directives
 which allow objects and arrays in JSON source topic values to be expanded to
 produce many reference topics.

 A path mapping clause begins with the `to` keyword and is followed by a
 path mapping template. A path mapping template is a topic path with embedded
 <em>directives</em>. Directives are evaluated when creating the topic
 reference and substituted into the topic path. Directives are delimited by
 angle brackets (`<`, `>`) and consist of the name of the
 directive and a list of parameters. The parameter list is comma-separated and
 surrounded by parentheses (`(`, `)`).

 The following path mapping directives are supported:


 #### Source path directives

 Source path directives extract a portion of the source path and are
 parameterized by the index of the start part of the source path and the
 number of parts to include. The number of parts parameter is optional – if it
 is missing, the selection extends to the end of the source path. The syntax
 is <code>&lt;path(<em>start</em>, <em>number</em>)&gt;</code>, or
 <code>&lt;path(<em>start</em>)&gt;</code> when the number of parts parameter
 is omitted.

 For example, given the source path `a/b/c/d`, the source path directive
 `&lt;path(1, 2)&gt;` is mapped to the reference topic path `b/c`, and
 the source path directive `&lt;path(2)&gt;` is mapped to the reference topic
 path `c/d`.

 #### Source value ("scalar") directives

 Source value directives are only applied to {@link TopicType#JSON JSON}
 source topics; if the path mapping contains a source value directive,
 non-JSON topics matching the source topic selector are ignored. Source value
 directives use the keyword `scalar` and are parameterized by a single
 <a href="https://tools.ietf.org/html/rfc6901"> JSON pointer</a> that extracts
 a scalar value from the source (or expanded) value. A scalar value is a
 string, a number, `true`, `false`, or `null`, that is,
 anything other than an array or a object. If the JSON pointer does not refer
 to a scalar value in the source (or expanded) value, no reference topic will
 be created. This includes cases where the JSON pointer refers to an array or
 an object), or when no part of the source value is selected.

 Deriving the reference topic paths from part of the source topic value
 effectively creates a secondary index on the value. For source value
 directives to work efficiently, the selected scalar values should be
 relatively stable. If an update to the source topic changes the selected
 scalar value, the corresponding reference topic will be removed and a new
 reference topic will be created.

 For example, given a source value of

 <pre>
 {
     "account" : "1234",
     "balance" : { "amount" : 12.57, "currency" : "USD" }
 }
 </pre>

 and the source value directive
 `currency/&lt;scalar(/balance/currency)&lt;/account/&lt;scalar(/account)&gt;`, the
 reference topic path will be `currency/USD/account/1234`.

 If the extracted value is a string, it is copied literally to the reference
 topic path. A value that contains path separators (`/`) will create a
 reference topic path with more levels than the path mapping template.

 An extracted value of `null` will be copied to the reference topic path
 as the string `"null"`.

 #### Expand value directives

 <dd>Expand value directives are only applied to {@link TopicType#JSON JSON}
 source topics; if the path mapping contains an expand value directive,
 non-JSON topics matching the source topic selector are ignored.
 <p>
 Expand value directives use the keyword `expand` and are parameterized
 by one or two <a href="https://tools.ietf.org/html/rfc6901"> JSON
 pointers</a>.
 <p>
 The first pointer indicates the element within the value to be expanded, and
 if omitted, the value is expanded from the root. Expansion of a source topic
 indicates that every direct child of the element pointed to by the expand
 pointer will be used to create a new reference topic (or provide input to
 later expand or scalar directives). For example `&lt;expand()&gt;` would
 expand every child item in the source value and `&lt;expand(/account)&gt;`
 would expand every child of the `account` value in the source value.
 The specified value could be an object, an array or even a scalar value, but
 a scalar value would expand to only a single new value.
 <p>
 The optional second parameter of the expand directive specifies a pointer to
 a scalar value within the expanded value which will be used to derive the
 path fragment of the reference topic path. If the second pointer is not
 specified or no scalar value is found for the pointer, the path fragment is
 taken from the key (if the child value is an object) or the index (if the
 child value is an array). Scalar child values will expand to a reference
 topic but will not add anything to the generated path. For example
 `expand(,/name)&gt;` would expand from the root of the source value and
 each child value path fragment would be obtained from the scalar value with
 the key `name`.
 <p>
 So if a source topic had a value of

 <pre>
 {
 "values": [1, 5, 7]
 }
 </pre>

 a path mapping of `value&lt;expand(/values)&gt;` would expand the value to
 the following reference topics:-
 <p>
 path `value0` with a value of `1`<br>
 path `value1` with a value of `5`<br>
 path `value2` with a value of `7`<br>
 <p>
 Expand directives can be nested (i.e. there can be more than one expand
 directive in a path mapping). In this case a second expand directive will use
 the value from the previous expand as its source (root) value and not the
 value of the source topic. This also applies to scalar directives that follow
 an expand directive.
 <p>
 If expansion causes more than one mapping to the same topic path, only the
 first encountered will be created and updated.
 <p>
 Expanding source topic values effectively creates secondary indices on the
 value. For expanded value directives to work efficiently, the value selected
 for expansion should be relatively stable in terms of the children it
 contains. If an update to the source topic changes the children of the
 expanded value, then corresponding reference topics will be removed and
 created. Updates should generally be limited to changing values within the
 expanded values.</dd>

 ### Topic property mapping clause

 The topic specification of a reference topic is derived from the topic
 specification of the source topics. A reference topic has the same topic
 type as its source topic.

 The topic properties of a reference topic are derived from the source topic.
 Some topic properties can be tuned using the optional topic property mapping
 clause. The following table describes the behavior for each topic property.

 <table>
 <tr>
 <th style="text-align:left;">Source topic property</th>
 <th>Reference topic specification default</th>
 <th>Can be set by topic property mapping?</th>
 <th>Notes</th>
 </tr>
 <tr>
 <th style="text-align:left;">`compressionPropertyKey`</th>
 <td>Copied from source topic specification</td>
 <td>Yes</td>
 <td></td>
 </tr>
 <tr>
 <th style="text-align:left;">`conflationPropertyKey`</th>
 <td>Copied from source topic specification</td>
 <td>Yes</td>
 <td></td>
 </tr>
 <tr>
 <th style="text-align:left;">`dontRetainValuePropertyKey`</th>
 <td>Copied from source topic specification</td>
 <td>Yes</td>
 <td></td>
 </tr>
 <tr>
 <th style="text-align:left;">`ownerPropertyKey`</th>
 <td>Not set</td>
 <td>No</td>
 <td></td>
 </tr>
 <tr>
 <th style="text-align:left;">`persistentPropertyKey`</th>
 <td>Not set</td>
 <td>No</td>
 <td>Reference topics are not persisted. Topic views are persisted, so a
 reference topic will be recreated on server restart if its source is
 persistent.</td>
 </tr>
 <tr>
 <th style="text-align:left;">`priorityPropertyKey`</th>
 <td>Copied from source topic specification</td>
 <td>Yes</td>
 <td></td>
 </tr>
 <tr>
 <th style="text-align:left;">`publishValuesOnlyPropertyKey`</th>
 <td>Copied from source topic specification</td>
 <td>Yes</td>
 <td></td>
 </tr>
 <tr>
 <th style="text-align:left;">`removalPropertyKey`</th>
 <td>Not set</td>
 <td>No</td>
 <td>Reference topics cannot be removed directly.</td>
 </tr>
 <tr>
 <th style="text-align:left;">`schemaPropertyKey`</th>
 <td>Copied from source topic specification</td>
 <td>No</td>
 <td>A recordV2 reference topic has the same
 schema as its source topic.</td>
 </tr>
 <tr>
 <th style="text-align:left;">`slaveMasterTopicPropertyKey`</th>
 <td>Not set</td>
 <td>No</td>
 <td>If a reference topic has a slave topic as its source topic, it indirectly
 references the slave's master topic.</td>
 </tr>
 <tr>
 <th style="text-align:left;">`tidyOnSubscribePropertyKey`</th>
 <td>Copied from source topic specification</td>
 <td>Yes</td>
 <td></td>
 </tr>
 <tr>
 <th style="text-align:left;">`timeSeriesEventValueTypePropertyKey`</th>
 <td>Copied from source topic specification</td>
 <td>No</td>
 <td>A time series reference topic has the same
 value type as its source topic.</td>
 </tr>
 <tr>
 <th style="text-align:left;">`timeSeriesRetainedRangePropertyKey`</th>
 <td>Copied from source topic specification</td>
 <td>Yes, with restrictions</td>
 <td>A topic property mapping cannot increase the time series retained range
 by overriding the `TIME_SERIES_RETAINED_RANGE` property. The retained
 range of a reference time series topic will be constrained to be no greater
 than that of its source topic.</td>
 </tr>
 <tr>
 <th style="text-align:left;">`timeSeriesSubscriptionRangePropertyKey`</th>
 <td>Copied from source topic specification</td>
 <td>Yes</td>
 <td></td>
 </tr>
 <tr>
 <th style="text-align:left;">`validateValuesPropertyKey`</th>
 <td>Not set</td>
 <td>No</td>
 <td>A reference topic reflects updates to its source topic. It cannot reject
 updates.</td>
 </tr>
 </table>

 A topic property mapping clause begins with the keywords
 `with properties` and consists of a comma-separated list of topic
 property keys and values, each separated by a colon. For example, the
 following topic view specification maps all topics below the path
 `a` to reference topics below the path `b`, and
 disables both conflation and compression for the reference topics.

 <pre>
 map ?a// to b/&lt;path(1)&gt; with properties 'CONFLATION':'off', 'COMPRESSION':'false'
 </pre>

 ### Topic value mapping

 By default, a reference topic's value is a copy of the source topic value, or
 part of the source value produced by an expand path mapping directive. For
 `JSON` source topics, the optional topic value mapping clause can be applied to
 extract part of the source value, or to further refine the value produced by
 the expand directive.

 A topic value mapping begins the keyword `as` and is followed by a value
 directive. A value directive is delimited by angle brackets (`<`, `>`), and
 consists of the `value` keywords and a single JSON pointer parameter. The JSON
 pointer selects the part of the source value to copy.

 For example, given a source value of

 <pre>
 {
     "account" : "1234",
     "balance" : { "amount" : 12.57, "currency" : "USD" }
 }
 </pre>

 and the value mapping clause `as <value(/balance)>`, the
 reference topic value will be

 <pre>
 {
     "amount" : 12.57,
     "currency" : "USD"
 }
 </pre>

 Value mappings that follow expand directives apply to the expanded value and
 not the source topic value.

 Topic value mappings only alter the reference topic value; only the path
 mapping determines whether a reference topic should exist. If the topic value
 mapping's JSON pointer fails to select anything from the source topic value,
 the reference topic will have the JSON value `null`.

 Topic value mappings are often used with path value mappings to avoid repeating
 information in the path and the value. For example:

 <pre>
 map ?accounts// to balances/&lt;scalar(/account)&gt; as &lt;value(/balance)&gt;
 </pre>

 ### Throttle clause

 The optional throttle clause can be used to constrain the rate at which a
 reference topic is updated when its source topic is updated. The primary
 application of a throttle clause is to restrict the number of updates sent to
 reference topic subscribers, reducing network utilization or the processing
 each subscriber must do. Throttling also restricts the rate at which client
 sessions can observe changes to reference topic values using the fetch API.
 The throttle clause has the form:

 <pre>
 throttle to <em>X</em> updates every <em>period</em>
 </pre>

 where <em>X</em> is a positive integer, and <em>period</em> is a positive
 integer followed by a time unit which is one of `seconds`,
 `minutes`, or `hours`. For example, the following topic
 view specification maps all topics below the path `a` to reference
 topics below the path `b`, but updates the value of each reference
 topic at most twice every five seconds:

 <pre>
 map ?a// to b/&lt;path(1)&gt; throttle to 2 updates every 5 seconds
 </pre>

 To improve readability, the throttling clause allows `1 update` as
 an alternative to `1 updates`, and `every second` as an
 alternative to `every 1 seconds` (and so on, for other time
 units). For example, the following topic view specification maps all topics
 below the path `a` to reference topics below the path
 `b`, but updates the value of each reference topic at most once
 every hour:

 <pre>
 map ?a// to b/&lt;path(1)&gt; throttle to 1 update every minute
 </pre>

 The throttle clause is only applied when a source topic is updated more
 frequently than the configured rate. If a source topic is updated less
 frequently, updates are passed on unconstrained. If the rate is exceeded, a
 reference topic will not be updated again until the configured period has
 expired. At this time, the reference topic will be updated based on the
 source topic updates that happened in the interim, and a single value will be
 published. Thus, a throttle clause provides <em>topic-scoped conflation</em>.

 The throttle clause is ignored for time series topics because time series
 updates do not support efficient conflation. Updates to source time series
 topics are passed on immediately to the corresponding reference topics,
 regardless of any throttle clause.

 ### Escaping and quoting special characters

 Each part of a topic view expression has characters with special
 significance. Source topic clauses and path mapping clauses are delimited by
 white space. Directives in path and topic property mapping clauses are
 delimited by the `<` and `>` characters, and each directive
 parameter is terminated by `,` or `)`. Topic property mapping
 clauses are delimited by white space, and the `:` and `,`
 characters.

 Sometimes a topic view must refer to or generate topics with paths that
 containing special characters, or use a JSON pointer containing special
 characters. The escape sequence `\x` can be used to literally insert
 any character `x`, with a one exception: `\/` cannot be used in
 path fragments since the path delimiter `/` is always significant.

 Here is an example topic view expression containing escape sequences. It maps
 the topic path `a topic` a reference topic with the path
 `another topic`.

 <pre>
 map a\ topic to another\ topic
 </pre>

 Here is an example with a source value directive that uses the JSON pointer
 `/x()/y` to extract the target path from the source value. The
 `)` character in the JSON pointer must be escaped so it is not treated
 as the end of the parameter list.

 <pre>
 map ?a// to &lt;scalar(/x(\)/y)&gt;
 </pre>

 To insert `\`, the escape sequence `\\` must be used.

 There is no need to escape white space in JSON pointers directive parameters.
 However, white space is significant. For example, the following expressions
 have different topic value mapping clauses since the JSON pointer in the
 second expression is `"/x "`; that is, it has a trailing space:

 <pre>
 map a to b as &lt;value(/x)&gt;
 map a to b as &lt;value(/x )&gt;
 </pre>

 Instead of using escape sequences, white space characters can be included in
 source topic clauses and path mapping clauses using quotes. A clause is
 quoted by wrapping it in single quote (`'`) or double quote (`"`)
 characters. For example:

 <pre>
 map "a topic" to "another topic"
 </pre>

 Within a quoted clause, quotes of the same type must be escaped:

 <pre>
 map 'alice\'s topic' to 'bob\'s topic'
 </pre>

 For consistency, the values in topic property mapping clauses can be escaped
 or quoted. However, there is no need to do so because none of the valid
 values for the mappable properties contain special characters.

 ### Dealing with topic path conflicts

 Reference topics have a lower priority than normal topics created through the
 API, including replicas of normal topics created by topic replication or
 fan-out. A reference topic will only be created if no topic or reference topic
 is already bound to its derived topic path.

 Topic views have a precedence based on order of creation. If two topic views
 define mappings the same topic path, the earliest-created topic view will
 create a reference topic. If a topic view is updated, it retains its original
 precedence.

 ### Topic view persistence and replication

 Reference topics are neither replicated nor persisted. They are created and
 removed based on their source topics. However, topic views are replicated and
 persisted. A server that restarts will restore topic views during recovery.
 Each topic view will then create reference topics based on the source topics
 that have been recovered.

 The server records all changes to topic views in a persistent store. Topic
 views are restored if the server is started.

 If a server belongs to a cluster, topic views will be replicated to each
 server in the cluster. Topic views are evaluated locally within a server.
 Replicated topic views that select non-replicated source topics can create
 different reference topics on each server in the cluster.

 ### Access control

 To list the topic views a session needs `READ_TOPIC_VIEW` permission.
 To create or remove a topic view a session needs `MODIFY_TOPIC_VIEW`
 permission, `SELECT_TOPIC` permission for the prefix of the source topic
 selector and `MODIFY_TOPIC` permission for the prefix of the path mapping.

 ### Accessing the feature

 The Topic Views feature for a session can be obtained from the session's
 `topicViews` property.

 @see PTDiffusionSession

 @since 6.3
 */
@interface PTDiffusionTopicViewsFeature : PTDiffusionFeature

/**
 Create a new named topic view.

 If a view with the same name already exists the new view will update the
 existing view.

 @param name The name of the view.

 @param specification The specification of the view using the DSL.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException If any argument is `nil`.

 @since 6.3
 */
-(void)createTopicViewWithName:(NSString *)name
                 specification:(NSString *)specification
             completionHandler:(void (^)(PTDiffusionTopicView * _Nullable view, NSError * _Nullable error))completionHandler;

/**
 List all the topic views that have been created.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil` and `views` will contain a list of views sorted by their
 creation order. The completion handler will be called asynchronously on the
 main dispatch queue.

 @exception NSInvalidArgumentException If completionHandler is `nil`.

 @since 6.3
 */
-(void)listTopicViewsWithCompletionHandler:(void (^)(NSArray<PTDiffusionTopicView *> * _Nullable views, NSError * _Nullable error))completionHandler;

/**
 Remove a named topic view if it exists.

 If the named view does not exist then the operation is considered successful
 and the completion handler is called accordingly.

 @param name The name of the view.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException If any argument is `nil`.

 @since 6.3
 */
-(void)removeTopicViewWithName:(NSString *)name
             completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
