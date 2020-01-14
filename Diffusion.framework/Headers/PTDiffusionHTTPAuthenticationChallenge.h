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

@class PTDiffusionHTTPAuthenticationChallengeStatus;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief An HTTP response from a server connection request, challenging the
 client to authenticate.
 
 @see PTDiffusionHTTPAuthenticationChallengeHandler

 @since 6.0
 */
@interface PTDiffusionHTTPAuthenticationChallenge : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 The status received from the HTTP server.

 @since 6.0
 */
@property(nonatomic, readonly) PTDiffusionHTTPAuthenticationChallengeStatus* status;

/**
 The headers received from the HTTP server.
 
 @since 6.0
 */
@property(nonatomic, readonly) NSDictionary<NSString *, NSString *>* headers;

/**
 Compares the receiver to the given challenge.

 @param challenge The HTTP authentication challenge object with which to compare
 the receiver.

 @return `YES` if the challenge is identical to the receiver, otherwise `NO`.

 @note Two challenge objects are equal if they have the same statusCode and
 headers properties. The reasonPhrase property is not used when evaluating
 equality.

 @since 6.0
 */
-(BOOL)isEqualToHTTPAuthenticationChallenge:(nullable PTDiffusionHTTPAuthenticationChallenge *)challenge;

@end

NS_ASSUME_NONNULL_END
