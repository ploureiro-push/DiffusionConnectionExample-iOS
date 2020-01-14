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

@class PTDiffusionSession;
@class PTDiffusionSessionReconnectionAttempt;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The session reconnection strategy protocol defines the behaviour for a session when
 recovering a failed connection.
 
 @see PTDiffusionSessionConfiguration

 @since 5.6
 */
@protocol PTDiffusionSessionReconnectionStrategy <NSObject>

/**
 The connection has failed when connecting or connected and the session is now in
 a recovering state.
 
 @param session The session which is recovering.
 
 @param attempt The reconnection attempt object providing `start` and `abort` methods
 to be used by the implementing strategy immediately or at some point in the future
 to instruct the session how to proceed.

 @since 5.6
 */
-(void)         diffusionSession:(PTDiffusionSession *)session
    wishesToReconnectWithAttempt:(PTDiffusionSessionReconnectionAttempt *)attempt;

@end

/**
 @brief Immediate abort is a default reconnection strategy supplied with the client library.
 
 This strategy immediately aborts.

 @since 5.6
 */
@interface PTDiffusionSessionImmediateAbortReconnectionStrategy : NSObject <PTDiffusionSessionReconnectionStrategy>
@end

/**
 @brief Delayed is a default reconnection strategy supplied with the client library.
 
 This strategy attempts to reconnect after a fixed delay specified in seconds.

 @since 5.6
 */
@interface PTDiffusionSessionDelayedReconnectionStrategy : NSObject <PTDiffusionSessionReconnectionStrategy>

/**
 Returns a delayed reconnection strategy initialised with a default 5 second delay.

 @since 5.6
 */
-(instancetype)init;

/**
 Returns a delayed reconnection strategy initialised with the given delay.
 
 @param delay The delay in seconds, after which point the receiver will call the session reconnection
 attempt's `start` method.

 @since 5.6
 */
-(instancetype)initWithDelay:(NSTimeInterval)delay NS_DESIGNATED_INITIALIZER;

/**
 The delay, in seconds, after which point the receiver will call the session reconnection 
 attempt's `start` method.

 @since 5.6
 */
@property(nonatomic, readonly) NSTimeInterval delay;

@end

NS_ASSUME_NONNULL_END
