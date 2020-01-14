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
 @brief Methods implemented by classes wishing to listen to error notifications.
 
 Error reports indicate that an unexpected condition has occurred.
 They are used sparingly. Error conditions that occur in the context of an API
 operation and that an application can reasonably handle are reported to
 operation-specific delegates or completion handlers, not as error reports.
 
 A client can typically do nothing about an error report other than to report it
 for diagnosis. The server log should be examined for further information.

 @note The PTDiffusionSessionErrorHandler protocol was deprecated in 5.9 and
 removed in 6.0.

 @since 6.0
 */
@protocol PTDiffusionErrorListener

/**
 Called when an error has been reported.
 
 @param error The error that was reported.

 @since 6.0
 */
-(void)diffusionDidReportError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
