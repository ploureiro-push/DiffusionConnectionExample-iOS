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
#import <Diffusion/PTDiffusionRegistration.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The registration state of the associated topic notification listener
 on the server.

 Provides operations to control which topic paths the listener will receive
 notifications for.

 @since 6.1
 */
@interface PTDiffusionTopicNotificationRegistration : PTDiffusionRegistration

/**
 Request to receive notifications for all topics matched by the provided topic
 selector.

 @param expression The @ref md_topic_selectors "topic selector" expression to be
 evaluated by the server.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any arguments are `nil`.

 @since 6.1
 */
-(void)selectWithTopicSelectorExpression:(NSString *)expression
                       completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 Request to stop receiving notifications for all topics matched by the provided
 topic selector.

 @param expression The @ref md_topic_selectors "topic selector" expression to be
 evaluated by the server.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any arguments are `nil`.

 @since 6.1
 */
-(void)deselectWithTopicSelectorExpression:(NSString *)expression
                         completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
