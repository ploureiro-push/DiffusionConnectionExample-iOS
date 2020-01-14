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
#import <Diffusion/PTDiffusionHTTPAuthentication.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Provider of responses to basic authentication challenges from HTTP proxies.
 
 @see PTDiffusionHTTPProxyConfiguration

 @since 6.0
 */
@interface PTDiffusionBasicHTTPProxyAuthentication : NSObject <PTDiffusionHTTPAuthentication>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 @param username The username to respond with.
 
 @param password The password to respond with.
 
 @exception NSInvalidArgumentException If either username or password is `nil`.

 @since 6.0
 */
-(instancetype)initWithUsername:(NSString *)username
                       password:(NSString *)password NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
