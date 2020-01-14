//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2015, 2019 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;

@class PTDiffusionCredentials;
@class PTDiffusionHTTPProxyConfiguration;

@protocol PTDiffusionSessionReconnectionStrategy;

extern const NSTimeInterval PTDiffusionSessionDefaultReconnectionTimeout;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A session configuration defines behavior and policies to use when connecting to Diffusion.
 
 @see PTDiffusionSession

 @since 5.6
 */
@interface PTDiffusionSessionConfiguration : NSObject <NSCopying, NSMutableCopying>

/**
 Returns a session configuration object initialized with the given principal and credentials.

 @param principal The security principal to use when opening the session.
 A value of `nil` dictates that no principal name will be associated with the session,
 indicating anonymous authentication.

 @param credentials The security credentials to use when opening the session.
 A value of `nil` dictates that no credentials will be used when authenticating the session.

 @since 5.6
 */
-(instancetype)initWithPrincipal:(nullable NSString *)principal
                     credentials:(nullable PTDiffusionCredentials *)credentials;

/**
 The security principal to use when opening the session.
 
 A value of `nil` dictates that no principal name will be associated with the session,
 indicating anonymous authentication.

 @since 5.6
 */
@property(nonatomic, nullable, readonly, copy) NSString *principal;

/**
 The security credentials to use when opening the session.
 
 A value of `nil` dictates that no credentials will be used when authenticating the session.

 @since 5.6
 */
@property(nonatomic, nullable, readonly, copy) PTDiffusionCredentials *credentials;

/**
 The reconnection timeout in seconds that will be used on connection failure.
 
 The reconnection timeout boxed by this number is accessed as a double representing an NSTimeInterval.
 
 A value of `nil` or a negative boxed value both dictate that reconnection will be disabled.

 @since 5.6
 */
@property(nonatomic, nullable, readonly) NSNumber* reconnectionTimeout;

/**
 The reconnection strategy that will be used on connection failure.
 
 A value of `nil` when a valid reconnectionTimeout has been set dictates that the default
 reconnection strategy will be employed.

 @since 5.6
 */
@property(nonatomic, nullable, readonly) id<PTDiffusionSessionReconnectionStrategy> reconnectionStrategy;

/**
 The default recovery buffer size in messages.
 
 @see recoveryBufferSize

 @since 6.0
 */
+(NSUInteger)defaultRecoveryBufferSize;

/**
 The recovery buffer size in messages; can be zero.
 
 If the server is configured to support reconnection, a session established with
 a non-zero reconnection time retains a buffer of sent messages.
 If the session disconnects and reconnects, this buffer is used to re-send
 messages that the server has not received.
 
 Higher values increase the chance of successful reconnection, but increase the
 per-session memory footprint.
 
 @see defaultRecoveryBufferSize
 
 @since 6.0
 */
@property(nonatomic, readonly) NSUInteger recoveryBufferSize;

/**
 The default connection timeout (2 seconds).
 
 @since 5.7
 */
+(NSTimeInterval)defaultConnectionTimeout;

/**
 The lowest value that the maximum message size can be set to in bytes.

 @see maximumMessageSize
 
 @since 6.0
 */
+(NSUInteger)maximumMessageSizeMinimum;

/**
 The default maximum message size in bytes. The maximum message size limits the
 size of received messages. This default value is NSUIntegerMax, so the message
 size is effectively unlimited.

 @see maximumMessageSize
 
 @since 6.0
 */
+(NSUInteger)defaultMaximumMessageSize;

/**
 The default maximum outbound queue size in messages.

 @see maximumQueueSize

 @since 6.0
 */
+(NSUInteger)defaultMaximumQueueSize;

/**
 The maximum message size in bytes.

 This constrains the size of messages that may be received from the server and
 thus the size of any content that can be received. The limit protects against
 unexpectedly large messages.

 @see defaultMaximumMessageSize
 @see maximumMessageSizeMinimum

 @since 6.0
 */
@property(nonatomic, readonly) NSUInteger maximumMessageSize;

/**
 The maximum size of the outbound message queue for the connection.

 The outbound message queue should be large enough to accommodate all the
 messages sent to the server. This would include topic updates, messaging and
 service requests such as registering a handler.

 It may be necessary to increase this value for applications that send messages
 in bursts, or continue to send messages when a session is disconnected and
 reconnecting. Larger values allow more messages to be queued, and increase the
 memory footprint of the session.

 If the outbound message queue fills, sending a message will cause the session
 to close with an error.

 @see defaultMaximumQueueSize

 @since 6.0
 */
@property(nonatomic, readonly) NSUInteger maximumQueueSize;

/**
 The connection timeout.
 
 This constrains the time taken to establish an initial connection to the server.
 The server is responsible for limiting the overall time taken to complete a connection
 once it has received the request.

 @since 5.7
 */
@property(nonatomic, readonly) NSTimeInterval connectionTimeout;

/**
 Security settings to be applied to the underlying transport streams for SSL/TLS
 encrypted connections.
 
 A value of `nil` or an empty dictionary indicates that default settings, as
 defined by the host operating system, will be applied.

 Supported keys are documented by Apple under 'CFStream Property SSL Settings
 Constants' in their Core Foundation
 [CFStream Reference](https://developer.apple.com/library/ios/documentation/CoreFoundation/Reference/CFStreamConstants/#//apple_ref/doc/constant_group/CFStream_Property_SSL_Settings_Constants).
 
 For example, a rudimentary approach to allowing otherwise disallowed self-signed
 certificates could be to disable validation of the certificate chain entirely:
 
     configuration.sslOptions =
         [NSDictionary dictionaryWithObject:kCFBooleanFalse
                                     forKey:kCFStreamSSLValidatesCertificateChain];

 @since 5.7.1
 */
@property(nonatomic, nullable, readonly, copy) NSDictionary* sslOptions;

/**
 User-defined @ref md_session_properties "session properties".

 These properties will be provided to the server when a session is created using
 this session configuration. They will be validated during authentication and
 may be discarded or changed.

 A value of `nil` or an empty dictionary indicates that no user-defined session
 properties will be provided to the server on connection.

 @since 6.3
 */
@property(nonatomic, nullable, readonly, copy) NSDictionary<NSString *, NSString *>* properties;

/**
 Configuration of the HTTP Proxy that should be used to make connections to the server.
 
 This allows connection to a server using HTTP CONNECT tunneling through the
 specified proxy.
 
 A value of `nil` dictates that a proxy is not used. This is the default.

 @since 6.0
 */
@property(nonatomic, nullable, readonly, copy) PTDiffusionHTTPProxyConfiguration* httpProxyConfiguration;

/**
 Compares the receiver to the given session configuration.

 @param sessionConfiguration The session configuration object with which to compare the receiver.

 @return `YES` if the receiver and the given session configuration will have the same effect.

 @since 5.6
 */
-(BOOL)isEqualToSessionConfiguration:(nullable PTDiffusionSessionConfiguration *)sessionConfiguration;

@end

/**
 @brief A mutable session configuration can be modified prior to being used to define
 behaviour and policies to use when connecting to Diffusion.

 @since 5.6
 */
@interface PTDiffusionMutableSessionConfiguration : PTDiffusionSessionConfiguration

/**
 The security principal to use when opening the session.

 A value of `nil` dictates that no principal name will be associated with the session,
 indicating anonymous authentication.

 @since 5.6
 */
@property(nonatomic, nullable, readwrite, copy) NSString *principal;

/**
 The security credentials to use when opening the session.

 A value of `nil` dictates that no credentials will be used when authenticating the session.

 @since 5.6
 */
@property(nonatomic, nullable, readwrite, copy) PTDiffusionCredentials *credentials;

/**
 The reconnection timeout in seconds that will be used on connection failure.

 The reconnection timeout boxed by this number is accessed as a double representing an NSTimeInterval.

 A value of `nil` or a negative boxed value both dictate that reconnection will be disabled.

 @since 5.6
 */
@property(nonatomic, nullable, readwrite) NSNumber* reconnectionTimeout;

/**
 The reconnection strategy that will be used on connection failure.

 A value of `nil` when a valid reconnectionTimeout has been set dictates that the default
 reconnection strategy will be employed.

 @since 5.6
 */
@property(nonatomic, nullable, readwrite) id<PTDiffusionSessionReconnectionStrategy> reconnectionStrategy;

/**
 The recovery buffer size in messages; can be zero.

 If the server is configured to support reconnection, a session established with
 a non-zero reconnection time retains a buffer of sent messages.
 If the session disconnects and reconnects, this buffer is used to re-send
 messages that the server has not received.

 Higher values increase the chance of successful reconnection, but increase the
 per-session memory footprint.

 @see defaultRecoveryBufferSize

 @since 6.0
 */
@property(nonatomic, readwrite) NSUInteger recoveryBufferSize;

/**
 The maximum message size in bytes.

 This constrains the size of messages that may be received from the server and
 thus the size of any content that can be received. The limit protects against
 unexpectedly large messages.
 
 @exception NSInvalidArgumentException On writing to this property if the
 given size is below the allowable minimum.

 @see defaultMaximumMessageSize
 @see maximumMessageSizeMinimum

 @since 6.0
 */
@property(nonatomic, readwrite) NSUInteger maximumMessageSize;

/**
 The maximum size of the outbound message queue for the connection.

 The outbound message queue should be large enough to accommodate all the
 messages sent to the server. This would include topic updates, messaging and
 service requests such as registering a handler.

 It may be necessary to increase this value for applications that send messages
 in bursts, or continue to send messages when a session is disconnected and
 reconnecting. Larger values allow more messages to be queued, and increase the
 memory footprint of the session.

 If the outbound message queue fills, sending a message will cause the session
 to close with an error.

 @see defaultMaximumQueueSize

 @since 6.0
 */
@property(nonatomic, readwrite) NSUInteger maximumQueueSize;

/**
 The connection timeout.

 This constrains the time taken to establish an initial connection to the server.
 The server is responsible for limiting the overall time taken to complete a connection
 once it has received the request.

 If not explicitly set, defaultConnectionTimeout will be assumed.
 
 @note If this exceeds one hour (3,600 seconds) a warning will be logged and the
 connection timeout will be constrained to one hour.

 @since 5.7
 */
@property(nonatomic, readwrite) NSTimeInterval connectionTimeout;

/**
 Security settings to be applied to the underlying transport streams for SSL/TLS
 encrypted connections.
 
 A value of `nil` or an empty dictionary indicates that default settings, as
 defined by the host operating system, will be applied.
 
 Supported keys are documented by Apple under 'CFStream Property SSL Settings
 Constants' in their Core Foundation
 [CFStream Reference](https://developer.apple.com/library/ios/documentation/CoreFoundation/Reference/CFStreamConstants/#//apple_ref/doc/constant_group/CFStream_Property_SSL_Settings_Constants).
 
 For example, a rudimentary approach to allowing otherwise disallowed self-signed
 certificates could be to disable validation of the certificate chain entirely:
 
     configuration.sslOptions =
         [NSDictionary dictionaryWithObject:kCFBooleanFalse
                                     forKey:kCFStreamSSLValidatesCertificateChain];

 @since 5.7.1
 */
@property(nonatomic, nullable, readwrite, copy) NSDictionary* sslOptions;

/**
 User-defined @ref md_session_properties "session properties".

 These properties will be provided to the server when a session is created using
 this session configuration. They will be validated during authentication and
 may be discarded or changed.

 A value of `nil` or an empty dictionary indicates that no user-defined session
 properties will be provided to the server on connection.

 @since 6.3
 */
@property(nonatomic, nullable, readwrite, copy) NSDictionary<NSString *, NSString *>* properties;

/**
 Configuration of the HTTP Proxy that should be used to make connections to the server.

 This allows connection to a server using HTTP CONNECT tunneling through the
 specified proxy.

 A value of `nil` dictates that a proxy is not used. This is the default.

 @since 6.0
 */
@property(nonatomic, nullable, readwrite, copy) PTDiffusionHTTPProxyConfiguration* httpProxyConfiguration;

@end

NS_ASSUME_NONNULL_END
