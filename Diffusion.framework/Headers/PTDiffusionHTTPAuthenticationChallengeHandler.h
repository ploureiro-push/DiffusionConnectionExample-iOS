//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2017 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;

@class PTDiffusionHTTPAuthenticationChallenge;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The protocol implemented by classes providing an authentication challenge
 handler implementation for HTTP connections.

 @see PTDiffusionHTTPAuthentication
 
 @since 6.0
 */
@protocol PTDiffusionHTTPAuthenticationChallengeHandler

/**
 Called when a challenge is received. The receiver must return a response to the
 challenge.
 
 @param challenge The challenge received from the HTTP server, encapsulating
 Status-Code and headers.
 
 @return HTTP headers to be sent in response to the challenge.
 
 @exception NSInvalidArgumentException If challenge is `nil`.
 
 @since 6.0
 */
-(NSDictionary<NSString *, NSString *>*)responseForChallenge:(PTDiffusionHTTPAuthenticationChallenge *)challenge;

/**
 The maximum number of HTTP transactions permitted before authentication fails.

 @since 6.0
 */
@property(nonatomic, readonly) NSUInteger maximumConversations;

@end

NS_ASSUME_NONNULL_END
