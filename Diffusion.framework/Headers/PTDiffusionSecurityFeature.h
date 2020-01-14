//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2015, 2019 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionFeature.h>

@class PTDiffusionCredentials;
@class PTDiffusionGlobalPermission;
@class PTDiffusionTopicPermission;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief This feature provides a client session with the ability to change its
 associated principal as well as to query permissions assigned to it.

 The Security feature for a session can be obtained from the session's
 `security` property.

 @see PTDiffusionSession
 
 @since 5.6
 */
@interface PTDiffusionSecurityFeature : PTDiffusionFeature

/**
 Change the security principal associated with the current session.
 
 If authentication fails, the current principal will remain valid.

 @param principal The new principal name.

 @param credentials The credentials authenticating the new principal.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException Raised if the completionHandler argument
 is `nil`.
 
 @since 5.6
 */
-(void)changePrincipal:(nullable NSString *)principal
           credentials:(nullable PTDiffusionCredentials *)credentials
     completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 Query the global permissions assigned to the calling session.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @since 6.3
 */
-(void)getGlobalPermissionsWithCompletionHandler:(void (^)(NSSet<PTDiffusionGlobalPermission *> * _Nullable permissions, NSError * _Nullable error))completionHandler;

/**
 Query the topic permissions assigned to the calling session on a given path.

 @param path the path to query for permissions

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @since 6.3
 */
-(void)getTopicPermissionsForPath:(NSString *)path
                completionHandler:(void (^)(NSSet<PTDiffusionTopicPermission *> * _Nullable permissions, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
