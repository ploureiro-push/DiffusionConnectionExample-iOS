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

@protocol PTDiffusionHTTPAuthentication;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Connection details for an HTTP proxy to be tunneled through in order to
 reach the Diffusion server.
 
 @see PTDiffusionSessionConfiguration

 @since 6.0
 */
@interface PTDiffusionHTTPProxyConfiguration : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 @param host The host name of the HTTP proxy.
 
 @param port The port of the HTTP proxy.
 
 @exception NSInvalidArgumentException If host is `nil`.

 @since 6.0
 */
-(instancetype)initWithHost:(NSString *)host
                       port:(UInt32)port NS_DESIGNATED_INITIALIZER;

/**
 @param host The host name of the proxy.

 @param port The TCP port of the proxy.
 
 @param authentication The provider to be used if the proxy requests authentication.

 @exception NSInvalidArgumentException If either host or authentication is `nil`.

 @see PTDiffusionBasicHTTPProxyAuthentication

 @since 6.0
 */
-(instancetype)initWithHost:(NSString *)host
                       port:(UInt32)port
             authentication:(id<PTDiffusionHTTPAuthentication>)authentication NS_DESIGNATED_INITIALIZER;

/**
 The host name of the proxy.

 @since 6.0
 */
@property(nonatomic, readonly) NSString* host;

/**
 The TCP port of the proxy.

 @since 6.0
 */
@property(nonatomic, readonly) UInt32 port;

/**
 The provider to be used if the proxy requests authentication.

 @see PTDiffusionBasicHTTPProxyAuthentication

 @since 6.0
 */
@property(nonatomic, readonly, nullable) id<PTDiffusionHTTPAuthentication> authentication;

/**
 Compares the receiver to the given configuration.

 @param configuration The HTTP proxy configuration object with which to compare
 the receiver.

 @return `YES` if the configuration is identical to the receiver, otherwise `NO`.

 @since 6.0
 */
-(BOOL)isEqualToHTTPProxyConfiguration:(nullable PTDiffusionHTTPProxyConfiguration *)configuration;

@end

NS_ASSUME_NONNULL_END
