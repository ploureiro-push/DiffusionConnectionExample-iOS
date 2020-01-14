//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2015, 2017 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;

/**
 Delivery priority for a sent message.

 @since 5.6
 */
typedef NS_ENUM(NSUInteger, PTDiffusionSendDeliveryPriority) {
    /**
     Normal priority.

     @since 5.6
     */
    PTDiffusionSendDeliveryPriority_Normal = 1,

    /**
     Highest priority.

     @since 5.6
     */
    PTDiffusionSendDeliveryPriority_High = 2,

    /**
     Lowest priority.

     @since 5.6
     */
    PTDiffusionSendDeliveryPriority_Low = 3,
};

NS_ASSUME_NONNULL_BEGIN

/**
 Returns a localized string representation of the given send delivery priority.

 @param priority The send delivery priority for which a description is to be
 returned.
 
 @since 5.7
 */
NSString* PTDiffusionSendDeliveryPriorityToString(PTDiffusionSendDeliveryPriority priority);

NS_ASSUME_NONNULL_END
