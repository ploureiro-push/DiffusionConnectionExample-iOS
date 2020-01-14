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
#import <Diffusion/PTDiffusionFeature.h>
#import <Diffusion/PTDiffusionTopicType.h>

@class PTDiffusionAddTopicResult;
@class PTDiffusionBytes;
@class PTDiffusionMissingTopicNotification;
@class PTDiffusionTopicSpecification;
@class PTDiffusionTopicTreeRegistration;

@protocol PTDiffusionMissingTopicHandler;
@protocol PTDiffusionTopicEventListener;
@protocol PTDiffusionTopicTreeRegistrationDelegate;

typedef NS_ENUM(NSInteger, PTDiffusionTopicControlFeatureErrorCode) {
    PTDiffusionTopicControlFeatureErrorCode_ServerFailedToAddTopic = 1,
};

NS_ASSUME_NONNULL_BEGIN

/**
 @since 5.7
 */
extern NSString *const PTDiffusionTopicControlFeatureErrorDomain;

/**
 @brief The Topic Control feature provides a client session with the ability to
 manage topics.

 The Topic Control feature for a session can be obtained from the session's
 `topicControl` property.

 @see PTDiffusionSession

 @since 5.7
 */
@interface PTDiffusionTopicControlFeature : PTDiffusionFeature

/**
 Register a handler of requests for a branch of the topic tree.

 The provided handler is called when a client subscribes or fetches using a
 topic selector that matches no existing topics. This allows a control client to
 intercede when another session requests a topic that does not exist.
 The control client may use any of the add topic methods to create the topic,
 take some other action, or do nothing, before allowing the client operation to
 proceed by calling proceed. Alternatively, the control client can call cancel
 to discard the request.

 A control client can register multiple handlers, but may only register a single
 handler for a given topic path.
 A handler will only be called for topic selectors with a path prefix that starts
 with or is equal to topicPath. If the path prefix matches multiple handlers,
 the one registered for the most specific (longest) topic path will be called.

 @param handler The handler to use for the topic tree branch identified by
 the given topicPath (unless overridden by a handler registered against a more
 specific branch).

 @param topicPath Identifies a branch of the topic tree.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will
 be `nil` and the `registration` argument will not be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.

 @note If the session is closing or closed when this method is called, the
 completion handler block will be called with an error, while the missing topic
 handler will receive no messages.

 @exception NSInvalidArgumentException If any argument is `nil`.

 @since 5.7
 */
-(void)addMissingTopicHandler:(id<PTDiffusionMissingTopicHandler>)handler
                 forTopicPath:(NSString *)topicPath
            completionHandler:(void (^)(PTDiffusionTopicTreeRegistration * _Nullable registration, NSError * _Nullable error))completionHandler;

/**
 Send a request to the server to add a topic.

 This is a convenience method which creates the topic with default details for
 the given type.

 @param path The full path of the topic to be created.

 @param type The type of topic to be created.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will
 be `nil` and `result` will be non-`nil`.
 The completion handler will be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException If any argument is `nil` or value has been
 supplied for a topic type that is not stateful.

 @since 6.1
 */
-(void)addTopicWithPath:(NSString *)path
                   type:(PTDiffusionTopicType)type
      completionHandler:(void (^)(PTDiffusionAddTopicResult * _Nullable result, NSError * _Nullable error))completionHandler;

/**
 Send a request to the server to add a topic.

 The topic will be initialized with the given value, if specified non-`nil`,
 during creation and therefore the value must be compatible with the topic type.

 @param path The full path of the topic to be created.

 @param specification Defines the topic to be created.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will
 be `nil` and `result` will be non-`nil`.
 The completion handler will be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException If any argument is `nil` or value has been
 supplied for a topic type that is not stateful.

 @since 6.1
 */
-(void)addTopicWithPath:(NSString *)path
          specification:(PTDiffusionTopicSpecification *)specification
      completionHandler:(void (^)(PTDiffusionAddTopicResult * _Nullable result, NSError * _Nullable error))completionHandler;

/**
 Register a listener to receive topic events for a branch of the topic tree.

 This allows a client to receive different events for topics.
 These events are emitted when a topic is subscribed to by one or more sessions
 after previously having no subscribers, or when a topic is no longer subscribed
 to by any session.
 These events are averaged over a small window of time to prevent rapid dispatch
 of events that ultimately return a topic to it's previous state.

 Each control session may register a single handler for a branch.

 @param listener Specifies the listener for the specified branch (unless overriden
 by a listener registered against a more specific branch).

 @param topicPath Identifies a branch of the topic tree.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will
 be `nil` and the `registration` argument will not be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.

 @note If the session is closing or closed when this method is called, the
 completion handler block will be called with an error, while the topic event
 listener will receive no messages.

 @exception NSInvalidArgumentException If any argument is `nil`.

 @deprecated Since 6.1. The main use case for this method was the removal of
 unused topics, now much better satisfied by using the
 PTDiffusionTopicSpecification#removalPropertyKey with the
 `subscriptions < n for` condition. The removal topic property is fully cluster
 aware. This method will be removed in a future release.

 @since 5.7
 */
-(void)addTopicEventListener:(id<PTDiffusionTopicEventListener>)listener
                forTopicPath:(NSString *)topicPath
           completionHandler:(void (^)(PTDiffusionTopicTreeRegistration * _Nullable registration, NSError * _Nullable error))completionHandler
__deprecated_msg("Will be removed in a future release.");

/**
 Send a request to remove one or more topics.

 All topics that match the provided topic selector that the caller has
 permission to remove will be removed.

 The selector's descendant pattern qualifier (a trailing `/` or `//`), can be
 used to remove descendant topics. If a single `/` qualifier is specified, all
 descendants of the matched topic paths will be removed. If `//` is specified,
 the matched paths and all descendants of the matched paths (complete branches)
 will be removed.

 @param expression The @ref md_topic_selectors "topic selector" expression to be
 evaluated by the server.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException If any argument is `nil`.

 @since 5.9
 */
-(void)removeDiscreteWithTopicSelectorExpression:(NSString *)expression
                               completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 Register a deferred action to remove all topics that the caller has permission
 to remove from a branch of the topic tree.

 The server will remove the topics if this session is closed.
 If several client sessions request removal of the same branch, the topics will
 not be removed until the last session is closed.

 For example, suppose two client sessions both call register expression "a/b".
 When both sessions are closed, either explicitly or by the server, the topic `a/b`
 and all of its descendants will be removed.
 This method is typically used by a client that has added one or more topics to
 tidy up and remove the topics if it is ever disconnected from the server or
 otherwise fails.

 The server will reject a request if the topicPath conflicts with existing registrations.
 Different sessions can call this method for the same topic path, but not for topic
 paths above or below existing registrations on the same branch of the topic tree.

 The last session to close must have MODIFY_TOPIC permission for topicPath.
 If this is not the case, none of the topic or its descendants will be removed.

 @param topicPath Identifies a branch of the topic tree.
 This topic and its descendants will be removed if the action is executed.

 @param delegate The delegate to be informed of lifecycle events in respect of
 this registration.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will
 be `nil` and the `registration` argument will not be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.

 @note If the session is closing or closed when this method is called, the
 completion handler block will be called with an error, while the topic tree
 registration delegate will receive no messages.

 @exception NSInvalidArgumentException If any argument is `nil`.

 @deprecated Since 6.1. The preferred method for automatic removal of topics is
 by using the PTDiffusionTopicSpecification#removalPropertyKey - whereby
 achieving the equivalent of this method the property may be specified as:
 `when this session closes remove "?<topicPath>//"`. To achieve a dependency
 upon more than one session, a condition specifying a principal name or some
 other session property could be used.
 This method will be removed in a future release.

 @since 5.7
 */
-(void)removeTopicsWithSessionForTopicPath:(NSString *)topicPath
                                  delegate:(id<PTDiffusionTopicTreeRegistrationDelegate>)delegate
                         completionHandler:(void (^)(PTDiffusionTopicTreeRegistration * _Nullable registration, NSError * _Nullable error))completionHandler
__deprecated_msg("Will be removed in a future release.");

@end

NS_ASSUME_NONNULL_END
