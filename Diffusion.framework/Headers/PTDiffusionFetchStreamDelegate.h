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
#import <Diffusion/PTDiffusionStreamDelegate.h>

@class PTDiffusionContent;
@class PTDiffusionStream;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The fetch stream delegate protocol defines the methods to be implemented
 by classes wishing to receive responses to topic fetch requests.

 @see PTDiffusionTopicsFeature

 @since 5.6
 */
@protocol PTDiffusionFetchStreamDelegate <PTDiffusionStreamDelegate>

/**
 A fetch response was received for a topic path handled by the fetch stream.

 @param stream The fetch stream that received the fetch response.

 @param topicPath The topic path that was fetched.

 @param content The content of the fetched topic.

 @since 5.6
 */
-(void)diffusionStream:(PTDiffusionStream *)stream
     didFetchTopicPath:(NSString *)topicPath
               content:(PTDiffusionContent *)content;

@end

NS_ASSUME_NONNULL_END
