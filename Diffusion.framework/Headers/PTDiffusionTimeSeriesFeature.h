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
#import <Diffusion/PTDiffusionFeature.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The Time Series feature provides a client session with the ability to
 update and query time series topics.

 The Time Series feature for a session can be obtained from the session's
 `timeSeries` property.
 
 @see PTDiffusionSession
 
 @since 6.0
 */
@interface PTDiffusionTimeSeriesFeature : PTDiffusionFeature

@end

NS_ASSUME_NONNULL_END
