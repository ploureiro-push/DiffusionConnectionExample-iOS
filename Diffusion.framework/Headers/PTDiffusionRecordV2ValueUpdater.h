//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2017, 2019 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionTopicUpdater.h>
#import <Diffusion/PTDiffusionValueUpdater.h>

@class PTDiffusionRecordV2;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A record value updater may be used to update record topics by specifying
 new values.

 @see PTDiffusionTopicUpdateControlFeature
 @see PTDiffusionTopicUpdater

 @deprecated Since 6.3. This class will be removed in a future release. It has
 been replaced by PTDiffusionRecordV2UpdateStream which is accessed using
 PTDiffusionTopicUpdateFeature, providing equivalent and additional
 functionality such as conditional updates.

 @since 6.0
 */
__deprecated_msg("Will be removed in a future release.")
@interface PTDiffusionRecordV2ValueUpdater : PTDiffusionValueUpdater

/**
 Returns the current cached value for a given topic path.

 @param value On successful return then set to the current cached value or `nil`
 if there is no value for the given path. There may be no value because no value
 has yet been sent, or the value has been removed from the cache.

 @param topicPath Specifies the topic to obtain the current value for.

 @param error If an error occurs, upon return contains an `NSError` object that
 describes the problem.

 @return `YES` if there is no cached value for the given topic path or if the
 cached entry for the given topic path is of the correct type. In either of
 these cases the value will be assigned appropriately. Otherwise this method
 returns `NO` and error will be assigned with a failure reason.

 @exception NSInvalidArgumentException If either of the value or topicPath
 arguments are `nil`.

 @since 6.0
 */
-(BOOL)getCachedValue:(PTDiffusionRecordV2 *_Nullable *_Nonnull)value
         forTopicPath:(NSString *)topicPath
                error:(NSError **)error;

/**
 Updates a topic to a specified value.

 For exclusive updating, this method caches the supplied value so that
 subsequent calls for the same topic will be able to use the current value to
 calculate deltas of change to send to the server rather than having to send the
 whole value.

 For non-exclusive updating, the complete value is always sent to the server and
 the value is not cached.

 @param topicPath Specifies the topic to be updated.

 @param value The new value for the topic.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will
 be `nil`. The completion handler will be called asynchronously on the main
 dispatch queue.

 @exception NSInvalidArgumentException If any of the supplied arguments are `nil`.

 @since 6.0
 */
-(void)updateWithTopicPath:(NSString *)topicPath
                     value:(PTDiffusionRecordV2 *)value
         completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

@end

/**
 @brief Extension adding support for updating topics using record values.

 @since 6.0
 */
@interface PTDiffusionTopicUpdater (PTDiffusionRecordV2ValueUpdater)

/**
 Returns an updater that can be used for the record data type to apply value
 updates.

 @since 6.0
 */
-(PTDiffusionRecordV2ValueUpdater *)recordValueUpdater;

@end

NS_ASSUME_NONNULL_END
