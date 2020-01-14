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
#import <Diffusion/PTDiffusionFetchResult.h>

@class PTDiffusionStringFetchTopicResult;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Encapsulates the results from a string fetch operation issued to the
 server.

 A string fetch operation is issued using the
 PTDiffusionFetchRequest#fetchStringValuesWithTopicSelectorExpression:completionHandler:
 method.

 @since 6.2
 */
@interface PTDiffusionStringFetchResult : PTDiffusionFetchResult

/**
 The results from the fetch operation, in path order, each representing a single
 topic selected by the fetch operation.

 @since 6.2
 */
@property(nonatomic, readonly) NSArray<PTDiffusionStringFetchTopicResult *> * stringResults;

@end

NS_ASSUME_NONNULL_END
