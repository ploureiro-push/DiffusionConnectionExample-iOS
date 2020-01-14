//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2016, 2019 Push Technology Ltd., All Rights Reserved.
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

@class PTDiffusionTopicTreeRegistration;
@class PTDiffusionTopicUpdater;

@protocol PTDiffusionTopicUpdateSource;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The topic update control feature provides a client session with the capability to
 update topics at the server.
 
 In order to update any topic the client must have suitable permissions for that topic.
 
 A client does not have to be subscribed to a topic in order to update it.
 
 Topics may be updated exclusively or non-exclusively.
 In exclusive mode the client registers as the update source for a particular branch of the
 topic tree and once registered no other client will be able to update topics in that branch.
 In non-exclusive mode a client may update any topic as long as there is no exclusive update
 source for its branch.
 
 In either mode a PTDiffusionTopicUpdater is needed to send the updates.
 The way in which the updater is obtained is dependent upon the mode.
 
 Updaters are thread-safe, but do not update topics from different threads as order can not
 be guaranteed.

 @deprecated Since 6.3. This class will be removed in a future release. It has
 been replaced by PTDiffusionTopicUpdateFeature, which provides equivalent and
 additional functionality such as conditional updates.

 @since 5.7
 */
__deprecated_msg("Will be removed in a future release.")
@interface PTDiffusionTopicUpdateControlFeature : PTDiffusionFeature

/**
 @brief Register an update source to be used for exclusive updating.

 Registers an object conforming to the PTDiffusionTopicUpdateSource protocol for a branch of
 the topic tree.

 This registers the current client session as an update source for a specified branch of the
 topic tree, thus allowing updating of topics in that branch.

 If the registration is successful the completion handler will be provided with a registration.
 This may be used to deregister the update source from the associated branch at a later point in time.

 When an update source is registered, it will either be active or on standby, depending on the initial
 state that the server assigns.
 Subsequent state changes will result in further calls to these methods.

 An update source is active when the server determines it is valid to send topic updates on the
 specified branch. In this case the update source is provided with a PTDiffusionTopicUpdater object
 to use to perform updates.

 An update source is on standby when this source may no longer provide updates on the specified branch.
 Any updater instances previously provided to the update source are now invalid.
 
 @param updateSource An object to be told when the active or on standby.
 
 @param topicPath The topic path to the branch of the topic tree to be exclusively updated by this
 update source when it's active.
 
 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will be `nil` and
 the `registration` argument will not be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.

 @note If the session is closing or closed when this method is called, the
 completion handler block will be called with an error, while the topic update
 source will receive no messages.

 @exception NSInvalidArgumentException If any arguments are `nil`.

 @since 5.7
 */
-(void)registerUpdateSource:(id<PTDiffusionTopicUpdateSource>)updateSource
               forTopicPath:(NSString *)topicPath
          completionHandler:(void (^)(PTDiffusionTopicTreeRegistration * _Nullable registration, NSError * _Nullable error))completionHandler;

/**
 @brief Returns an updater to be used for non-exclusive updating.
 
 The updater may be used to send updates to any topic that the client has permission to update.
 However, an update will fail if there is already a registered exclusive update source for the topic.
 
 If more than one client sends non-exclusive updates to the same topic, the updates are
 performed on a last update wins basis.
 
 @since 5.7
 */
@property(nonatomic, readonly) PTDiffusionTopicUpdater* updater;

@end

NS_ASSUME_NONNULL_END
