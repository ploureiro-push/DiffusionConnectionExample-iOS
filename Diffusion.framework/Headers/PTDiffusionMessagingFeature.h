//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2015, 2018 Push Technology Ltd., All Rights Reserved.
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

@class PTDiffusionBytes;
@class PTDiffusionMessageStream;
@class PTDiffusionReceiveContext;
@class PTDiffusionRequestStream;
@class PTDiffusionSendOptions;
@class PTDiffusionTopicSelector;

@protocol PTDiffusionMessageStreamDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The Messaging feature provides a client session with messaging capabilities.
 
 The Messaging feature for a session can be obtained from the session's
 `messaging` property.
 
 Each message is delivered to a request stream registered with the server.
 Additionally, the server and other clients can send messages to be received
 using this feature.

 Messaging is distinct from the publish/subscribe PTDiffusionTopicsFeature which
 provides streams of topic updates.
 
 Messages are sent and received for a particular path. The message path provides
 a hierarchical context for the recipient.

 Message paths are distinct from topic paths. A topic with the path need not
 exist on the server; if a topic does exist, it is unaffected by messaging.
 An application can use the same path to associate messages with topics, or an
 arbitrary path can be chosen.

 For more detail,
 see: @ref md_messaging "Messaging with the Apple client library".
 
 @see PTDiffusionSession

 @since 5.6
 */
@interface PTDiffusionMessagingFeature : PTDiffusionFeature

/**
 Send a message.

 The message will be routed to any appropriately registered control handlers
 for the given message path.

 @param path The message path to send to.

 @param value The content of the message.

 @param options The send options to use.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @deprecated Since 6.2. One-way messaging has been deprecated in favor of
 request-response messaging. This method will be removed in a future release.

 @since 6.0
 */
-(void)sendWithPath:(NSString *)path
              value:(PTDiffusionBytes *)value
            options:(PTDiffusionSendOptions *)options
  completionHandler:(void (^)(NSError * _Nullable error))completionHandler
__deprecated_msg("Will be removed in a future release.");

/**
 Send a message using default send options.

 The message will be routed to any appropriately registered control handlers
 for the given message path.

 @param path The message path to send to.

 @param value The content of the message.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @deprecated Since 6.2. One-way messaging has been deprecated in favor of
 request-response messaging. This method will be removed in a future release.

 @since 6.0
 */
-(void)sendWithPath:(NSString *)path
              value:(PTDiffusionBytes *)value
  completionHandler:(void (^)(NSError * _Nullable error))completionHandler
__deprecated_msg("Will be removed in a future release.");

/**
 Add a message stream to receive messages for topics that match the given topic selector.

 When a message is received from the server, it will be passed to all message streams that have
 been added with matching selectors.
 If there is more than one match, the order in which the message streams are called is not defined.
 If there is no matching message stream, the fallback message stream will be called instead.

 @param selector The @ref md_topic_selectors "topic selector" to be evaluated locally.

 @param delegate Receiver of messages on matching message stream events.
 Used by the stream to notify of events but not retained.
 The delegate will be sent messages asynchronously on the main dispatch queue.

 @return A new stream instance configured to notify the delegate of events.
 This does not need to be retained by the caller, but should be if use with the
 `removeMessageStream:` method is required later on.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @note Since the addition of value streams for version 5.9, this method now
 returns instances of PTDiffusionMessageStream, being a new subclass of
 PTDiffusionStream.

 @deprecated Since 6.2. One-way messaging has been deprecated in favor of
 request-response messaging. This method will be removed in a future release.

 @since 5.6
 */
-(PTDiffusionMessageStream *)addMessageStreamWithSelector:(PTDiffusionTopicSelector *)selector
                                                 delegate:(id<PTDiffusionMessageStreamDelegate>)delegate
__deprecated_msg("Will be removed in a future release.");

/**
 Remove a message stream that was previously added using a topic selector or as a fallback.

 @param stream The stream to remove.

 @return `YES` if the stream was removed.

 @note If the supplied `stream` argument is `nil` or the stream has already been removed from
 this feature then calls to this method do nothing and return `NO`.

 @note Since the addition of value streams for version 5.9, this method now
 only accepts instances of PTDiffusionMessageStream, being a new subclass of
 PTDiffusionStream.

 @deprecated Since 6.2. One-way messaging has been deprecated in favor of
 request-response messaging. This method will be removed in a future release.

 @since 5.6
 */
-(BOOL)removeMessageStream:(nullable PTDiffusionMessageStream *)stream
__deprecated_msg("Will be removed in a future release.");

/**
 When a message is received from the server, it will be passed on to all message streams that have been
 added with matching selectors. If no message stream is registered with a matching selector, the
 fallback message streams that have been registered using this method will be called instead.

 Zero, one, or many fallback message streams can be set.
 If there is no fallback message stream, messages that match no other will be discarded.

 @param delegate Receiver of messages stream events not handled by an explicitly registered topic selector.
 Used by the stream to notify of events but not retained.
 The delegate will be sent messages asynchronously on the main dispatch queue.

 @return A new message stream instance configured to notify the delegate of events.
 This does not need to be retained by the caller, but should be if use with the
 `removeMessageStream:` method is required later on.

 @exception NSInvalidArgumentException Raised if the supplied `delegate` argument is `nil`.

 @note Since the addition of value streams for version 5.9, this method now
 returns instances of PTDiffusionMessageStream, being a new subclass of
 PTDiffusionStream.

 @deprecated Since 6.2. One-way messaging has been deprecated in favor of
 request-response messaging. This method will be removed in a future release.

 @since 5.6
 */
-(PTDiffusionMessageStream *)addFallbackMessageStreamWithDelegate:(id<PTDiffusionMessageStreamDelegate>)delegate
__deprecated_msg("Will be removed in a future release.");

/**
 Assign the request stream to handle requests sent to the given path.
 
 @param stream The request stream which should be mapped to receive requests
 sent to the given path.
 
 @param path The path for which received requests should be dispatched to the
 given request stream.
 
 @return The previously set request stream for the given path, or `nil` if this
 is a fresh dispatch mapping.

 @since 6.0
 */
-(nullable PTDiffusionRequestStream *)setRequestStream:(PTDiffusionRequestStream *)stream
                                               forPath:(NSString *)path;

/**
 Remove the request stream mapped to the given path.

 @param path The path for which any request stream mapping should be removed.

 @return The previously set request stream for the given path, or `nil` if there
 was not an existing dispatch mapping.

 @since 6.0
 */
-(nullable PTDiffusionRequestStream *)removeRequestStreamForPath:(NSString *)path;

@end

NS_ASSUME_NONNULL_END
