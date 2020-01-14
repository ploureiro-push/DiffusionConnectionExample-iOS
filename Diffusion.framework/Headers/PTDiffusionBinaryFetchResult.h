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

@class PTDiffusionBinaryFetchTopicResult;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Encapsulates the results from a binary fetch operation issued to the
 server.

 A binary fetch operation is issued using the
 PTDiffusionFetchRequest#fetchBinaryValuesWithTopicSelectorExpression:completionHandler:
 method.

 @since 6.2
 */
@interface PTDiffusionBinaryFetchResult : PTDiffusionFetchResult

/**
 The results from the fetch operation, in path order, each representing a single
 topic selected by the fetch operation.

 @since 6.2
 */
@property(nonatomic, readonly) NSArray<PTDiffusionBinaryFetchTopicResult *> * binaryResults;

@end

NS_ASSUME_NONNULL_END
