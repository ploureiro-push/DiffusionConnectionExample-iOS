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

@class PTDiffusionSessionLockScope;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A server-managed resource that can be used to coordinate exclusive
 access to shared resources across sessions.

 For example, to ensure a single session has the right to update a topic; to
 ensure at most one session responds to an event; or to select a single session
 to perform a housekeeping task. Session locks support general collaborative
 locking schemes. The application architect is responsible for designing a
 suitable locking scheme and for ensuring each application component follows the
 scheme appropriately.

 Session locks are identified by a lock name. Lock names are arbitrary and
 chosen at will to suit the application. Each lock is owned by at most one
 session. Locks are established on demand; there is no separate operation to
 create or destroy a lock.

 A session lock is acquired using the
 PTDiffusionSession#lockWithName:completionHandler: method. If no other session
 owns the lock, the server will assign the lock to the calling session
 immediately. Otherwise, the server will record that the session is waiting to
 acquire the lock. A session can call `lock` more than once for a given session
 lock; if the lock is acquired, all calls will complete successfully with equal
 PTDiffusionSessionLock instances.

 If a session closes, the session locks it owns are automatically released. A
 session can also release a lock using the #unlockWithCompletionHandler: method.
 When a session lock is released and other sessions are waiting to acquire the
 lock, the server will arbitrarily select one of the waiting sessions and notify
 it that it has acquired the lock. All of the newly selected session's pending
 `lock` calls will complete normally. Other sessions will continue to wait.

 The PTDiffusionSession#lockWithName:scope:completionHandler: method takes a
 scope parameter that provides the further option of automatically releasing the
 lock when the session loses its connection to the server.

 There is no association between a lock and a thread. If a session calls `lock`
 for a lock it already owns, the call will complete normally and immediately
 with a PTDiffusionSessionLock instance that is equal to the one returned when
 the lock was originally acquired. A single call to `unlock` will release this
 session's claim to a lock.

 Lock ownership can be lost due to an independent event such as loss of
 connection, and not only due to the use of the locking API by the owner.
 Consequently, the session should poll using #owned to check that it still owns
 the lock before accessing the protected resource.

 ### Race conditions

 This session lock API has inherent race conditions. Even if an application is
 coded correctly to protect a shared resource using session locks, there may be
 a period where two or more sessions concurrently access the resource. The races
 arise for several reasons including

 - due to the *check-then-act* approach of polling #owned, the lock can be lost
 after the check has succeeded but before the resource is accessed;
 - the server can detect a session is disconnected and assign the lock to
 another session before the original session has detected the disconnection.

 Despite this imprecision, session locks provide a useful way to coordinate
 session actions.

 @since 6.3
 */
@interface PTDiffusionSessionLock : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 The name of the session lock.

 @since 6.3
 */
@property(nonatomic, readonly) NSString* name;

/**
 A value that identifies the acquisition of the lock with the given #name.
 Session locks that are acquired later are guaranteed to have bigger sequence
 values, allowing the sequence number to be used as a fencing token.

 @since 6.3
 */
@property(nonatomic, readonly) SInt64 sequence;

/**
 Whether the session lock is still owned by the session. This method may be
 manually polled but does not support KVO.

 @since 6.3
 */
@property(readonly, getter=isOwned) BOOL owned;

/**
 The scope of the lock.

 The scope determines when the lock will be released automatically.

 If a session makes multiple lock requests for a lock using different scopes,
 and the server assigns the lock to the session fulfilling the requests, the
 lock will be given the weakest scope
 (PTDiffusionSessionLockScope#unlockOnConnectionLoss). Consequently, an
 individual request can complete with a lock that has a different scope to that
 requested.

 @see PTDiffusionSession#lockWithName:scope:completionHandler:

 @since 6.3
 */
@property(nonatomic, readonly) PTDiffusionSessionLockScope* scope;

/**
 Release the session lock, if owned.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 On successful completion, this session will no longer own the named session
 lock, and `wasOwned` will wrap a `BOOL` value where `YES` indicates this
 session previously owned the lock and `NO` indicates that it did not.

 On completion with failure, this session does not own the session lock. The
 common reason for failure, indicated by the error reported, is that the session
 is closed.

 @exception NSInvalidArgumentException Raised if completionHandler is `nil`.

 @since 6.3
 */
-(void)unlockWithCompletionHandler:(void (^)(NSNumber * _Nullable wasOwned, NSError * _Nullable error))completionHandler;

/**
 Compares the receiver to the given session lock.

 @param sessionLock The session lock object with which to compare the receiver.

 @return `YES` if the session lock is equal to the receiver, otherwise `NO`.

 @since 6.3
 */
-(BOOL)isEqualToSessionLock:(nullable PTDiffusionSessionLock *)sessionLock;

@end

NS_ASSUME_NONNULL_END
