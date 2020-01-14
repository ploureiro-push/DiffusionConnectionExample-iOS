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

@class PTDiffusionTopicTreeRegistration;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Common protocol for delegates that establish a server side control presence for the
 client session at a particular branch of the topic tree.

 @since 5.7
 */
@protocol PTDiffusionTopicTreeRegistrationDelegate

/**
 Called if the handler is closed.
 
 No further calls will be made to this handler.

 @param registration The topic tree registration for which this delegate applies.

 @since 5.7
 */
-(void)diffusionTopicTreeRegistrationDidClose:(PTDiffusionTopicTreeRegistration *)registration;

/**
 Called in the event of a contextual error relating to this handler.

 No further calls will be made to this handler.

 @param registration The topic tree registration for which this delegate applies.
 
 @param error The failure reason.

 @since 5.7
 */
-(void)diffusionTopicTreeRegistration:(PTDiffusionTopicTreeRegistration *)registration
                     didFailWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
