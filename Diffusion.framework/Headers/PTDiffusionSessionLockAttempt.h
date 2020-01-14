//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2019 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionCancellable.h>

@class PTDiffusionSessionLock;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A handle to a session lock request.

 Instances of this object may be used to cancel the session lock attempt as well
 as to query the lock instance once acquired.

 @since 6.3
 */
@interface PTDiffusionSessionLockAttempt : NSObject <PTDiffusionCancellable, NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 The acquired lock, if the attempt was successful. Until a response has come
 back from the server, this property will be `nil`. It will remain `nil` if that
 response indicates that the session lock attempt failed.

 @since 6.3
 */
@property(nullable, readonly) PTDiffusionSessionLock * lock;

/**
 Compares the receiver to the given session lock attempt.

 @param sessionLockAttempt The session lock attempt object with which to compare
 the receiver.

 @return `YES` if the session lock attempt is equal to the receiver, otherwise `NO`.

 @since 6.3
 */
-(BOOL)isEqualToSessionLockAttempt:(nullable PTDiffusionSessionLockAttempt *)sessionLockAttempt;

@end

NS_ASSUME_NONNULL_END
