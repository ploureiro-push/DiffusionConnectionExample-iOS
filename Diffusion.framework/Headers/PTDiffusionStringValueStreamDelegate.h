//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2017 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionSubscriberStreamDelegate.h>

@class PTDiffusionTopicSpecification;
@class PTDiffusionValueStream;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Methods implemented by classes handling streamed events for string
 value topics.

 This protocol defines the methods to be implemented by classes wishing to
 receive streamed events when updates are received from the server for string
 topics.
 
 @see PTDiffusionPrimitive

 @since 6.0
 */
@protocol PTDiffusionStringValueStreamDelegate <PTDiffusionSubscriberStreamDelegate>

/**
 An update was received for a topic path handled by a string value stream.

 @param stream The topic stream that received the update.

 @param topicPath The topic path that was updated.

 @param specification The specification for the updated topic.
 
 @param oldString The previous value. If `nil` then this is either the first
 value, or the previous value was `nil` indicating no value.
 
 @param newString The new value derived from the last update received from the
 server, or `nil` if there is no value.

 @since 6.0
 */
-(void)diffusionStream:(PTDiffusionValueStream *)stream
    didUpdateTopicPath:(NSString *)topicPath
         specification:(PTDiffusionTopicSpecification *)specification
             oldString:(nullable NSString *)oldString
             newString:(nullable NSString *)newString;

@end

NS_ASSUME_NONNULL_END
