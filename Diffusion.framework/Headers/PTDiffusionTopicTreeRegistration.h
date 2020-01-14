//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2016, 2018 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionRegistration.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A reference to a handler registered for a particular topic path.
 
 A topic tree registration is provided once a handler with a server-side
 presence has been registered.

 @since 5.7
 */
@interface PTDiffusionTopicTreeRegistration : PTDiffusionRegistration

/**
 The path registered.
 
 @since 6.0
 */
@property(nonatomic, readonly) NSString* path;

@end

NS_ASSUME_NONNULL_END
