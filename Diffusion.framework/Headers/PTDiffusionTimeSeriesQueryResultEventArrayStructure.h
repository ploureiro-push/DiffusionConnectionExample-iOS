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
#import <Diffusion/PTDiffusionEnumeration.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Describes the structural properties of the array of events presented
 by a time series query result.

 @see PTDiffusionTimeSeriesQueryResult

 @since 6.0
 */
@interface PTDiffusionTimeSeriesQueryResultEventArrayStructure : PTDiffusionEnumeration

/**
 The array is presented in time series order, with the following properties:

 - The sequence of each event in the array is unique.
 - The array is ordered by sequence. The sequence of each subsequent event
   in the stream is greater than its predecessor.
 - Edit event timestamps may lie outside the query range.
 - The array can have multiple edit events for the same original event.
 
 @since 6.0
 */
+(instancetype)editEventStream;

/**
 The array is ordered by the original event sequence number, presenting edit
 events instead of the original events they replace.

 The array has the following properties:

 - The sequence of each event in the stream is unique.
 - The original event sequence of each event in the stream is unique.
 - The stream is ordered by original event sequence. The original event sequence
   of each subsequent event in the stream is greater than its predecessor.
 - If no events have been removed from the time series, the original event
   sequence of each subsequent event is one greater than its predecessor.
 - If an event is an original event, the query found no corresponding edit
   events.
 - If an event is an edit event, its timestamp attribute may lie outside the
   query range. Consequentially, the sequence and timestamp attributes of the
   events may be non-sequential.

 @since 6.0
 */
+(instancetype)valueEventStream;

@end

NS_ASSUME_NONNULL_END
