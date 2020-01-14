//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2016, 2017 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;

@class PTDiffusionLoggingDestinationConfiguration;
@class PTDiffusionLoggingLevel;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Logging provides access to debug information that can be enabled at runtime.
 
 Changes to properties here have immediate effect on the verbosity or otherwise
 of log output.
 
 The format of output log messages is subject to change.
 
 By default messages are sent to the Apple System Log facility using synchronous
 calls to the Foundation framework's NSLog function. The destinationConfiguration
 property can be used to change this behaviour.

 @since 5.7
 */
@interface PTDiffusionLogging : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Returns the Diffusion logging object representing the current application process.

 @since 5.7
 */
+(PTDiffusionLogging *)logging;

/**
 Global switch to switch on or off logging. A value of `YES` switches logging on and
 a value of `NO` switches it off.
 
 The default value for this property is `NO`.
 
 @note Logging may be switched on using this property but the amount of informational
 messages output depends on the combination of other properties defined by this
 interface.

 @since 5.7
 */
@property(nonatomic, readwrite, getter=isEnabled) BOOL enabled;

/**
 The ranking of information messages required to be output.
 This property allows the granularity of log output to be set.
 Only messages ranked at this granularity or above will be enabled.
 
 The default value for this property is [PTDiffusionLoggingLevel info].

 @since 5.7
 */
@property(nonatomic, readwrite) PTDiffusionLoggingLevel* level;

/**
 Set the format of log message output. The syntax of this string is subject to change
 so the required formatting tokens are not documented or intended to be constructed for use
 by application developers unless instructed by a member of support staff in order to
 assist in debugging an issue.

 @since 5.7
 */
-(void)setFormat:(NSString *)format;

/**
 Set all properties to default values, as required for production use when
 debugging information is not required or desired.
 A call to this method turns off all runtime-switchable log output.
 
 @note This method intentionally does not reset the destinationConfiguration
 property.

 @since 5.7
 */
-(void)reset;

/**
 Options allowing log output to be directed to a custom location.

 The default value for this property is `nil`, specifying that messages should
 be sent to the Apple System Log facility using synchronous calls to the
 Foundation framework's NSLog function.

 @since 6.0
 */
@property(nonatomic, readwrite, nullable) PTDiffusionLoggingDestinationConfiguration* destinationConfiguration;

@end

NS_ASSUME_NONNULL_END
