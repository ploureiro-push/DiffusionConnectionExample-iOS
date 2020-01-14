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

@class PTDiffusionTopicSelector;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A value updater may be used to update topics of a certain type by
 specifying new values.
 
 An updater can be used to send any number of updates.

 If this updater was obtained from an update source, the topics that can be
 updated are restricted by the topic path used to register the update source.

 @see PTDiffusionTopicUpdateControlFeature
 @see PTDiffusionTopicUpdater

 @deprecated Since 6.3. This class will be removed in a future release. It has
 been replaced by PTDiffusionUpdateStream which is accessed using
 PTDiffusionTopicUpdateFeature, providing equivalent and additional
 functionality such as conditional updates.

 @since 6.0
 */
__deprecated_msg("Will be removed in a future release.")
@interface PTDiffusionValueUpdater : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Removes values from the value cache.

 If a cached value is removed, the next update for a topic will transmit the
 whole value to the server rather than a delta.
 
 @param topicSelector Indicating the topics for which entries are to be removed.

 @exception NSInvalidArgumentException If the topicSelector argument is `nil`.

 @since 6.0
 */
-(void)removeCachedValuesWithTopicSelector:(PTDiffusionTopicSelector *)topicSelector;

/**
 A convenience method wrapping a call to `[self removeCachedValuesWithTopicSelector:]`

 @param expression The @ref md_topic_selectors "topic selector" expression to be
 evaluated locally, indicating the topics for which entries are to be removed.

 @exception NSInvalidArgumentException If the expression argument is `nil`.

 @since 6.0
 */
-(void)removeCachedValuesWithSelectorExpression:(NSString *)expression;

@end

NS_ASSUME_NONNULL_END
