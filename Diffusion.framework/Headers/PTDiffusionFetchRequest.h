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

@class PTDiffusionFetchResult;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A fetch request.

 This defines a fetch request to be made to the server. A new request can be
 created using the PTDiffusionTopicsFeature#fetchRequest method and modified to
 specify a range of topics and/or various levels of detail.

 The fetch request is issued to the server using one of the data type specific
 fetch methods, supplying a topic selector which specifies the selection of
 topics (e.g.
 #fetchJSONValuesWithTopicSelectorExpression:completionHandler: for JSON).

 A range is defined as being between two points of the topic tree which is
 ordered in full path name order. So an example tree order would be:
 - `a`
 - `a/b`
 - `a/c`
 - `a/c/x`
 - `a/c/y`
 - `a/d`
 - `a/e`
 - `b`
 - `b/a/x`
 - `b/b/x`
 - `c`

 The start point of a range can be specified using #fromTopicPath: or
 #afterTopicPath: and an end point using #toTopicPath: or #beforeTopicPath:.
 #fromTopicPath: and #toTopicPath: include any topic with the specified path in
 the selection, whereas #afterTopicPath: and #beforeTopicPath: are non-inclusive
 and useful for paging through a potentially large range of topics. If no start
 point is specified, the start point is assumed to be the logical beginning of
 the topic tree. Similarly, if no end point is specified, the end point is the
 logical end of the topic tree. Ranges should be within the scope indicated by
 the topic selector used when issuing the fetch.

 As a minimum, the path and type of each topic selected will be returned. It is
 also possible to request that the topic values and/or properties are returned.

 The topic types selected are naturally constrained by the data type indicated
 when the fetch is requested. So if
 PTDiffusionFetchRequest#fetchStringValuesWithTopicSelectorExpression:completionHandler:
 is used, only PTDiffusionTopicType_String topics will be selected. However, if
 PTDiffusionFetchRequest#fetchJSONValuesWithTopicSelectorExpression:completionHandler:
 is used, all types compatible with PTDiffusionJSON will be selected including
 PTDiffusionTopicType_String, PTDiffusionTopicType_Int64 and
 PTDiffusionTopicType_Double.

 To select topic types when values are not required, or to further constrain the
 selection when values are required, it is also possible to specify exactly
 which topic types to select.

 A limit on the number of results returned can be specified using #first:. This
 is advisable when the result set could potentially be large. When such a limit
 is used then the result will indicate whether more results for the same
 selection would be available via the PTDiffusionFetchResult#more property.

 The request can be sent to the server using one of the fetch methods provided
 by data type extensions. Results are returned in path order, earliest path
 first, starting from the beginning of any range specified.

 It is also possible to request results from the end of the range indicated by
 specifying a limit to the number of results using #last:. This returns up to
 the specified number of results from the end of the range, in path order. This
 is useful for paging backwards through a range of topics.

 Slave topics are supported, in that if the slave topic itself is within the
 requested selector/range and it is currently linked to a topic that should be
 selected then a result will be returned for the slave topic with the
 type/value/properties of the source topic.

 Routing topics are **not** supported, and if encountered will be ignored (i.e.
 treated as if they did not exist).

 Instances of this class are immutable and can be safely shared and reused.

 @since 6.2
 */
@interface PTDiffusionFetchRequest : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Specifies a logical start point within the topic tree.

 If specified, only results for topics with a path that is lexically 'after' the
 specified path will be returned.

 This is the non-inclusive equivalent of #fromTopicPath: and if used will
 override any previous #fromTopicPath: or #afterTopicPath: constraint.

 @param topicPath The topic path after which results are to be returned.

 @return A new fetch request derived from this fetch request but selecting only
 topics after the specified path (not inclusive).

 @since 6.2
 */
-(instancetype)afterTopicPath:(NSString *)topicPath;

/**
 Specifies a logical end point within the topic tree.

 If specified, only results for topics with a path that is lexically 'before'
 the specified path will be returned.

 This is the non-inclusive equivalent of #toTopicPath: and if used will override
 any previous #toTopicPath: or #beforeTopicPath: constraint.

 @param topicPath The topic path before which results are to be returned.

 @return A new fetch request derived from this fetch request but selecting only
 topics before the specified path (not inclusive).

 @since 6.2
 */
-(instancetype)beforeTopicPath:(NSString *)topicPath;

/**
 Specifies a logical start point within the topic tree.

 If specified, only results for topics with a path that is lexically equal to or
 'after' the specified path will be returned.

 This is the inclusive equivalent of #afterTopicPath: and if used will override
 any previous #afterTopicPath: or #fromTopicPath: constraint.

 @param topicPath The topic path from which results are to be returned.

 @return A new fetch request derived from this fetch request but selecting only
 topics from the specified path onwards (inclusive).

 @since 6.2
 */
-(instancetype)fromTopicPath:(NSString *)topicPath;

/**
 Specifies a logical end point within the topic tree.

 If specified, only results for topics with a path that is lexically equal to or
 'before' the specified path will be returned.

 This is the inclusive equivalent of #beforeTopicPath: and if used will override
 any previous #beforeTopicPath: or #toTopicPath: constraint.

 @param topicPath The topic path to which results are to be returned.

 @return A new fetch request derived from this fetch request but selecting only
 topics including and before the specified path (inclusive).

 @since 6.2
 */
-(instancetype)toTopicPath:(NSString *)topicPath;

/**
 Specifies that all properties associated with each topic's
 PTDiffusionTopicSpecification should be returned.

 @return A new fetch request derived from this fetch request but specifying that
 topic specification properties should be returned.

 @since 6.2
 */
-(instancetype)withProperties;

/**
 Specifies a maximum number of topic results to be returned from the start of
 the required range.

 If this is not specified, the number of results returned will only be limited
 by other constraints of the request.

 This should be used to retrieve results in manageable batches and prevent very
 large result sets.

 If there are potentially more results that would satisfy the other constraints,
 then the fetch result will indicate so via the PTDiffusionFetchResult#hasMore
 property.

 Either this or #last: may be specified. This will therefore override any
 previous #last: or #first: constraint.

 @param number The maximum number of results to return from the start of the
 range.

 @return A new fetch request derived from this fetch request but selecting only
 the number of topics specified from the start of the range.

 @exception NSInvalidArgumentException if number is greater than `INT32_MAX`.

 @since 6.2
 */
-(instancetype)first:(UInt32)number;

/**
 Specifies a maximum number of topic results to be returned from the end of the
 required range.

 This is similar to #first: except that the specified number of results are
 returned from the end of the range. This is useful for paging backwards through
 a range of topics. Results are always returned in topic path order (not reverse
 order).

 Either this or #first: may be specified. This will therefore override any
 previous #first: or #last: constraint.

 @param number The maximum number of results to return from the end of the
 range.

 @return A new fetch request derived from this fetch request but selecting only
 the number of topics specified from the end of the range.

 @exception NSInvalidArgumentException if number is greater than `-INT32_MIN`.

 @since 6.2
 */
-(instancetype)last:(UInt32)number;

/**
 Specifies the maximum data size of the result set.

 This may be used to constrain the size of the result. If not specified then by
 default the maximum message size for the session (as specified by
 PTDiffusionSessionConfiguration#maximumMessageSize ) is used.

 @param size The maximum size of the result set in bytes. If a value greater
 than the session's maximum message size is specified, the maximum message size
 will be used.

 @return A new fetch request derived from this fetch request but constraining
 the size of the result to the specified maximum.

 @exception NSInvalidArgumentException if size is greater than `INT32_MAX`.

 @since 6.2
 */
-(instancetype)maximumResultSize:(UInt32)size;

/**
 Specifies that only topics of the specified topic types should be returned.

 If this is not specified, #allTypes will be returned (unless constrained by
 value data type).

 This may be used instead to further constrain the results when already
 constraining by values. For example, you can use
 PTDiffusionFetchRequest#withJSONValues then specify PTDiffusionTopicType_JSON
 here to ensure that only JSON topics are returned and not those topics that are
 logically value subtypes of JSON (e.g. PTDiffusionTopicType_String).

 If already constraining by value data type then the topic types specified here
 must be compatible with the value class specified.

 Neither PTDiffusionTopicType_Slave nor PTDiffusionTopicType_Routing may be
 specified as only target topic types may be selected.

 @param topicTypes Topic types to be selected, boxed as NSNumber instances.

 @return A new fetch request derived from this fetch request but specifying that
 only topics of the specified topic types should be returned.

 @throws IllegalArgumentException if invalid topic types are specified

 @since 6.2
 */
-(instancetype)topicTypes:(NSSet<NSNumber *> *)topicTypes;

/**
 Specifies a limit on the number of results returned for each deep
 branch.

 A deep branch has a root path that has a number of parts equal to the
 `deep_branch_depth` parameter. The `deep_branch_limit` specifies the
 maximum number of results for each deep branch.

 This method is particularly useful for incrementally exploring a
 topic tree from the root, allowing a breadth-first search strategy.

 For example, given a topic tree containing the topics with the
 following paths:

 <pre>
 x/0
 x/x/1
 x/x/x/2
 y/y/y/y/3
 y/y/y/4
 z/5
 z/z/6
 </pre>

 Then

 <pre>
 PTDiffusionFetchRequest *const request =
 [session.topics.fetchRequest limitDeepBranches:1
                                          limit:1];

 [request fetchBinaryValuesWithTopicSelectorExpression:@"?.//"
                                     completionHandler:
 ^(PTDiffusionBinaryFetchResult *const result, NSError *const error)
 </pre>

 will return results with the paths `x/0`, `y/y/y/y/3`,
 and `z/5`. The application can then determine the roots of the
 tree are `x`, `y`, and `z`.

 The `deepBranchLimit` parameter can usefully be set to
 `0`. For example, given the same example topic tree,

 <pre>
 PTDiffusionFetchRequest *const request =
 [session.topics.fetchRequest limitDeepBranches:3
                                          limit:0];

 [request fetchBinaryValuesWithTopicSelectorExpression:@"?.//"
                                     completionHandler:
 ^(PTDiffusionBinaryFetchResult *const result, NSError *const error)
 </pre>

 will only return results having paths with fewer than three parts;
 namely `x/0`, and `z/5`.

 The fetch result does not indicate whether this option caused some
 results to be filtered from deep branches. It has no affect on the
 ` result. If the result set
 contains `deepBranchLimit` results for a particular deep
 branch, some topics from that branch may have been filtered.

 @param deepBranchDepth The number of parts in the root path of a
                        branch for it to be considered deep

 @param deepBranchLimit The maximum number of results to return for
                        each deep branch

 @return A new fetch request derived from this fetch request but restricting
 the number of results for deep branches.

 @since 6.4
 */
-(instancetype)limitDeepBranches:(UInt32)deepBranchDepth
                           limit:(UInt32)deepBranchLimit;

/**
 A constant set of all topic types that can be fetched.

 @since 6.2
 */
+(NSSet<NSNumber *> *)allTypes;

/**
 Sends a fetch request to the server, specifying that values should not be
 returned for selected topics.

 Results are returned for all topics matching the selector that satisfy the
 request constraints within any range defined by #fromTopicPath: /
 #afterTopicPath: and/or #toTopicPath: / #beforeTopicPath:

 @param expression Specifies a @ref md_topic_selectors "topic selector",
 evaluated at the server, which selects the topics to be fetched.

 @since 6.2
 */
-(void)fetchWithTopicSelectorExpression:(NSString *)expression
                      completionHandler:(void (^)(PTDiffusionFetchResult * _Nullable result, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
