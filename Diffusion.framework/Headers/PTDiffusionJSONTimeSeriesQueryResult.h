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
#import <Diffusion/PTDiffusionTimeSeriesQueryResult.h>

@class PTDiffusionJSONTimeSeriesEvent;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Query result providing an array of JSON time series events.

 @since 6.0
 */
@interface PTDiffusionJSONTimeSeriesQueryResult : PTDiffusionTimeSeriesQueryResult

/**
 The JSON time series events.

 @see eventArrayStructure

 @since 6.0
 */
@property(nonatomic, readonly) NSArray<PTDiffusionJSONTimeSeriesEvent *>* jsonEvents;

@end

NS_ASSUME_NONNULL_END
