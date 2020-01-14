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

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Builder for queries that select a range of events from a time series.

 @since 6.0
 */
@interface PTDiffusionTimeSeriesRangeQuery : NSObject <NSCopying>

/**
 Return a copy of the receiver configured to perform a value range query with
 the view range set to the entire time series.

 <strong>Operator type:</strong> value range.

 @return a copy of the receiver configured to perform a view range query with a
 new view range that selects the entire time series.
 
 @since 6.0
 */
-(instancetype)forValues;

/**
 Return a copy of the receiver configured to perform an edit range query with
 the view range set to the entire time series.

 <strong>Operator type:</strong> value range.

 @return a copy of the receiver configured to perform an edit range query with a
 new view range that selects the entire time series.
 
 @since 6.0
 */
-(instancetype)forEdits;

/**
 Return a copy of the receiver configured to perform a value range query with
 the edit range set to the entire time series.

 This operator can only be applied to value range queries. Newly initialised
 range query instances are value range queries. The @ref forValues operator can
 be used to create a value range query from an edit range query.

 <strong>Operator type:</strong> edit range.

 @return a copy of the receiver configured to perform a view range query with a
 new edit range that selects the entire time series, or `nil` if this is not a
 value range query.

 @since 6.0
 */
-(nullable instancetype)editRange;

/**
 Return a copy of the receiver configured to perform an edit range query with
 the edit range that selects all edits in the entire time series.

 This operator can only be applied to edit range queries. Newly initialised
 range query instances are value range queries. The @ref forEdits operator can
 be used to create an edit range query from a value range query.

 <strong>Operator type:</strong> edit range.

 @return a copy of the receiver configured to perform an edit range query with a
 new edit range that selects all edits in the entire time series, or `nil` if
 this is not an edit range query.

 @since 6.0
 */
-(nullable instancetype)allEdits;

/**
 Return a copy of the receiver configured to perform an edit range query with
 the edit range that selects latest edits in the entire time series.

 This operator can only be applied to edit range queries. Newly initialised
 range query instances are value range queries. The @ref forEdits operator can
 be used to create an edit range query from a value range query.

 <strong>Operator type:</strong> edit range.

 @return a copy of the receiver configured to perform an edit range query with a
 new edit range that selects the latest edits in the entire time series, or
 `nil` if this is not an edit range query.

 @since 6.0
 */
-(nullable instancetype)latestEdits;

/**
 Return a copy of the receiver with the anchor of the current range configured
 to be an absolute sequence number.

 <strong>Operator type:</strong> anchor.

 @param sequence absolute sequence number specifying the anchor of the returned
 range.

 @return a copy of the receiver with a new anchor.
 
 @exception NSInvalidArgumentException if sequence is greater than `INT64_MAX`.

 @since 6.0
 */
-(instancetype)fromSequence:(UInt64)sequence;

/**
 Return a copy of the receiver with the anchor of the current range configured
 to be the start of the time series.

 There is a difference between `fromStart` and `fromSequence:0` if the range
 also ends before the first event of the time series. For example,
 `[[query fromStart] toStart]` is always empty, but
 `[[query fromSequence:0] toStart]` includes the event with sequence number `0`.

 <strong>Operator type:</strong> anchor.

 @return a copy of the receiver with a new anchor.

 @since 6.0
 */
-(instancetype)fromStart;

/**
 Return a copy of the receiver with the anchor of the current range configured
 to be an absolute time.

 <strong>Operator type:</strong> anchor.

 @param date absolute time specifying the anchor of range.

 @return a copy of the receiver with a new anchor.

 @since 6.0
 */
-(instancetype)fromDate:(NSDate *)date;

/**
 Return a copy of the receiver with the anchor of the current range configured
 to be a relative offset before the end of the time series.

 <strong>Operator type:</strong> anchor.

 @param count specifies the anchor as a number of events before the end of the
 time series. For value range queries, count is the number of original events.
 For edit range queries, count is the number of events of any type.

 @return a copy of the receiver with a new anchor.

 @exception NSInvalidArgumentException if count is greater than `INT64_MAX`.

 @since 6.0
 */
-(instancetype)fromLastWithCount:(UInt64)count;

/**
 Return a copy of the receiver with the anchor of the current range configured
 to be a relative time from the timestamp of the last event in the time series.

 <strong>Operator type:</strong> anchor.

 @param timeInterval specifies anchor relative to the timestamp of the latest
 event in the time series.

 @return a copy of the receiver with a new anchor.

 @exception NSInvalidArgumentException if timeInterval is negative.

 @since 6.0
 */
-(instancetype)fromLastWithTimeInterval:(NSTimeInterval)timeInterval;

/**
 Return a copy of the receiver with the span of the current range configured to
 end at an absolute sequence number.

 <strong>Operator type:</strong> span.

 @param sequence absolute sequence number specifying the end of the returned
 range.

 @return a copy of the receiver with a new span.
 
 @exception NSInvalidArgumentException if sequence is greater than `INT64_MAX`.

 @since 6.0
 */
-(instancetype)toSequence:(UInt64)sequence;

/**
 Return a copy of the receiver with the span of the current range configured to
 end at the start of the time series.

 There is a difference between `toStart` and `toSequence:0` if the range also
 starts before the first event of the time series. For example,
 `[[query fromStart] toStart]` is always empty, but
 `[[query fromStart] toSequence:0]` includes the event with sequence number `0`.

 <strong>Operator type:</strong> span.

 @return a copy of the receiver with a new span.
 
 @since 6.0
 */
-(instancetype)toStart;

/**
 Return a copy of the receiver with the span of the current range configured to
 end at an absolute time.

 <strong>Operator type:</strong> span.

 @param date absolute time specifying the end of the range.

 @return a copy of the receiver with a new span.
 
 @since 6.0
 */
-(instancetype)toDate:(NSDate *)date;

/**
 Return a copy of the receiver with the span of the current range configured to
 select a range of events following the anchor.

 <strong>Operator type:</strong> span.

 @param count specifies the end of the range of events to select following the
 anchor. For value range queries, count is the number of original events. For
 edit range queries, count is the number of events of any type.

 @return a copy of the receiver with a new span.

 @exception NSInvalidArgumentException if count is greater than `INT64_MAX`.

 @since 6.0
 */
-(instancetype)nextWithCount:(UInt64)count;

/**
 Return a copy of the receiver with the span of the current range configured to
 select a temporal range of events following the anchor.

 <strong>Operator type:</strong> span.

 @param timeInterval the time span of events following the anchor to select.

 @return a copy of the receiver with a new span.

 @exception NSInvalidArgumentException if timeInterval is negative.

 @since 6.0
 */
-(instancetype)nextWithTimeInterval:(NSTimeInterval)timeInterval;

/**
 Return a copy of the receiver with the span of the current range configured to
 select a range of events preceding the anchor.

 <strong>Operator type:</strong> span.

 @param count specifies the end of the range of events to select preceding the
 anchor. For value range queries, count is the number of original events. For
 edit range queries, count is the number of events of any type.

 @return a copy of the receiver with a new span.

 @exception NSInvalidArgumentException if count is greater than `INT64_MAX`.

 @since 6.0
 */
-(instancetype)previousWithCount:(UInt64)count;

/**
 Return a copy of the receiver with the span of the current range configured to
 select a temporal range of events preceding the anchor.

 <strong>Operator type:</strong> span.

 @param timeInterval the time span of events preceding the anchor to select.

 @return a copy of the receiver with a new span.

 @exception NSInvalidArgumentException if timeInterval is negative.

 @since 6.0
 */
-(instancetype)previousWithTimeInterval:(NSTimeInterval)timeInterval;

/**
 Return a copy of the receiver with the span of the current range configured to
 end a number of events before the end of the time series.

 <strong>Operator type:</strong> span.

 @param count specifies the end of the range of events to select as a number of
 events before the end of the time series. For value range queries, count is the
 number of original events. For edit range queries, count is the number of
 events of any type.

 @return a copy of the receiver with a new span.

 @exception NSInvalidArgumentException if count is greater than `INT64_MAX`.

 @since 6.0
 */
-(instancetype)untilLastWithCount:(UInt64)count;

/**
 Return a copy of the receiver with the span of the current range configured to
 end at a relative time from the timestamp of the last event in the time series.


 <strong>Operator type:</strong> span.

 @param timeInterval specifies the end of the range of events to select relative
 to the timestamp of the latest event in the time series.

 @return a copy of the receiver with a new span.

 @exception NSInvalidArgumentException if timeInterval is negative.

 @since 6.0
 */
-(instancetype)untilLastWithTimeInterval:(NSTimeInterval)timeInterval;

/**
 Return a copy of the receiver that returns at most count events.

 If the query would otherwise select more than count events, only the latest
 count values (those with the highest sequence numbers) are returned.

 This is most useful when a temporal span has been configured with
 @ref nextWithTimeInterval: or @ref previousWithTimeInterval: where the potential
 number of returned events is unknown.

 PTDiffusionTimeSeriesQueryResult::complete can be used to determine whether
 a query has returned an incomplete result.

 <strong>Operator type:</strong> limit.

 @param count the maximum number of events to return.

 @return a copy of the receiver with a new limit.

 @exception NSInvalidArgumentException if count is greater than `INT64_MAX`.

 @since 6.0
 */
-(instancetype)limitWithCount:(UInt64)count;

/**
 Compares the receiver to the given time series range query.

 @param timeSeriesRangeQuery The time series range query object with which
 to compare the receiver.

 @return `YES` if it is identical to the receiver, otherwise `NO`.

 @since 6.0
 */
-(BOOL)isEqualToTimeSeriesRangeQuery:(nullable PTDiffusionTimeSeriesRangeQuery *)timeSeriesRangeQuery;

@end

NS_ASSUME_NONNULL_END
