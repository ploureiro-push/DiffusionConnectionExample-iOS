//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2015, 2016 Push Technology Ltd., All Rights Reserved.
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
 @brief Session state represents the condition a session has in respect
 of connectivity to a Diffusion server.
 
 A session state object is immutable.

 @see PTDiffusionSessionStateChange
 
 @since 5.6
 */
@interface PTDiffusionSessionState : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 `YES` if the session has an active connection to the server, otherwise `NO`.

 @since 5.6
 */
@property(nonatomic, readonly, getter=isConnected) BOOL connected;

/**
 `YES` if the session is in the process of attempting reconnection to the server,
 otherwise `NO`.

 @since 5.6
 */
@property(nonatomic, readonly, getter=isRecovering) BOOL recovering;

/**
 `YES` if the session is closed, otherwise `NO`.
 
 This might mean that the session lost its connection to the server and
 could not be recovered.

 @since 5.6
 */
@property(nonatomic, readonly, getter=isClosed) BOOL closed;

/**
 If the session is closed then this property will be `nil` if the closure
 was normal and expected, otherwise it will contain the failure reason.
 
 @note This property is to be considered as an auxiliary, informational
 attachment to this session state instance. As such it is not incorporated
 within the result of the hash method and is not checked on calls to isEqual:
 or isEqualToSessionState:.

 @since 5.9
 */
@property(nonatomic, readonly, nullable) NSError* error;

/**
 Compares the receiver to the given session state.

 @param sessionState The session state object with which to compare the receiver.

 @return `YES` if the given session state is equal to the receiver, otherwise `NO`.

 @since 5.6
 */
-(BOOL)isEqualToSessionState:(nullable PTDiffusionSessionState *)sessionState;

@end

NS_ASSUME_NONNULL_END
