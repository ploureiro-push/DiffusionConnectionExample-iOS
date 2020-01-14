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

@class PTDiffusionPartialJSONUpdateConstraint;
@class PTDiffusionSessionLock;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A constraint to be applied to an update operation or the creation of an
 update stream.

 Constraints describe a condition that must be satisfied for an operation to
 succeed. Constraints can be applied to the setting of a value or creation of an
 update stream. Constraints are only evaluated on the server.

 Constraints are evaluated using the:
 - active session locks
 - existence of the topic
 - current value of the topic

 The value of a topic can be described in several ways. The value can be
 described as an exact value, a partial value or an unset value.

 Constraints can be composed with one another. It is only possible to construct
 logical ANDs of constraints. Constraints can only be composed if the resulting
 constraint is satisfiable. Multiple session locks can be held but a topic can
 only have a single value. Constraints specifying multiple topic values cannot
 be constructed.

 @see PTDiffusionTopicUpdateFeature

 @since 6.3
 */
@interface PTDiffusionUpdateConstraint : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Returns a constraint requiring a lock to be held by the session.

 This can be used to coordinate operations between multiple sessions.

 @exception NSInvalidArgumentException If the lock argument is `nil`.

 @since 6.3
 */
+(instancetype)lockedWithLock:(PTDiffusionSessionLock *)lock;

/**
 Create a constraint requiring the topic to have no value.

 This is useful when setting the first value of a topic. This constraint is
 unsatisfied if no topic is present at the path, making it unsuitable for
 operations that try to add topics.

 @since 6.3
 */
+(instancetype)noValue;

/**
 Returns a constraint requiring the path to have no topic.

 This is useful when setting the first value of a topic being added using one of
 the 'add and set' methods without changing the value if the topic already
 exists. This constraint is unsatisfied if a topic is present at the path,
 making it unsuitable for operations that try to set topics without adding them.

 @since 6.3
 */
+(instancetype)noTopic;

/**
 Returns a constraint that partially matches the current topic value.

 The topic must be PTDiffusionTopicType_JSON. The returned constraint partially
 describes the structure of a PTDiffusionJSON value.

 @since 6.3
 */
+(PTDiffusionPartialJSONUpdateConstraint *)jsonValue;

/**
 Returns a composed constraint that represents a logical AND of this constraint
 and another.

 @param constraint The other constraint that will be logically-ANDed with this
 constraint

 @param error Location to store a reason in case of failure. May be `nil`.

 @return A new constraint or `nil` if there was an error.

 @exception NSInvalidArgumentException If the constraint argument is `nil`.

 @since 6.3
 */
-(nullable instancetype)andConstraint:(PTDiffusionUpdateConstraint *)constraint
                                error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
