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

@class PTDiffusionSessionId;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A single request from a session to subscribe to a routing topic.

 Each request received by a handler must either be routed or deferred.

 @since 6.1
 */
@interface PTDiffusionSubscriptionRoutingRequest : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Identifies the session making the subscription request.

 @since 6.1
 */
@property(nonatomic, readonly) PTDiffusionSessionId* sessionId;

/**
 Identifies the subscribed routing topic.

 @since 6.1
 */
@property(nonatomic, readonly) NSString* topicPath;

/**
 Defer the handling of this subscription request.

 * When a request is deferred, the server will discard the request, and the
 requesting session will not receive a subscription notification.

 An implementation can retain the requesting PTDiffusionSessionId and the
 routing topic's path so a routing subscription can be established at a later
 time using the PTDiffusionSubscriptionControlFeature.

 Each instance of this class can be used once. If route or defer has already
 been called for this instance, calling this method will cause a warning to be
 logged by the server, but otherwise have no effect.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException Raised if completionHandler is `nil`.

 @since 6.1
 */
-(void)deferWithCompletionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 Resolve a subscription request by providing the path of a source topic to which
 the requesting session will be subscribed via the routing topic.

 The requesting session will receive a subscription notification with the
 routing topic's path and the topic specification of the source topic. If the
 source topic is stateful, the requesting session will also be sent an update
 for the routing topic path with the current value of the source topic. The
 existence of the source topic is hidden from the requesting session. Updates to
 the source topic are forwarded to the session as if they came from the routing
 topic.

 A session that does not have `SELECT_TOPIC` or `READ_TOPIC` permission for the
 source topic cannot subscribe directly, but can be subscribed indirectly using
 this method.

 @param topicPath The topic path of the source topic to route to.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @since 6.1
 */
-(void)routeToSourceTopicPath:(NSString *)topicPath
        withCompletionHandler:(void (^)(NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
