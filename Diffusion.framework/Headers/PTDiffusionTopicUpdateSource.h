//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2016, 2019 Push Technology Ltd., All Rights Reserved.
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
@class PTDiffusionTopicUpdater;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A source of updates which may be registered in order to update parts of the topic tree.
 
 Classes wishing to peform the role of an update source must conform to this protocol.

 Registering as an update source for a particular point in the topic tree allows a client to
 update all topics below that point in the tree.
 There is no need to subscribe to a topic in order to update it.

 Once an update source is registered it may be in either a active state, where it can provide
 topic updates, or a standby state, where it is still registered but is not allowed to perform
 updates.
 An update source may switch between these states in any order, depending on server policy.
 
 @see PTDiffusionTopicUpdateControlFeature

 @deprecated Since 6.3. This class will be removed in a future release. See
 PTDiffusionTopicUpdateFeature, providing equivalent and additional
 functionality such as conditional updates.

 @since 5.7
 */
__deprecated_msg("Will be removed in a future release.")
@protocol PTDiffusionTopicUpdateSource <PTDiffusionTopicTreeRegistrationDelegate>

/**
 State notification that this source is now active for the specified topic path, and is
 therefore in a valid state to send updates on topics at or below the registered topic path.

 @param registration The topic tree registration for which this updater applies.
 
 @param updater An updater that may be used to update topics at or below the registered
 topic path.

 @since 5.7
 */
-(void)diffusionTopicTreeRegistration:(PTDiffusionTopicTreeRegistration *)registration
                  isActiveWithUpdater:(PTDiffusionTopicUpdater *)updater;

/**
 Notification that this source is not currently allowed to provide topic updates for the
 specified topic path. This indicates that another UpdateSource is currently active for
 the given topic path.

 Server policy will dictate when this UpdateSource is set to be active.

 If this UpdateSource was previously in an active state, any updater instances for this
 topic path will no longer be valid for use.
 
 @param registration The topic tree registration for which this updater applies.

 @since 5.7
 */
-(void)diffusionTopicTreeRegistrationIsOnStandbyForUpdates:(PTDiffusionTopicTreeRegistration *)registration;

@end

NS_ASSUME_NONNULL_END
