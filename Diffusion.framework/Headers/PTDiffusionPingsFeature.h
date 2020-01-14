//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2016 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionFeature.h>

@class PTDiffusionPingDetails;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The Pings feature provides a client session with the ability to ping the server.

 The main purpose of a ping is to test, at a very basic level, the current
 network conditions that exist between the client session and the server it is
 connected to. Each ping request will return details on the latency
 experienced in the form of a round-trip time value.
 
 The Pings feature for a session can be obtained from the session's `pings` property.
 
 @see PTDiffusionSession
 
 @since 5.7
 */
@interface PTDiffusionPingsFeature : PTDiffusionFeature

/**
 Send a ping to the server.
 
 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.
 
 @exception NSInvalidArgumentException Raised if the completionHandler is `nil`.

 @since 5.7
 */
-(void)pingServerWithCompletionHandler:(void (^)(PTDiffusionPingDetails * _Nullable details, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
