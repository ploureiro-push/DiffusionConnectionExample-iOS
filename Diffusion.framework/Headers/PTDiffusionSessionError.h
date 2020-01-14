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
 The value assigned to the `domain` property of NSError objects generated when
 establishing or reestablishing a session's connection to the server.
 
 @see PTDiffusionSessionErrorCode

 @since 6.0
 */
extern NSString *const PTDiffusionSessionErrorDomain;

/**
 Values assigned to the `code` property of NSError objects generated when
 establishing or reestablishing a session's connection to the server.
 
 @see PTDiffusionSessionErrorDomain

 @since 6.0
 */
typedef NS_ENUM(NSInteger, PTDiffusionSessionErrorCode) {
    /**
     The session was closed after being unexpectedly disconnected.

     @since 6.0
     */
    PTDiffusionSessionErrorCode_Disconnected = 2,

    /**
     The session was closed locally.

     @since 6.0
     */
    PTDiffusionSessionErrorCode_ClosedByClient = 3,

    /**
     There was a problem when establishing a session.

     The session is closed. No further operations are possible.
     
     @since 6.0
     */
    PTDiffusionSessionErrorCode_Establishment = 4,

    /**
     The session operation failed due to a security constraint.
     
     Repeating the operation with the same security credentials is likely to
     fail.

     @since 6.0
     */
    PTDiffusionSessionErrorCode_Security = 5,
};

NS_ASSUME_NONNULL_END
