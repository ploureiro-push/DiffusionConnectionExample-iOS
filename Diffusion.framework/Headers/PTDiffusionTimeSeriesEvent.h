//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2017, 2018 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionFetchRequest.h>
#import <Diffusion/PTDiffusionTimeSeriesEventMetadata.h>

@class PTDiffusionBytes;
@class PTDiffusionTimeSeriesFetchResult;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief An event in a time series.

 Two instances are equal if and only if they have identical attributes.
 Typically two instances that have the same sequence number will be equal, but
 this may not be true if the event has changed on the server.

 @since 6.0
 */
@interface PTDiffusionTimeSeriesEvent : PTDiffusionTimeSeriesEventMetadata

/**
 If this is an edit event, returns the metadata of the original event that this
 event replaces; otherwise returns this event.
 
 The result is always the metadata of an original event, never that of an edit
 event.

 @since 6.0
 */
@property(nonatomic, readonly) PTDiffusionTimeSeriesEventMetadata* originalEvent;

/**
 If this is an edit event then `YES`, otherwise `NO` indicating that this is an
 original event.
 
 @since 6.0
 */
@property(nonatomic, readonly, getter=isEditEvent) BOOL editEvent;

/**
 The value associated with the event.

 @since 6.3
 */
@property(nonatomic, readonly) PTDiffusionBytes* bytes;

/**
 Compares the receiver to the given time series event.

 @param timeSeriesEvent The time series event object with which to compare the
 receiver.

 @return `YES` if it is identical to the receiver, otherwise `NO`.

 @since 6.0
 */
-(BOOL)isEqualToTimeSeriesEvent:(nullable PTDiffusionTimeSeriesEvent *)timeSeriesEvent;

@end

/**
 @brief Extension adding support to Topics feature fetch requests allowing them
 to be constrained to only those topics with a data type compatible with time
 series events.

 @since 6.3
 */
@interface PTDiffusionFetchRequest (PTDiffusionTimeSeriesEvent)

/**
 Sends a fetch request to the server, specifying that values should be returned
 for selected topics, constraining the selection to time series topics. Any
 topic types specified in a previous call to #topicTypes: that cannot be read as
 a time series will be removed from the list of topic types.

 Results are returned for all topics matching the selector that satisfy the
 request constraints within any range defined by #fromTopicPath: /
 #afterTopicPath: and/or #toTopicPath: / #beforeTopicPath:

 @param expression Specifies a @ref md_topic_selectors "topic selector",
 evaluated at the server, which selects the topics to be fetched.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @since 6.3
 */
-(void)fetchTimeSeriesEventsWithTopicSelectorExpression:(NSString *)expression
                                      completionHandler:(void (^)(PTDiffusionTimeSeriesFetchResult * _Nullable result, NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
