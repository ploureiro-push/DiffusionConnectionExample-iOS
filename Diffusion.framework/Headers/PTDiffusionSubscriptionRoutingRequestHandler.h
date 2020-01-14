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
#import <Diffusion/PTDiffusionStreamDelegate.h>

@class PTDiffusionSubscriptionRoutingRequest;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Methods implemented by classes handling streamed subscription routing
 requests.

 This protocol defines methods to be implemented by classes wishing to provide
 routing functionality.

 @see PTDiffusionSubscriptionControlFeature

 @since 6.1
 */
@protocol PTDiffusionSubscriptionRoutingRequestHandler <PTDiffusionStreamDelegate>

/**
 Notification of a request to subscribe to a specific routing topic.

 @param stream The stream that received the update.

 @param request The request, which must be replied to or deferred.

 @since 6.1
 */
-(void)                  diffusionStream:(PTDiffusionStream *)stream
    didReceiveSubscriptionRoutingRequest:(PTDiffusionSubscriptionRoutingRequest *)request;

@end

NS_ASSUME_NONNULL_END
