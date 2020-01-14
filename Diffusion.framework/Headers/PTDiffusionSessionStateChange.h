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

@class PTDiffusionSessionState;

NS_ASSUME_NONNULL_BEGIN

/**
 The name used for session state change notifications.

 The notification's `userInfo` dictionary contains a PTDiffusionSessionStateChange object that describes the state change,
 accessed using #PTDiffusionSessionStateChangeUserInfoKey.

 @relates PTDiffusionSessionStateChange
 @see PTDiffusionSessionStateChangeUserInfoKey
 
 @note Session state change notifications are notified from the main dispatch queue and are delivered after
 both KVO notifications on the session's state property and any invocations of completion callback handler blocks.

 @since 5.6
 */
extern NSString *const PTDiffusionSessionStateDidChangeNotification;

/**
 The notification `userInfo` dictionary key used to access the PTDiffusionSessionStateChange object on
 receipt of a #PTDiffusionSessionStateDidChangeNotification.

 @relates PTDiffusionSessionStateChange
 @see PTDiffusionSessionStateDidChangeNotification

 @since 5.6
 */
extern NSString *const PTDiffusionSessionStateChangeUserInfoKey;

/**
 @brief A session state change represents a change in a session's state.
 
 A session state change object is immutable.

 The @ref md_quick_start "Quick Start" guide provides an example of observing session state changes broadcast
 through the default notification center.

 @see PTDiffusionSession

 @since 5.6
 */
@interface PTDiffusionSessionStateChange : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 The previous state. This is the state that the session was in prior to transitioning to its current state.

 @since 5.6
 */
@property(nonatomic, readonly) PTDiffusionSessionState* previousState;

/**
 The current state. This is the state that the session has now transitioned to.

 @since 5.6
 */
@property(nonatomic, readonly) PTDiffusionSessionState* state;

/**
 Compares the receiver to the given session state change.

 @param sessionStateChange The session state change object with which to compare the receiver.

 @return `YES` if the given session state change is equal to the receiver, otherwise `NO`.

 @since 5.6
 */
-(BOOL)isEqualToSessionStateChange:(nullable PTDiffusionSessionStateChange *)sessionStateChange;

@end

NS_ASSUME_NONNULL_END
