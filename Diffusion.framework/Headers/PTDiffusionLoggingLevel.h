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
#import <Diffusion/PTDiffusionEnumeration.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A level of information events useful for debugging.
 
 The levels defined here are modelled on those defined by SLF4J as used by
 the Diffusion Java API.
 
 @see PTDiffusionLogging

 @since 5.7
 */
@interface PTDiffusionLoggingLevel : PTDiffusionEnumeration

/**
 Designates error events that might still allow the application to continue
 running normally.

 @since 5.7
 */
+(instancetype)error;

/**
 Designates potentially harmful situations.

 @since 5.7
 */
+(instancetype)warn;

/**
 Designates informational messages that highlight the process of the application
 at a coarse-grained level.

 @since 5.7
 */
+(instancetype)info;

/**
 Designates fine-grained informational messages that are most useful to debug
 an application.

 @since 5.7
 */
+(instancetype)debug;

/**
 Designates finer-grained informational events than debug.

 @since 5.7
 */
+(instancetype)trace;

@end

NS_ASSUME_NONNULL_END
