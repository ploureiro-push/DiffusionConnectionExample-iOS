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

#import <Diffusion/PTDiffusionEnumeration.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Scope specifying when a session lock should be releaed.

 @see PTDiffusionSession#lockWithName:scope:completionHandler:

 @since 6.3
 */
@interface PTDiffusionSessionLockScope : PTDiffusionEnumeration

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 The lock will be released when the acquiring session loses its current
 connection to the server.

 @since 6.3
 */
+(instancetype)unlockOnSessionLoss;

/**
 The lock will be released when the acquiring session is closed.

 @since 6.3
 */
+(instancetype)unlockOnConnectionLoss;

/**
 Compares the receiver to the given session lock scope.

 @param sessionLockScope The session lock scope object with which to compare the
 receiver.

 @return `YES` if the session lock scope is equal to the receiver, otherwise `NO`.

 @since 6.3
 */
-(BOOL)isEqualToSessionLockScope:(nullable PTDiffusionSessionLockScope *)sessionLockScope;

@end

NS_ASSUME_NONNULL_END
