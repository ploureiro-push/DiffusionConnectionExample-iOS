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
#import <Diffusion/PTDiffusionFeature.h>
#import <Diffusion/PTDiffusionUpdateConstraint.h>
#import <Diffusion/PTDiffusionJSONPatchResult.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The Topic Update feature provides a client session with the ability to
 update topics.

 Topics can be set to new values using stateless set operations or by using an
 update stream. Both mechanisms ensure that new values are applied safely to
 appropriate topics.

 ### Update streams

 An update stream is created for a specific topic. The type of the topic must
 match the type of values passed to the update stream. An update stream can be
 used to send any number of updates. It sends a sequence of updates for a
 specific topic to the server. If supported by the data type, updates will be
 sent to the server as a stream of binary deltas.

 Update streams have additional ways of failing compared to stateless set
 operations but when used repeatedly have lower overheads. This is because
 update streams maintain a small amount of state that reduces the overhead of
 operations but can become invalid for example, if the topic is deleted, or
 some other session updates the topic value.

 By default, update streams use a form of optimistic locking. An update stream
 can update its topic incrementally as long as nothing else updates the topic.
 If the topic is updated independently (for example, by another session, or by
 the current session via set or a different update stream), then the next update
 performed by the update stream will complete with an 'invalid update stream'
 error.

 Applications can chose to use collaborative locking to coordinate exclusive
 access to a topic. To follow this pattern acquire a PTDiffusionSessionLock and
 use it with a PTDiffusionUpdateConstraint#lockedWithLock: constraint.
 The application is responsible for designing a locking scheme which determines
 which lock is required to access a particular topic, and for ensuring that all
 parts of the application that update the topic follow this scheme. Lock
 constraints and an application locking scheme can also ensure a sequence of set
 operations has exclusive access to the topic.

 ### Constraints

 Constraints can be applied to the setting of a value and creation of an update
 stream. Constraints describe a condition that must be satisfied for the
 operation to succeed. The constraints are evaluated on the server. The
 available constraints are:

 - an active session lock
 - the absence of a topic
 - the current value of the topic being updated
 - a part of the current value of the topic being updated

 ### Removing values

 When a PTDiffusionTopicType_String, PTDiffusionTopicType_Int64 or
 PTDiffusionTopicType_Double topic is set to `nil`, the topic will be updated to
 have no value. If a previous value was present subscribers will receive a
 notification that the new value is `nil`. New subscribers will not receive a
 value notification.

 ### Adding topics

 When setting a value using either stateless operations or update streams it is
 possible to add a topic if one is not present. This is done using the 'and and
 set' methods or providing a topic specification when creating the update
 stream. If a topic exists these methods will update the existing topic.

 ### Time series topics

 Time series topics have a specific update protocol and are not supported by
 this feature. Use PTDiffusionTimeSeriesFeature to update time series topics.

 ### Access control

 To update a topic a session needs `UPDATE_TOPIC` permission for the topic path.
 To create a topic a session needs `MODIFY_TOPIC` permission for the topic path.
 Requests that combine adding a topic and setting the value, such as those sent
 by the 'add and set' methods, require both permissions.

 ### Accessing the feature

 The Topic Update feature for a session can be obtained from the session's
 `topicUpdate` property.

 This feature is also extended by PTDiffusionTopicsFeature. This means it is
 possible to use the methods described here through that feature.

 @see PTDiffusionSession

 @since 6.3
 */

@interface PTDiffusionTopicUpdateFeature : PTDiffusionFeature

/**
 Applies a JSON Patch to a JSON topic.

 <p>
 The `patch` argument should be formatted according to the JSON
 Patch standard (RFC 6902).

 <p>
 Patches are a sequence of JSON Patch operations contained in an array.
 They are applied as an atomic update to the previous value if the
 resulting update is successfully calculated. The following patch will
 check the value at a specific key and update if the expected value is
 correct:
 <p>

 `[{"op":"test", "path":"/price", "value" : 22},
 {"op":"add", "path":"/price", "value": 23}]`

 <p>
 The available operations are:

 <ul>
 <li>
 <strong>Add:</strong> `{"op": "add", "path": "/a/b/c", "value": [ "foo", "bar" ]}`
 <li>
 <strong>Remove:</strong> `{"op": "remove", "path": "/a/b/c"}`
 <li>
 <strong>Replace:</strong> `{"op": "replace", "path": "/a/b/c", "value": 43}`
 <li>
 <strong>Move:</strong> `{"op": "move", "from": "/a/b/c", "path": "/a/b/d"}`
 <li>
 <strong>Copy:</strong> `{"op": "copy", "from": "/a/b/c", "path": "/a/b/e"}`
 <li>
 <strong>Test:</strong> `{"op": "test", "path": "/a/b/c", "value": "foo"}`
 </ul>

 <p>
 The test operation checks that the CBOR representation of the value of a
 topic is identical to the value provided in the patch after converting it
 to CBOR. If the value is represented differently as CBOR, commonly due to
 different key ordering, then the patch will return the index of the
 failed operation . e.g the values
 `{"foo": "bar", "count": 43}` and
 `{"count": 43, "foo": "bar"}` are unequal despite semantic equality
 due to the differences in a byte for byte comparison.

 @param jsonPatch the JSON Patch

 @param path the path of the topic to patch

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @see <a href="https://tools.ietf.org/html/rfc6902">
 RFC 6902: JavaScript Object Notation (JSON) Patch</a>

 @since 6.4

 */
-(void)applyJsonPatch:(NSString *)jsonPatch
               toPath:(NSString *)path
    completionHandler:(void (^)(PTDiffusionJSONPatchResult *result, NSError * _Nullable error))completionHandler;


/**

 Applies a JSON Patch to a JSON topic.

 <p>
 Takes a constraint that must be satisfied for the update to be
 applied.
 <p>
 In other respects this method works in the same way as
 applyJsonPatch:toPath:completionHandler:


 @param jsonPatch the JSON Patch

 @param path the path of the topic to patch

 @param constraint the constraint that must be satisfied for the patch to
 be applied

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @see <a href="https://tools.ietf.org/html/rfc6902">
 RFC 6902: JavaScript Object Notation (JSON) Patch</a>

 @since 6.4
*/
-(void)applyJsonPatch:(NSString *)jsonPatch
               toPath:(NSString *)path
       withConstraint:(PTDiffusionUpdateConstraint *)constraint
    completionHandler:(void (^)(PTDiffusionJSONPatchResult *result, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
