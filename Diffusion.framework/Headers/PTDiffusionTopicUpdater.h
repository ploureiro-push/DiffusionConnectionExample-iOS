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

@class PTDiffusionBytes;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A topic updater provides methods for an update source to update topics.
 
 An Updater can be used to send any number of updates.

 If this updater was obtained by an update source, being an exclusive updater,
 then the topics that may be updated are determined by the topic path used when
 registering the update source.
 
 @see PTDiffusionTopicUpdateControlFeature

 @deprecated Since 6.3. This class will be removed in a future release. It has
 been replaced by PTDiffusionUpdateStream which is accessed using
 PTDiffusionTopicUpdateFeature, providing equivalent and additional
 functionality such as conditional updates.

 @since 5.7
 */
__deprecated_msg("Will be removed in a future release.")
@interface PTDiffusionTopicUpdater : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Update the topic to the state represented by the supplied value, sending
 updates to subscribers if required.

 @param topicPath Identifies the topic to update.

 @param value Value representing the new state.

 @param completionHandler Block to be called asynchronously on success or failure.
 If the operation was successful, the `error` argument passed to the block will be `nil`.
 The completion handler will be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException If any of the supplied arguments are `nil`.

 @note The supplied value must always represent the new full topic state.

 @since 5.9
 */
-(void)updateWithTopicPath:(NSString *)topicPath
                     value:(PTDiffusionBytes *)value
         completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
