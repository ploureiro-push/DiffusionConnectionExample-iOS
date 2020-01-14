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
#import <Diffusion/PTDiffusionStreamDelegate.h>

@class PTDiffusionContent;
@class PTDiffusionReceiveContext;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The message stream delegate protocol defines the methods to be implemented by classes
 wishing to receive messages.

 @see PTDiffusionMessagingFeature

 @deprecated Since 6.2. One-way messaging has been deprecated in favor of
 request-response messaging. This protocol will be removed in a future release.
 see: @ref md_messaging "Messaging with the Apple client library".

 @since 5.6
 */
__deprecated_msg("Will be removed in a future release.")
@protocol PTDiffusionMessageStreamDelegate <PTDiffusionStreamDelegate>

/**
 A message was received for a path handled by the topic stream.

 @param stream The message stream that received the message.

 @param path The path on which the message was received.

 @param content The content of the message.

 @param context The message context.

 @since 5.6
 */
-(void)          diffusionStream:(PTDiffusionStream *)stream
    didReceiveMessageOnTopicPath:(NSString *)path
                         content:(PTDiffusionContent *)content
                         context:(PTDiffusionReceiveContext *)context;

@end

NS_ASSUME_NONNULL_END
