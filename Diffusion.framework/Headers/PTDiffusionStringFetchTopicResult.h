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

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Encapsulates the result from a string fetch operation for a single
 selected topic.

 A string fetch operation is issued using the
 PTDiffusionFetchRequest#fetchStringValuesWithTopicSelectorExpression:completionHandler:
 method.

 @since 6.2
 */
@interface PTDiffusionStringFetchTopicResult : PTDiffusionFetchTopicResult

/**
 Returns the topic value, or `nil` if the topic has no value.

 @since 6.2
 */
@property(nonatomic, readonly, nullable) NSString* string;

@end

NS_ASSUME_NONNULL_END
