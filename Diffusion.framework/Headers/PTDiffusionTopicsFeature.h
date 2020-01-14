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
#import <Diffusion/PTDiffusionTopicUpdateFeature.h>
#import <Diffusion/PTDiffusionTopicUnsubscriptionReason.h>

@class PTDiffusionFetchRequest;
@class PTDiffusionStream;
@class PTDiffusionTopicSelector;
@class PTDiffusionValueStream;

@protocol PTDiffusionFetchStreamDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The Topics feature provides a client session with the capability to receive streamed
 topic updates and/or fetch the state of topics.

 The Topics feature for a session can be obtained from the session's
 `topics` property.

 @see PTDiffusionSession

 @since 5.6
 */
@interface PTDiffusionTopicsFeature : PTDiffusionTopicUpdateFeature

/**
 Fetch the current state of topics.

 @param expression The @ref md_topic_selectors "topic selector" expression to be
 evaluated by the server.

 @param delegate Receiver of messages relating to this fetch request.
 The delegate will be sent messages asynchronously on the main dispatch queue.

 @return A new stream instance configured to notify the delegate of events.
 This does not need to be retained by the caller, but should be if later use of
 the removeStream: method is required.

 @note This method will return `nil` if the session has been closed.

 @exception NSInvalidArgumentException raised if any supplied arguments are `nil`.

 @deprecated Since 6.2. Prefer #fetchRequest instead. Unlike this method, it
 supports additional query constraints, returns type-safe values and optionally
 allows topic properties to be returned in order to fetch the current state of
 topics.

 @since 5.6
 */
-(nullable PTDiffusionStream *)fetchWithTopicSelectorExpression:(NSString *)expression
                                                       delegate:(id<PTDiffusionFetchStreamDelegate>)delegate
__deprecated_msg("Will be removed in a future release.");

/**
 Request subscription to topics.

 The session will become subscribed to each existing topic matching
 the selector unless the session is already subscribed to the topic,
 or the session does not have `READ_TOPIC` permission for the topic
 path. For each topic to which the session becomes subscribed, a
 subscription notification and initial value (if any) will be
 delivered to registered value streams before the completion handler
 is called.

 The subscription request is also retained at the server and the session
 will be automatically subscribed to newly created topics that match the
 selector (unless a subsequent unsubscription cancels the request).

 @param expression The @ref md_topic_selectors "topic selector" expression to be
 evaluated by the server.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @since 5.6
 */
-(void)subscribeWithTopicSelectorExpression:(NSString *)expression
                          completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 Request unsubscription from topics.

 @param expression The @ref md_topic_selectors "topic selector" expression to be
 evaluated by the server.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @since 5.6
 */
-(void)unsubscribeFromTopicSelectorExpression:(NSString *)expression
                            completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 When a matching update is received from the server for a topic, it will be
 passed on to all value streams that have been added with matching selectors.
 If no value stream is registered with a matching selector, the fallback value
 streams that have been registered using this method will be called instead.

 Zero, one, or many fallback value streams can be set.
 If there is no fallback value stream, updates that match no other will be
 discarded.

 @param stream Handler of value stream events not handled by an explicitly
 registered topic selector.
 The delegate associated with this stream will be sent messages asynchronously
 on the main dispatch queue.

 @exception NSInvalidArgumentException Raised if the supplied `stream` argument
 is `nil`.

 @since 5.9
 */
-(void)addFallbackStream:(PTDiffusionValueStream *)stream;

/**
 Add a value stream to receive topic updates for topics that match the given
 topic selector.

 When a value update is received from the server, it will be passed to all
 streams that have been added with matching selectors.
 If there is more than one match, the order in which the streams are called is
 not defined.
 If there is no matching stream, the fallback stream(s) will be called instead.

 @param stream Handler of value stream events against this selector.
 The delegate associated with this stream will be sent messages asynchronously
 on the main dispatch queue.

 @param selector The @ref md_topic_selectors "topic selector" to be evaluated locally.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @since 5.9
 */
-(void)addStream:(PTDiffusionValueStream *)stream
    withSelector:(PTDiffusionTopicSelector *)selector;

/**
 Add a value stream to receive topic updates for topics that match the given
 topic selector expression.

 This convenience method calls addStream:withSelector: having constructed a
 PTDiffusionTopicSelector instance using the given expression.

 @param stream Handler of value stream events against this selector.
 The delegate associated with this stream will be sent messages asynchronously
 on the main dispatch queue.

 @param expression The @ref md_topic_selectors "topic selector" expression to be
 evaluated locally.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @since 6.0
 */
-(void)          addStream:(PTDiffusionValueStream *)stream
    withSelectorExpression:(NSString *)expression;

/**
 Remove a topic or value stream that was previously added using a topic selector
 or as a fallback.

 @param stream The stream to remove.

 @return `YES` if the stream was removed.

 @note If the supplied `stream` argument is `nil` or the stream has already been
 removed from the feature then calls to this method do nothing and return `NO`.

 @since 5.9
 */
-(BOOL)removeStream:(nullable PTDiffusionStream *)stream;

/**
 Creates an unconfigured fetch request.

 If the request is invoked by calling
 PTDiffusionFetchRequest#fetchWithTopicSelectorExpression:completionHandler:
 the fetch result will provide the paths and types of all of the topics which
 the session has permission to read.

 You will usually want to restrict the query to a subset of the topic tree, and
 to retrieve the topic values and/or properties. This is achieved by applying
 one or more of the builder methods to produce more refined requests.

 For example (Swift):

     topics.fetchRequest()
         .fetchStringValues(withTopicSelectorExpression: "*A/B//")
         {
             (result: PTDiffusionStringFetchResult?, error: Error?) in
             / / TODO Handle result, if not `nil`, otherwise handle error.
         }

 @return a new unconfigured fetch request

 @since 6.2
 */
-(PTDiffusionFetchRequest *)fetchRequest;

@end

NS_ASSUME_NONNULL_END
