//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2017, 2018 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionTopicTreeRegistrationDelegate.h>

@class PTDiffusionContent;
@class PTDiffusionReceiveContext;
@class PTDiffusionSessionId;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Handler for receiving messages from clients, with associated content and
 optional information.
 
 @see PTDiffusionMessagingControlFeature

 @deprecated Since 6.2. One-way messaging has been deprecated in favor of
 request-response messaging. This protocol will be removed in a future release.
 see: @ref md_messaging "Messaging with the Apple client library".

 @since 6.0
 */
__deprecated_msg("Will be removed in a future release.")
@protocol PTDiffusionMessageDelegate <PTDiffusionTopicTreeRegistrationDelegate>

/**
 Receives messages sent from client sessions using a path.
 
 The path will be one within the branch for which the handler was registered.

 @param registration The topic tree registration for which this handler applies.
 
 @param sessionId Identifies the client session that sent the message.
 
 @param path The message path that the message was sent to.
 
 @param content The message content sent by the client.
 
 @param context Receive context (including headers) associated with the message.

 @since 6.0
 */
-(void)diffusionTopicTreeRegistration:(PTDiffusionTopicTreeRegistration *)registration
              hadMessageFromSessionId:(PTDiffusionSessionId *)sessionId
                                 path:(NSString *)path
                              content:(PTDiffusionContent *)content
                              context:(PTDiffusionReceiveContext *)context;

@end

NS_ASSUME_NONNULL_END
