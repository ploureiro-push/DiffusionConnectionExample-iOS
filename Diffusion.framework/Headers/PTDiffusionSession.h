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

@class PTDiffusionMessagingControlFeature;
@class PTDiffusionMessagingFeature;
@class PTDiffusionPingsFeature;
@class PTDiffusionSecurityFeature;
@class PTDiffusionSessionConfiguration;
@class PTDiffusionSessionId;
@class PTDiffusionSessionLock;
@class PTDiffusionSessionLockAttempt;
@class PTDiffusionSessionLockScope;
@class PTDiffusionSessionState;
@class PTDiffusionSubscriptionControlFeature;
@class PTDiffusionTimeSeriesFeature;
@class PTDiffusionTopicControlFeature;
@class PTDiffusionTopicNotificationsFeature;
@class PTDiffusionTopicsFeature;
@class PTDiffusionTopicUpdateControlFeature;
@class PTDiffusionTopicUpdateFeature;
@class PTDiffusionTopicViewsFeature;

@protocol PTDiffusionErrorListener;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A session represents a single connection to a single Diffusion server.
 
 The @ref md_quick_start "Quick Start" guide provides basic instructions on how
 to get connected to a Diffusion server.

 Also see:
 - @ref md_session_filters "Session Filters".
 - @ref md_session_properties "Session Properties".

 @see PTDiffusionSessionStateChange

 @since 5.6
 */
@interface PTDiffusionSession : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Starts asynchronously connecting to a Diffusion server using the given session configuration.
 
 @param url The location of the server to connect to. Encapsulates host, port and protocol to use.
 Must be absolute.

 @param configuration The configuration options to connect with.

 @param completionHandler The completion handler to call on connection success or failure.
 The completion handler will be called from the main dispatch queue and will only be called once.
 
 @note Your completion handler _must_ store a strong reference to the session instance in order
 for it to remain open.

 @note The completion handler block is called after the session's state property has been set
 to connected but before those observing through the notification center are informed.

 @since 5.6
 */
+(void)openWithURL:(NSURL *)url
     configuration:(PTDiffusionSessionConfiguration *)configuration
 completionHandler:(void (^)(PTDiffusionSession * _Nullable session, NSError * _Nullable error))completionHandler;

/**
 Starts asynchronously connecting to a Diffusion server using the default session configuration.

 @param url The location of the server to connect to. Encapsulates host, port and protocol to use.
 Must be absolute.

 @param completionHandler The completion handler to call on connection success or failure.
 The completion handler will be called from the main dispatch queue and will only be called once.

 @note Your completion handler _must_ store a strong reference to the session instance in order
 for it to remain open.
 
 @note The completion handler block is called after the session's state property has been set
 to connected but before those observing through the notification center are informed.
 
 @since 5.6
 */
+(void)openWithURL:(NSURL *)url
 completionHandler:(void (^)(PTDiffusionSession * _Nullable session, NSError * _Nullable error))completionHandler;

/**
 The configuration used to open the session.

 @since 5.6
 */
@property(nonatomic, readonly, copy) PTDiffusionSessionConfiguration* configuration;

/**
 The unique identifier for the session as assigned by the server it connects to.
 
 This property is Key-Value Observable with changes being notified on the main dispatch queue.
 */
@property(nonatomic, readonly) PTDiffusionSessionId* sessionId;

/**
 The name of the security principal associated with the session.

 @return The principal name. If the session has no associated principal, it is
 known as an anonymous session, in which case the empty string
 anonymousPrincipal will be assigned to this property.
 
 @since 6.0
 */
@property(nonatomic, readonly) NSString* principal;

/**
 Value assigned to the principal property if this is an anonymous session.
 
 @since 6.0
 */
+(NSString *)anonymousPrincipal;

/**
 This constant can be used instead of a property key in requests for session
 property values to indicate that all fixed session properties are required.

 @since 6.0
 */
+(NSString *)allFixedProperties;

/**
 This constant can be used instead of a property key in requests for session
 property values to indicate that all user defined session properties are
 required.

 @since 6.0
 */
+(NSString *)allUserProperties;

/**
 Session property key for session roles.
 
 @since 6.2
 */
+(NSString *)rolesPropertyKey;

/**
 Session property key for session identifier.

 @see PTDiffusionSessionId

 @since 6.2
 */
+(NSString *)sessionIdPropertyKey;

/**
 Session property key for principal.

 @since 6.2
 */
+(NSString *)principalPropertyKey;

/**
 Session property key for connector name.

 @since 6.2
 */
+(NSString *)connectorPropertyKey;

/**
 Session property key for transport.

 @since 6.2
 */
+(NSString *)transportPropertyKey;

/**
 Session property key for client type.

 @since 6.2
 */
+(NSString *)clientTypePropertyKey;

/**
 Session property key for country code.

 @since 6.2
 */
+(NSString *)countryPropertyKey;

/**
 Session property key for language code.

 @since 6.2
 */
+(NSString *)languagePropertyKey;

/**
 Session property key for server name.

 @since 6.2
 */
+(NSString *)serverNamePropertyKey;

/**
 Session property key for client IP address.

 @since 6.2
 */
+(NSString *)clientIPPropertyKey;

/**
 Session property key for client latitude.

 @since 6.2
 */
+(NSString *)latitudePropertyKey;

/**
 Session property key for client longitude.

 @since 6.2
 */
+(NSString *)longitudePropertyKey;

/**
 Session property key for client start time.

 @since 6.2
 */
+(NSString *)startTimePropertyKey;

/**
 The current state of the session.
 
 This property is Key-Value Observable with changes being notified on the main dispatch queue.
 KVO notifications are sent before the invocation of any callback handler blocks.
 
 @note Session state can also be observed using the notification center.
 See PTDiffusionSessionStateChange for details.

 @since 5.7
 */
@property(nonatomic, readonly) PTDiffusionSessionState* state;

/**
 The delegate to use to report unexpected, non-fatal errors to.

 @since 6.0
 */
@property(nonatomic, weak) id<PTDiffusionErrorListener> errorListener;

/**
 Close the session. Once closed a session cannot be restarted.

 @since 5.6
 */
-(void)close;

/**
 The Topics feature provides the capability to receive streamed topic updates and/or
 fetch the state of topics.

 @since 5.6
 */
@property(nonatomic, readonly) PTDiffusionTopicsFeature* topics;

/**
 The Topic Control features provides the capability to manage topics.
 
 @since 5.7
 */
@property(nonatomic, readonly) PTDiffusionTopicControlFeature* topicControl;

/**
 The Topic Update Control feature provides the capability to update topics.

 @deprecated Since 6.3. PTDiffusionTopicUpdateControlFeature has been replaced
 by PTDiffusionTopicUpdateFeature, which provides equivalent and additional
 functionality such as conditional updates. This property will be removed in a
 future release.

 @since 5.7
 */
@property(nonatomic, readonly) PTDiffusionTopicUpdateControlFeature* topicUpdateControl
    __deprecated_msg("Will be removed in a future release.");

/**
 The Topic Update feature provides a client session with the ability to update
 topics.

 @since 6.3
 */
@property(nonatomic, readonly) PTDiffusionTopicUpdateFeature* topicUpdate;

/**
 The Messaging feature provides messaging capabilities.

 @since 5.6
 */
@property(nonatomic, readonly) PTDiffusionMessagingFeature* messaging;

/**
 The Messaging Control feature provides the capability to use messaging
 functionality to communicate directly with other client sessions.
 
 @since 6.0
 */
@property(nonatomic, readonly) PTDiffusionMessagingControlFeature* messagingControl;

/**
 The Security feature provides a client session with the ability to change
 the associated principal.
 
 @since 5.6
 */
@property(nonatomic, readonly) PTDiffusionSecurityFeature* security;

/**
 The Pings feature provides a client session with the ability to test the
 roundtrip time associated with sending a request to the server and receiving
 the associated response.
 
 @since 5.7
 */
@property(nonatomic, readonly) PTDiffusionPingsFeature* pings;

/**
 The Time Series feature provides a client session with the ability to update
 and query time series topics.

 @since 6.0
 */
@property(nonatomic, readonly) PTDiffusionTimeSeriesFeature* timeSeries;

/**
 The Topic Notifications feature allows a client session to receive
 notifications about changes to selected topics.

 @since 6.1
 */
@property(nonatomic, readonly) PTDiffusionTopicNotificationsFeature* topicNotifications;

/**
 The Subscription Control feature allows a client session to subscribe or
 unsubscribe other sessions to topics, as well as also providing a mechanism for
 handling requests to subscribe to routing topics.

 @since 6.1
 */
@property(nonatomic, readonly) PTDiffusionSubscriptionControlFeature* subscriptionControl;

/**
 The Topic Views feature allows a client session to manage topic views.

 @since 6.3
 */
@property(nonatomic, readonly) PTDiffusionTopicViewsFeature* topicViews;

/**
 Attempt to acquire a session lock.

 The completion handler block will be called with the requested lock if the
 server assigns it to the session. Otherwise, the completion handler block will
 be called with an error indicating why the lock could not be acquired.

 Acquiring the lock can take an arbitrarily long time if other sessions are
 competing for the lock. The server will retain the session's request for the
 lock until it is assigned to the session, the session is closed, or the session
 cancels the CompletableFuture.

 A session can call this method multiple times. If the lock is acquired, all
 calls will complete successfully with equal SessionLocks.

 Calling cancel on the returned PTDiffusionCancellable has no effect on other
 pending calls to acquire this lock.

 Upon successful acquisition, the session owns the lock and is responsible for
 unlocking it. When calling cancel on the returned PTDiffusionCancellable, take
 care that it has not already completed by checking the return value. The
 following Swift code releases the lock if the request could not be canceled.

     let attempt = session.lock(withName: "my-lock") { (lock, error) in
         / / ..
     }

     if (!attempt.cancel()) {
         attempt.lock?.unlock() { (wasOwned, error) in }
     }

 A session that acquires a lock will remain its owner until it is unlocked or
 the session closes. The variant of this methods that takes a scope parameter
 provides the further option of releasing the lock when the session loses its
 connection to the server.

 ### Access control

 To allow fine-grained access control, lock names are interpreted as path names,
 controlled with the `ACQUIRE_LOCK` topic permission. This allows permission to
 be granted to a session to acquire the lock `update-topic/a` while preventing
 the session from acquiring the lock `update-topic/b`, for example.

 @param name The name of the session lock.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 If this session has successfully acquired the session lock, or this session
 already owns the session lock, the completion handler will be called with the
 lock instance.

 If the completion handler is called with an error to indicate failure, this
 session does not own the session lock. Common reasons for failure include:

 - The calling session does not have the `AQUIRE_LOCK` permission for this lock
   name.
 - The session is closed.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @see #lockWithName:scope:completionHandler:

 @since 6.3
 */
-(PTDiffusionSessionLockAttempt *)lockWithName:(NSString *)name
                             completionHandler:(void (^)(PTDiffusionSessionLock * _Nullable lock, NSError * _Nullable error))completionHandler;

/**
 Variant of #lockWithName:completionHandler: that provides control over when a
 lock will be released.

 If called with PTDiffusionSessionLockScope#unlockOnSessionLoss, this method
 behaves exactly like #lockWithName:completionHandler:.

 If called with PTDiffusionSessionLockScope#unlockOnConnectionLoss, any lock
 that is returned will be unlocked if the session loses its connection to the
 server. This is useful to allow another session to take ownership of the lock
 while this session is reconnecting.

 @param name The name of the session lock

 @param scope Preferred scope. The scope of a lock controls when it will be
 released automatically. If a session makes multiple requests for a lock using
 different scopes, and the server assigns the lock to the session fulfilling the
 requests, the lock will be given the weakest scope
 (PTDiffusionSessionLockScope#unlockOnConnectionLoss).

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @see #lockWithName:completionHandler:

 @since 6.3
 */
-(PTDiffusionSessionLockAttempt *)lockWithName:(NSString *)name
                                         scope:(PTDiffusionSessionLockScope *)scope
                             completionHandler:(void (^)(PTDiffusionSessionLock * _Nullable lock, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
