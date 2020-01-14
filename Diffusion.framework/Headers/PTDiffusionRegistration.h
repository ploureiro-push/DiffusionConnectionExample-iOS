//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2018 Push Technology Ltd., All Rights Reserved.
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
 @brief A reference to a registered handle.

 Such a reference is provided once a handler with a server-side presence has
 been registered.

 @since 6.1
 */
@interface PTDiffusionRegistration : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Request that the handler is unregistered from the server.

 After the handler is unregistered, the completionHandler will be notified.

 @since 6.1
 */
-(void)closeWithCompletionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 Request that the handler is unregistered from the server.

 If the handler has already been unregistered, calling this method has no effect.

 @note Before 6.1 this method was defined on PTDiffusionTopicTreeRegistration.

 @since 5.7
 */
-(void)close;

@end

NS_ASSUME_NONNULL_END
