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

@protocol PTDiffusionHTTPAuthenticationChallengeHandler;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The protocol implemented by classes providing authentication challenge
 handler implementations for HTTP connections.
 
 Objects conforming to this protocol must be supplied with the session
 configuration in order to support HTTP proxies that require authentication.

 @since 6.0
 */
@protocol PTDiffusionHTTPAuthentication <NSObject>

/**
 Create a challenge handler to be responsible for responding to authentication
 challenges during connection negotiation.

 @since 6.0
 */
-(id<PTDiffusionHTTPAuthenticationChallengeHandler>)createHandler;

@end

NS_ASSUME_NONNULL_END
