//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2019 Push Technology Ltd., All Rights Reserved.
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
 @brief Permissions that protect globally scoped, access-controlled operations.

 There is no related object, permission is granted globally.

 @see PTDiffusionTopicPermission

 @since 6.3
 */
@interface PTDiffusionGlobalPermission : PTDiffusionEnumeration

/**
 Add an authentication handler.

 @since 6.3
 */
+(instancetype)authenticate;

/**
 List or listen to client sessions.

 @since 6.3
 */
+(instancetype)viewSession;

/**
 Alter a client session. This covers a range of actions including:

 - subscribe session to topic
 - throttle session
 - enable conflation for session
 - close session

 @since 6.3
 */
+(instancetype)modifySession;

/**
 Required to register any server-side handler.

 This restricts clients from consuming resources by registering long lived
 handlers (or example, addMessageHandler). Typically these would never be called
 due to lack of other permissions.

 @since 6.3
 */
+(instancetype)registerHandler;

/**
 View the server's runtime state - for example, read metrics.

 @since 6.3
 */
+(instancetype)viewServer;

/**
 Change the server's runtime state - for example, shut it down.

 @since 6.3
 */
+(instancetype)controlServer;

/**
 Read the security configuration.

 @since 6.3
 */
+(instancetype)viewSecurity;

/**
 Change the security configuration.

 @since 6.3
 */
+(instancetype)modifySecurity;

/**
 A permission that is unsupported by the session.

 @since 6.3
 */
+(instancetype)unknownGlobalPermission;

/**
 Read topic views.

 @since 6.3
 */
+(instancetype)readTopicViews;

/**
 Modify topic views.

 @since 6.3
 */
+(instancetype)modifyTopicViews;

@end

NS_ASSUME_NONNULL_END
