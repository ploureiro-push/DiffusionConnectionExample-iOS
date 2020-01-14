//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2018 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionFetchTopicResult.h>

@class PTDiffusionTimeSeriesEvent;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Encapsulates the result from a time series fetch operation for a single
 selected topic.

 A time series fetch operation is issued using the
 PTDiffusionFetchRequest#fetchTimeSeriesEventsWithTopicSelectorExpression:completionHandler:
 method.

 @since 6.3
 */
@interface PTDiffusionTimeSeriesFetchTopicResult : PTDiffusionFetchTopicResult

/**
 Returns the latest event, or `nil` if the topic has no events.

 @since 6.3
 */
@property(nonatomic, readonly, nullable) PTDiffusionTimeSeriesEvent* event;

@end

NS_ASSUME_NONNULL_END
