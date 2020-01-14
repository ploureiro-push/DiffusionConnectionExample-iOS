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

@class PTDiffusionRecordV2;
@class PTDiffusionTopicSpecification;
@class PTDiffusionValueStream;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Methods implemented by classes handling streamed events for record
 value topics.

 This protocol defines the methods to be implemented by classes wishing to
 receive streamed events when updates are received from the server for record
 topics.
 
 @see PTDiffusionRecordV2

 @since 6.0
 */
@protocol PTDiffusionRecordV2ValueStreamDelegate <PTDiffusionSubscriberStreamDelegate>

/**
 An update was received for a topic path handled by a record value stream.

 @param stream The value stream that received the update.

 @param topicPath The topic path that was updated.

 @param specification The specification for the updated topic.

 @param oldRecord The previous value. If `nil` then this is the first value.

 @param newRecord The new value derived from the last update received from the
 server.

 @since 6.0
 */
-(void)diffusionStream:(PTDiffusionValueStream *)stream
    didUpdateTopicPath:(NSString *)topicPath
         specification:(PTDiffusionTopicSpecification *)specification
             oldRecord:(nullable PTDiffusionRecordV2 *)oldRecord
             newRecord:(PTDiffusionRecordV2 *)newRecord;

@end

NS_ASSUME_NONNULL_END
