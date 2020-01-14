//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2016 Push Technology Ltd., All Rights Reserved.
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
 @brief Notification that a session has made a request using a selector that does
 not match any topics.

 Processing of the initial request will be halted until proceed is called, at
 which point the selector will be resolved against the topic tree again.

 If after calling proceed the selector still does not match against any topics,
 no further notifications will be provided.

 Should cancel be called, or the notification time out, the request will be discarded.
 The requesting session will not be notified that their request has been cancelled.

 @see PTDiffusionMissingTopicHandler

 @since 5.7
 */
@interface PTDiffusionMissingTopicNotification : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Cancel the client request on the server.

 Calling this will prevent any further processing of the request.
 For subscription requests, the topic selector will be discarded.
 The client session will not become subscribed to topics that match the selector
 if they are added later.

 @deprecated Since 6.4. This is only useful when using the deprecated method
 PTDiffusionTopicsFeature::fetchWithTopicSelectorExpression:delegate:. This will
 be removed in a future release.

 @since 5.7
 */
-(void)cancel
__deprecated_msg("Will be removed in a future release.");

/**
 Instruct the server to complete processing of the session request.

 This may be called after additional operations (such as adding topics) have been
 performed, to allow the requested selector to be resolved against the updated
 topic tree.

 For subscription requests, the topic selector will be added to the client's topic
 selections. This will cause the client session to become subscribed to topics
 that match the selector if they are added later.

 @since 5.7
 */
-(void)proceed;

/**
 The identity of the client session that made the request.

 @since 5.7
 */
@property(nonatomic, readonly) PTDiffusionSessionId* sessionId;

/**
 The topic selector expression that triggered this notification.

 @since 5.7
 */
@property(nonatomic, readonly) NSString* topicSelectorExpression;

@end

NS_ASSUME_NONNULL_END
