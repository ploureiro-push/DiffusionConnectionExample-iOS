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
 @brief Metadata associated with a time series event.

 @see PTDiffusionTimeSeriesEvent

 @since 6.0
 */
@interface PTDiffusionTimeSeriesEventMetadata : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Sequence number identifying this event within its time series.
 Assigned by the server when the event is created.

 Sequence numbers are unique within a time series. Each event appended to a
 time series is assigned a sequence number that is equal to the sequence
 number of the preceding event plus one.

 @return The sequence number; never higher than `INT64_MAX`.
 
 @since 6.0
 */
@property(nonatomic, readonly) UInt64 sequence;

/**
 Event timestamp. Assigned by the server when the event is created.

 Events do not have unique timestamps. Events with different sequence numbers
 may have the same timestamp.

 Subsequent events in a time series usually have timestamps that are greater or
 equal to the timestamps of earlier events, but this is not guaranteed due to
 changes to the time source used by the server.

 @return The difference, measured in milliseconds, between the time the server
 added the event to the time series and midnight, January 1, 1970 UTC.
 
 @since 6.0
 */
@property(nonatomic, readonly) SInt64 timestamp;

/**
 Server-authenticated identity of the session that created the event.

 @return The principal that created the event, or
 [PTDiffusionSession anonymousPrincipal] if the session that created the event
 was not authenticated

 @since 6.0
 */
@property(nonatomic, readonly) NSString* author;

/**
 Compares the receiver to the given time series event metadata.

 @param timeSeriesEventMetadata The time series event metadata object with which
 to compare the receiver.

 @return `YES` if it matches the receiver for just metadata elements (sequence,
 timestamp and author), otherwise `NO`.

 @since 6.0
 */
-(BOOL)isEqualToTimeSeriesEventMetadata:(nullable PTDiffusionTimeSeriesEventMetadata *)timeSeriesEventMetadata;

@end

NS_ASSUME_NONNULL_END
