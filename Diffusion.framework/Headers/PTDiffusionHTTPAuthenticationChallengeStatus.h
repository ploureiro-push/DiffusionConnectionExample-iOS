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

NS_ASSUME_NONNULL_BEGIN

/**
 @brief An HTTP Status received as part of an authentication challenge.
 
 @see PTDiffusionHTTPAuthenticationChallenge

 @since 6.0
 */
@interface PTDiffusionHTTPAuthenticationChallengeStatus : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 The server responded to the connection request with HTTP Status-Code 401.
 
 @note The reasonPhrase property for the static instance returned by this
 method will always be `nil`.
 
 @since 6.0
 */
+(instancetype)unauthorized;

/**
 The server responded to the connection request with HTTP Status-Code 407.

 @note The reasonPhrase property for the static instance returned by this
 method will always be `nil`.

 @since 6.0
 */
+(instancetype)proxyAuthenticationRequired;

/**
 The HTTP Reason-Phrase provided by the server with the response that generated
 this status.

 @since 6.0
 */
@property(nonatomic, readonly, nullable) NSString* reasonPhrase;

/**
 Compares the receiver to the given status.

 @param status The HTTP authentication challenge status object with which to
 compare the receiver.

 @return `YES` if the status is identical to the receiver, otherwise `NO`.

 @note Two status objects are equal if they mean the same thing.
 The reasonPhrase property is not used when evaluating equality.

 @since 6.0
 */
-(BOOL)isEqualToHTTPAuthenticationChallengeStatus:(nullable PTDiffusionHTTPAuthenticationChallengeStatus *)status;

@end

NS_ASSUME_NONNULL_END
