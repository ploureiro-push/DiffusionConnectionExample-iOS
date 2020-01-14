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
#import <Diffusion/PTDiffusionUpdateStream.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief An update stream that provides the ability for updating topics with
 numerical primitive values.

 @see PTDiffusionTopicUpdateFeature

 @since 6.3
 */
@interface PTDiffusionNumberUpdateStream : PTDiffusionUpdateStream

/**
 The latest value of the topic set using this update stream, from local cache.

 This value reflects the last value that has been set, before it is sent to the
 server.

 If the server rejects a set operation, the topic value will not change and this
 update stream will be invalidated.

 @since 6.3
 */
@property(nonatomic, readonly, nullable) NSNumber* value;

/**
 Sets the topic to a specified value or no value.

 When a `nil` value is supplied to this method for a PTDiffusionTopicType_Int64
 or PTDiffusionTopicType_Double topic, the topic will be updated to have no
 value. If a previous value was present subscribers will receive a notification
 that the new value is null. New subscribers will not receive a value
 notification.

 The first call to this method may fail with a "no such topic" or "incompatible
 topic" error. Subsequent calls may fail with "invalid update stream". Any call
 can fail with a "cluster repartition", "session security" or "session closed"
 error.

 If a PTDiffusionUpdateConstraint was provided when creating the update stream,
 the first call to this method may also fail with an "unsatisified constraint"
 error.

 If the update stream was created with one of the "create update stream"
 methods, the first call to this method may also fail with an "incompatible
 existing topic" error and it will not fail with a "no such topic" error.

 If this method fails all subsequent calls to 'set' or 'validate' will fail with
 an "invalid update stream" error.

 If the task fails, the completionHandler will be called with an error. Common
 reasons for failure include:

 - **no such topic** if there is no topic bound to `path`.
 - **incompatible topic** if updates cannot be applied to the topic, for example
 if a topic view has bound a reference topic to the path.
 - **incompatible topic state** if the topic is managed by a component (such as
 fan-out) that prohibits updates from the caller.
 - **exclusive updater conflict** if updates cannot be applied to the topic
 because an exclusive PTDiffusionTopicUpdateSource is registered for its path.
 - **unsatisfied constraint** if the `constraint` is not  satisfied by the topic
 `path`.
 - **invalid update stream** if the update stream has been invalidated.
 - **incompatible parent topic** if a topic could not be added because a topic
   at a parent path is incompatible.
 - **invalid topic path** if `path` is not a valid topic path.
 - **invalid topic specification** if the specification is invalid, possibly
   because mandatory properties were not supplied.
 - **topic license limit** if the topic could not be added as it would breach a
   licensing limit.
 - **cluster repartition** if the cluster was repartitioning.
 - **session security** if the calling session does not have the `MODIFY_TOPIC` or
 `UPDATE_TOPIC` permission for `path`.
 - **session closed** if the session is closed.

 @param value The value to set the topic to.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil` and `result` will be non-`nil`. The completion handler will
 be called asynchronously on the main dispatch queue.

 @param error If this method returns `NO` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return `YES` on success; or `NO` if an error occurred, in which case `*error`
 will be populated with the failure reason.

 @exception NSInvalidArgumentException If completionHandler is `nil`.

 @since 6.3
 */
-(BOOL)      setValue:(nullable NSNumber *)value
    completionHandler:(void (^)(PTDiffusionTopicCreationResult * _Nullable result, NSError * _Nullable error))completionHandler
                error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
