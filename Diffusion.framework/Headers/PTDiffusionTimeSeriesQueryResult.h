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

@class PTDiffusionTimeSeriesEvent;
@class PTDiffusionTimeSeriesQueryResultEventArrayStructure;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Query result providing an array of time series events.

 @since 6.0
 */
@interface PTDiffusionTimeSeriesQueryResult : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 If this result includes all events selected by the query then `YES`.
 
 When this property returns `YES` then the value returned by the selectedCount
 property will be the same as the count of the array returned by the events
 property.

 @since 6.0
 */
@property(nonatomic, readonly, getter=isComplete) BOOL complete;

/**
 The number of events selected by the query.
 
 This number may be greater than the count of the array returned by the events
 property due to a policy of the time series topic to limit the number of
 returned results, or the use a limit on the range query.

 @since 6.0
 */
@property(nonatomic, readonly) UInt64 selectedCount;

/**
 The structural properties of the events array.

 @see events
 
 @since 6.0
 */
@property(nonatomic, readonly) PTDiffusionTimeSeriesQueryResultEventArrayStructure* eventArrayStructure;

/**
 Compares the receiver to the given time series query result.

 @param timeSeriesQueryResult The time series query result object with which
 to compare the receiver.

 @return `YES` if it is identical to the receiver, otherwise `NO`.

 @since 6.0
 */
-(BOOL)isEqualToTimeSeriesQueryResult:(nullable PTDiffusionTimeSeriesQueryResult *)timeSeriesQueryResult;

@end

NS_ASSUME_NONNULL_END
