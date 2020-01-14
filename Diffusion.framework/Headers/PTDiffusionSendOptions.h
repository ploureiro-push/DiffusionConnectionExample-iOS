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
#import <Diffusion/PTDiffusionSendDeliveryPriority.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Send options are associated with sending content.
 
 @see PTDiffusionMessagingFeature

 @deprecated Since 6.2. This is only used within one-way messaging, which is
 also deprecated. This interface will be removed in a future release.

 @since 5.6
 */
__deprecated_msg("Will be removed in a future release.")
@interface PTDiffusionSendOptions : NSObject <NSCopying, NSMutableCopying>

/**
 Returns a send options object initialized with Normal delivery priority.
 
 @since 5.6
 */
-(instancetype)init;

/**
 Returns a send options object initialized with the given priority.

 @param priority The delivery priority to send with.

 @since 6.0
 */
-(instancetype)initWithPriority:(PTDiffusionSendDeliveryPriority)priority;

/**
 Returns a send options object with the given priority.

 @param priority The delivery priority to send with.

 @since 5.6
 */
+(instancetype)sendOptionsWithPriority:(PTDiffusionSendDeliveryPriority)priority;

/**
 The delivery priority to send with.

 @since 5.6
 */
@property(nonatomic, readonly) PTDiffusionSendDeliveryPriority priority;

/**
 Compares the receiver to the given send options.

 @param sendOptions The send options object with which to compare the receiver.

 @return `YES` if the send options is equal to the receiver, otherwise `NO`.

 @since 5.6
 */
-(BOOL)isEqualToSendOptions:(nullable PTDiffusionSendOptions *)sendOptions;

@end

/**
 @brief Mutable send options can be modified prior to being associated with sending content.

 @deprecated Since 6.2. This is only used within one-way messaging, which is
 also deprecated. This interface will be removed in a future release.

 @since 5.6
 */
__deprecated_msg("Will be removed in a future release.")
@interface PTDiffusionMutableSendOptions : PTDiffusionSendOptions

/**
 The delivery priority to send with.

 @since 5.6
 */
@property(nonatomic, readwrite) PTDiffusionSendDeliveryPriority priority;

@end

NS_ASSUME_NONNULL_END
