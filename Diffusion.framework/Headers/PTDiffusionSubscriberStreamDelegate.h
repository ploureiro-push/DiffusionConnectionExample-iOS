//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2016, 2017 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionStreamDelegate.h>
#import <Diffusion/PTDiffusionTopicUnsubscriptionReason.h>

@class PTDiffusionStream;
@class PTDiffusionTopicSpecification;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Methods implemented by classes handling streamed subscription events for
 value topics.

 This protocol defines methods to be implemented by classes wishing to receive
 streamed subscription events.
 
 @see PTDiffusionTopicsFeature

 @since 5.9
 */
@protocol PTDiffusionSubscriberStreamDelegate <PTDiffusionStreamDelegate>

/**
 Subscription notification.

 This method is called when a session is subscribed to a topic that matches the
 stream registration. This method is also called when a stream is added, for all
 of the session's subscriptions to topics that match the stream registration.

 For a given topic, this will be the initial notification, and the first
 notification following an unsubscription notification if the session
 re-subscribes to the topic.

 This method is also called for fallback streams that match the topic type when
 the session removes the last stream that selected a subscribed topic. The
 fallback stream will now receive updates for the topic, starting with an
 immediate notification of the currently cached value (if any).

 @param stream The stream that received the update.

 @param topicPath The topic path to which the session has been subscribed.

 @param specification The specification for the subscribed topic.

 @since 5.9
 */
-(void)     diffusionStream:(PTDiffusionStream *)stream
    didSubscribeToTopicPath:(NSString *)topicPath
              specification:(PTDiffusionTopicSpecification *)specification;

/**
 Unsubscription notification.

 This method is called if the session is unsubscribed from a topic that matches
 the stream registration. The stream will receive no more updates for the topic
 unless the session re-subscribes to the topic.

 This method is also called for fallback streams that match the topic type if
 the session adds the first stream that selects a subscribed topic. For these
 notifications, the reason will be
 PTDiffusionTopicUnsubscriptionReason_StreamChange. The fallback stream will no
 longer receive updates for the topic.

 @param stream The stream that received the update.

 @param topicPath The topic path from which the session has been unsubscribed.
 
 @param specification The specification for the unsubscribed topic.

 @param reason The reason for the unsubscription.

 @since 5.9
 */
-(void)         diffusionStream:(PTDiffusionStream *)stream
    didUnsubscribeFromTopicPath:(NSString *)topicPath
                  specification:(PTDiffusionTopicSpecification *)specification
                         reason:(PTDiffusionTopicUnsubscriptionReason)reason;

@end

NS_ASSUME_NONNULL_END
