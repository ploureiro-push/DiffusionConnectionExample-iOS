//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2015, 2017 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A topic selector identifies one or more topics.
 
 Topic selector objects are only used by the local client library and are immutable.
 
 For more information on topic selector evaluation see the
 @ref md_topic_selectors "Topic Selectors" guide.
 
 @see PTDiffusionMessagingFeature
 @see PTDiffusionTopicsFeature
 
 @since 5.6
 */
@interface PTDiffusionTopicSelector : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Return a topic selector object initialized with the given expression.
 
 @param expression The expression to be used for evalutating topic paths.

 @since 5.6
 */
+(instancetype)topicSelectorWithExpression:(NSString *)expression;

/**
 The expression association with the receiver.

 @since 5.6
 */
@property(nonatomic, readonly) NSString* expression;

/**
 The topic path prefix from this selector pattern.

 Returns the largest fixed topic path that begins the selector expression.
 For path selectors, this is the entire path. For split pattern or full pattern
 selectors, this is a topic path up to, but not including, the first part of the
 path that contains a regular expression.

 For selector sets, this method will return the largest prefix that is common to
 all included selectors.

 If there is no common prefix, an empty string will be returned.

 @since 6.1
 */
@property(nonatomic, readonly) NSString* pathPrefix;

/**
 Evaluate this receiver against a topic path.
 
 @param topicPath The topic path to evaluate against.
 May be `nil` or an empty string, in which case this method returns `NO`.

 @return `YES` if the receiver selects the topicPath.

 @since 5.6
 */
-(BOOL)selectsTopicPath:(nullable NSString *)topicPath;

/**
 Compares the receiver to the given topic selector.

 @param topicSelector The topic selector object with which to compare the receiver.

 @return `YES` if the topic selector is equal to the receiver, otherwise `NO`.

 @since 5.6
 */
-(BOOL)isEqualToTopicSelector:(nullable PTDiffusionTopicSelector *)topicSelector;

/**
 Create a selector that matches if any of the provided selectors match.

 @param selectors The selectors
 
 @return A selector which matches if any of selectors do.

 @since 5.9
 */
+(instancetype)topicSelectorWithAnyOf:(NSArray<PTDiffusionTopicSelector*>*)selectors;

/**
 A convenience wrapper around `topicSelectorWithAnyOf:`.

 @param expressions The selector expressions.

 @return A selector which matches if any of `expressions` do

 @since 5.9
 */
+(instancetype)topicSelectorWithAnyExpression:(NSArray<NSString*>*)expressions;

@end

NS_ASSUME_NONNULL_END
