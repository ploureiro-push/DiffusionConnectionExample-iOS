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
#import <Diffusion/PTDiffusionLoggingMessagePrinter.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Options allowing log output to be directed to a custom location.
 
 @see PTDiffusionLogging

 @since 6.0
 */
@interface PTDiffusionLoggingDestinationConfiguration : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Returns a logging destination configuration object initialized with the
 given message printer.

 @param messagePrinter A block that may be called multiple times during the
 lifetime of the current process.
 
 @note The message printer will always be called from a single GCD dispatch
 queue managed by the client library and dedicated to this application process.

 @since 6.0
 */
-(instancetype)initWithMessagePrinter:(PTDiffusionLoggingMessagePrinter)messagePrinter NS_DESIGNATED_INITIALIZER;

/**
 A block that may be called multiple times during the lifetime of the current
 process in order to emit formatted log messages.
 
 @note This property has the `nullable` attribute in order to allow for future
 expansion of this API.

 @since 6.0
 */
@property(nonatomic, readonly, nullable, copy) PTDiffusionLoggingMessagePrinter messagePrinter;

@end

NS_ASSUME_NONNULL_END
