//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2015, 2018 Push Technology Ltd., All Rights Reserved.
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
 @brief A receive context provides additional contextual information for received content.
 
 @see PTDiffusionMessageStreamDelegate

 @deprecated Since 6.2. This is only used within one-way messaging, which is
 also deprecated. This interface will be removed in a future release.

 @since 5.6
 */
__deprecated_msg("Will be removed in a future release.")
@interface PTDiffusionReceiveContext : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 The headers if there are any.

 The array will be empty if there are no headers.

 @since 5.6
 */
@property(nonatomic, readonly) NSArray<NSString *> * headers;

/**
 The values of any session properties that have been requested to be passed with
 messages.
 
 The dictionary will be empty if no properties were requested or if properties
 cannot be delivered to the receiver.

 @since 6.0
 */
@property(nonatomic, readonly) NSDictionary<NSString *, NSString *> * sessionProperties;

/**
 Compares the receiver to the given receive context.

 @param receiveContext The receive context object with which to compare the receiver.

 @return `YES` if the receive context is equal to the receiver, otherwise `NO`.

 @since 5.6
 */
-(BOOL)isEqualToReceiveContext:(nullable PTDiffusionReceiveContext *)receiveContext;

@end

NS_ASSUME_NONNULL_END
