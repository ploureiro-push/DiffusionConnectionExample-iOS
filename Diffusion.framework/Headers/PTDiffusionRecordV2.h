//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2017, 2019 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionBytes.h>
#import <Diffusion/PTDiffusionFetchRequest.h>
#import <Diffusion/PTDiffusionMessagingFeature.h>
#import <Diffusion/PTDiffusionMessagingControlFeature.h>
#import <Diffusion/PTDiffusionResponder.h>
#import <Diffusion/PTDiffusionTimeSeriesFeature.h>
#import <Diffusion/PTDiffusionTopicUpdateFeature.h>

@class PTDiffusionRecordV2Delta;
@class PTDiffusionRecordV2FetchResult;
@class PTDiffusionRecordV2Model;
@class PTDiffusionRecordV2Schema;
@class PTDiffusionRecordV2TimeSeriesQueryResult;
@class PTDiffusionRecordV2UpdateStream;
@class PTDiffusionRequest;
@class PTDiffusionRequestHandler;
@class PTDiffusionRequestStream;
@class PTDiffusionResponse;
@class PTDiffusionSessionResponseStream;
@class PTDiffusionTimeSeriesEventMetadata;
@class PTDiffusionTimeSeriesRangeQuery;
@class PTDiffusionTopicCreationResult;
@class PTDiffusionTopicSpecification;
@class PTDiffusionUpdateConstraint;
@class PTDiffusionValueStream;

@protocol PTDiffusionRecordV2RequestDelegate;
@protocol PTDiffusionRecordV2RequestStreamDelegate;
@protocol PTDiffusionRecordV2SessionResponseStreamDelegate;
@protocol PTDiffusionRecordV2TimeSeriesEventValueStreamDelegate;
@protocol PTDiffusionRecordV2ValueStreamDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief An immutable record value with support for binary deltas.
 
 @since 6.0
 */
@interface PTDiffusionRecordV2 : PTDiffusionBytes

/**
 Parses the value into a model based upon a specified schema.

 This assumes that data is compatible with the schema and does not do any
 validation. There is no need to validate the data if this has been done on
 entry or at the server. However, if the data is invalid then issues may occur
 when attempting to access it.

 If it is not certain that the data is valid then the
 #validatedModelWithSchema:error: method should be used instead.

 @param schema The schema to use for parsing the data.

 @param error If this method returns `nil` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return An immutable model derived from the data value; or `nil` if an error
 occurred, in which case `*error` will be populated with the failure reason.
 Reasons for failure include:
 - the data value does not contain correctly encoded record data.

 @since 6.0
 */
-(nullable PTDiffusionRecordV2Model *)modelWithSchema:(PTDiffusionRecordV2Schema *)schema
                                                error:(NSError **)error;

/**
 Parses the value into a model based upon a specified schema.

 @param schema The schema to use for parsing the data.

 @param error If this method returns `nil` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return An immutable model derived from the data value; or `nil` if an error
 occurred, in which case `*error` will be populated with the failure reason.
 Reasons for failure include:
 - the data value does not contain correctly encoded record data.
 - the data value is incompatible with the supplied schema.
 */
-(nullable PTDiffusionRecordV2Model *)validatedModelWithSchema:(PTDiffusionRecordV2Schema *)schema
                                                         error:(NSError **)error;

/**
 Returns the data value as an array of arrays of strings.

 @param error If this method returns `nil` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return An immutable array of records derived from the data value; or `nil` if
 an error occurred, in which case `*error` will be populated with the failure
 reason.

 @since 6.0
 */
-(nullable NSArray<NSArray<NSString *> *> *)recordsWithError:(NSError **)error;

/**
 Returns the data value as an array of fields.

 This disregards record boundaries. If there is more than one record, they are
 concatenated to produce a list of all of the fields.

 @param error If this method returns `nil` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return An immutable array of fields derived from the data value; or `nil` if
 an error occurred, in which case `*error` will be populated with the failure
 reason.

 @note This method would normally only be used when it is known that there is
 only one record.

 @since 6.0
 */
-(nullable NSArray<NSString *> *)fieldsWithError:(NSError **)error;

/**
 Compare this value with an earlier version to calculate a structural delta.
 
 @param originalRecord The original value to compare with this value.

 @since 6.0.2
 */
-(PTDiffusionRecordV2Delta *)diffFromOriginalRecord:(PTDiffusionRecordV2 *)originalRecord;

/**
 A request that can be used to send this value using messaging.

 @since 6.0.1
 */
@property(nonatomic, readonly) PTDiffusionRequest* request;

/**
 A response that can be used to send this value using messaging.

 @since 6.1
 */
@property(nonatomic, readonly) PTDiffusionResponse* response;

/**
 An update constraint requiring the current value of a topic to match this
 value.

 Use PTDiffusionUpdateConstraint#noValue to check if the topic has no value.

 This constraint is useful when changing the value of a topic. It is unsatisfied
 if no topic is present at the path, making it unsuitable for operations that
 try to add topics.

 @since 6.3
 */
@property(nonatomic, readonly) PTDiffusionUpdateConstraint * updateConstraint;

/**
 Creates a value stream capable of receiving record values.

 @param delegate The object which will handle the incoming stream. A weak
 reference is maintained to this object by the returned stream.

 @return An object reliant on the supplied delegate that can be added as a
 receiver of values using the Topics feature.

 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.

 @see PTDiffusionTopicsFeature

 @since 6.0
 */
+(PTDiffusionValueStream *)valueStreamWithDelegate:(id<PTDiffusionRecordV2ValueStreamDelegate>)delegate;

/**
 Creates a value stream capable of receiving record time series events.

 @param delegate The object which will handle the incoming stream. A weak
 reference is maintained to this object by the returned stream.

 @return An object reliant on the supplied delegate that can be added as a
 receiver of values using the Topics feature.

 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.

 @see PTDiffusionTopicsFeature

 @since 6.0
 */
+(PTDiffusionValueStream *)timeSeriesEventValueStreamWithDelegate:(id<PTDiffusionRecordV2TimeSeriesEventValueStreamDelegate>)delegate;

/**
 Creates a request handler capable of receiving record requests for a handler
 registered at the server.
 
 @param delegate The object which will handle the incoming requests. A weak
 reference is maintained to this object by the returned handler.
 
 @return An object reliant on the supplied delegate that can be registered at
 the server using the Messaging Control feature.
 
 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.
 
 @see PTDiffusionMessagingControlFeature

 @since 6.0
 */
+(PTDiffusionRequestHandler *)requestHandlerWithDelegate:(id<PTDiffusionRecordV2RequestDelegate>)delegate;

/**
 Creates a request stream capable of receiving record requests.

 @param delegate The object which will handle the incoming requests. A weak
 reference is maintained to this object by the returned stream.

 @return An object reliant on the supplied delegate that can be set as the
 receiver of requests using the Messaging feature.

 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.

 @see PTDiffusionMessagingFeature

 @since 6.0
 */
+(PTDiffusionRequestStream *)requestStreamWithDelegate:(id<PTDiffusionRecordV2RequestStreamDelegate>)delegate;

/**
 Creates a response stream capable of receiving record responses from discrete
 sessions.

 @param delegate The object which will handle the incoming responses. A weak
 reference is maintained to this object by the returned stream.

 @return An object reliant on the supplied delegate that can be set as the
 receiver of requests using the Messaging Control feature.

 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.

 @see PTDiffusionMessagingControlFeature

 @since 6.1
 */
+(PTDiffusionSessionResponseStream *)sessionResponseStreamWithDelegate:(id<PTDiffusionRecordV2SessionResponseStreamDelegate>)delegate;

/**
 Compares the receiver to the given record.

 @param record The record object with which to compare the receiver.

 @return `YES` if the data in record is equal to the contents of the receiver,
 otherwise `NO`.

 @note Two record objects are equal if they hold the same number of data bytes,
 and if the bytes at the same position in the objects are the same.

 @since 6.3
 */
-(BOOL)isEqualToRecord:(nullable PTDiffusionRecordV2 *)record;

@end

/**
 @brief Extension adding support for responding to requests using record values.
 
 @since 6.0
 */
@interface PTDiffusionResponder (PTDiffusionRecordV2)

/**
 Dispatch a response to a request.
 
 @param record The value to send in response.

 @exception NSInvalidArgumentException Raised if the record argument is `nil`.

 @since 6.0
 */
-(void)respondWithRecord:(PTDiffusionRecordV2 *)record;

@end

/**
 @brief Extension adding support to the Messaging feature for sending requests
 accepting a record response.

 @since 6.0
 */
@interface PTDiffusionMessagingFeature (PTDiffusionRecordV2)

/**
 Send a request for which a record response is expected.
 
 The message will be routed to an appropriately registered control handler for
 the given path.

 @param request The request to send.
 
 @param path The path to send the request to.
 
 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @since 6.0
 */
-(void)         sendRequest:(PTDiffusionRequest *)request
                     toPath:(NSString *)path
    recordCompletionHandler:(void (^)(PTDiffusionRecordV2 * _Nullable record, NSError * _Nullable error))completionHandler;

@end

/**
 @brief Extension adding support to the Messaging Control feature for sending
 requests accepting a record response.

 @since 6.0
 */
@interface PTDiffusionMessagingControlFeature (PTDiffusionRecordV2)

/**
 Send a request to a session for which a record response is expected.

 @param request The request to send.
 
 @param sessionId The session to send the request to.

 @param path The path to send the request to.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @since 6.0
 */
-(void)         sendRequest:(PTDiffusionRequest *)request
                toSessionId:(PTDiffusionSessionId *)sessionId
                       path:(NSString *)path
    recordCompletionHandler:(void (^)(PTDiffusionRecordV2 * _Nullable record, NSError * _Nullable error))completionHandler;

@end

/**
 @brief Extension adding support to the Time Series feature for appending and
 editing events using record values.
 
 @since 6.0
 */
@interface PTDiffusionTimeSeriesFeature (PTDiffusionRecordV2)

/**
 Update a time series topic by appending a new record value.
 
 The server will add an event to the end of the time series based on the
 supplied value, with a new sequence number, timestamp, and the author set to
 the authenticated principal of the session.
 
 @param topicPath The path of the time series topic to update.
 
 @param value The event value.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @since 6.0
 */
-(void)appendToTopicPath:(NSString *)topicPath
             recordValue:(PTDiffusionRecordV2 *)value
       completionHandler:(void (^)(PTDiffusionTimeSeriesEventMetadata * _Nullable eventMetadata, NSError * _Nullable error))completionHandler;

/**
 Update a time series topic by appending a new record value that overrides the
 value of an existing event.

 The existing event is identified by its sequence number and must be an original
 event.
 
 The server will add an edit event to the end of the time series based on the
 supplied value, with a new sequence number, timestamp, and the author set to
 the authenticated principal of the session.

 @param topicPath The path of the time series topic to update.
 
 @param originalSequence The sequence number of the original event to edit.

 @param value The event value.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any of the topicPath, value or
 completionHandler arguments are `nil`. Also raised if the originalSequence
 argument exceeds `INT64_MAX`.

 @since 6.0
 */
-(void)editAtTopicPath:(NSString *)topicPath
      originalSequence:(UInt64)originalSequence
           recordValue:(PTDiffusionRecordV2 *)value
     completionHandler:(void (^)(PTDiffusionTimeSeriesEventMetadata * _Nullable eventMetadata, NSError * _Nullable error))completionHandler;

/**
 Evaluate a query for a time series topic where events have record values.

 @param query The configured query.
 
 @param topicPath The path of the time series topic to query.
 
 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @since 6.0
 */
-(void)       evaluateQuery:(PTDiffusionTimeSeriesRangeQuery *)query
                atTopicPath:(NSString *)topicPath
    recordCompletionHandler:(void (^)(PTDiffusionRecordV2TimeSeriesQueryResult * _Nullable result, NSError * _Nullable error))completionHandler;

@end

/**
 @brief Extension adding support to Topics feature fetch requests allowing them
 to be constrained to only those topics with a data type compatible with
 records.

 @since 6.2
 */
@interface PTDiffusionFetchRequest (PTDiffusionRecordV2)

/**
 Sends a fetch request to the server, specifying that values should be returned
 for selected topics, constraining the selection to only those topics with a
 data type compatible with records.

 The record data type constrains the topic types. So, any topic types specified
 in a previous call to #topicTypes: that cannot be read as records will be
 removed from the list of topic types.

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

 @since 6.2
 */
-(void)fetchRecordValuesWithTopicSelectorExpression:(NSString *)expression
                                  completionHandler:(void (^)(PTDiffusionRecordV2FetchResult * _Nullable result, NSError * _Nullable error))completionHandler;

@end

/**
 @brief Extension adding support to the Topic Update feature for updating topics
 with record values.

 @since 6.3
 */
@interface PTDiffusionTopicUpdateFeature (PTDiffusionRecordV2)

/**
 Sets a topic to a specified record value.

 @param path The path of the topic.

 @param value The value.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException If any argument is `nil`.

 @since 6.3
 */
-(void)   setWithPath:(NSString *)path
        toRecordValue:(PTDiffusionRecordV2 *)value
    completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 Sets a topic to a specified record value if a constraint is satisfied.

 @param path The path of the topic.

 @param value The value.

 @param constraint The constraint that must be satisfied for the topic to be
 updated.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException If any argument is `nil`.

 @since 6.3
 */
-(void)   setWithPath:(NSString *)path
        toRecordValue:(PTDiffusionRecordV2 *)value
           constraint:(PTDiffusionUpdateConstraint *)constraint
    completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 Ensures a topic exists and sets it to a record value.

 If a topic does not exist at the path, one will be created using the
 specification. If a topic does exist, its specification must match
 specification, otherwise the operation will fail.

 In other respects this method works in the same way as
 setWithPath:toRecordValue:completionHandler:.

 @param path The path of the topic.

 @param value The value.

 @param specification The required specification of the topic.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil` and `result` will be non-`nil`. The completion handler will
 be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException If any argument is `nil` or if the topic
 type defined in the specification is incompatible with
 PTDiffusionDataTypes#recordV2.

 @since 6.3
 */
-(void)     addWithPath:(NSString *)path
          specification:(PTDiffusionTopicSpecification *)specification
    andSetToRecordValue:(PTDiffusionRecordV2 *)value
      completionHandler:(void (^)(PTDiffusionTopicCreationResult * _Nullable result, NSError * _Nullable error))completionHandler;

/**
 Ensures a topic exists and sets it to a record value if a constraint is
 satisfied.

 If a topic does not exist at the path, one will be created using the
 specification. If a topic does exist, its specification must match
 specification, otherwise the operation will fail.

 In other respects this method works in the same way as
 setWithPath:toRecordValue:constraint:completionHandler:.

 @param path The path of the topic.

 @param specification The required specification of the topic.

 @param value The value.

 @param constraint The constraint that must be satisfied for the topic to be
 updated.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil` and `result` will be non-`nil`. The completion handler will
 be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException If any argument is `nil` or if the topic
 type defined in the specification is incompatible with
 PTDiffusionDataTypes#recordV2.

 @since 6.3
 */
-(void)     addWithPath:(NSString *)path
          specification:(PTDiffusionTopicSpecification *)specification
    andSetToRecordValue:(PTDiffusionRecordV2 *)value
             constraint:(PTDiffusionUpdateConstraint *)constraint
      completionHandler:(void (^)(PTDiffusionTopicCreationResult * _Nullable result, NSError * _Nullable error))completionHandler;

/**
 Creates an update stream to use for updating a specific topic with record
 values.

 Update streams send a sequence of updates for a specific topic. The updates may
 be delivered to the server as binary deltas. They do not provide exclusive
 access to the topic. If exclusive access is required update streams should be
 used with session locks as constraints.

 Streams are validated lazily when the first 'set' or 'validate' operation is
 completed. Once validated a stream can be invalidated, after which it rejects
 future updates.

 @param path The path of the topic.

 @return An update stream.

 @exception NSInvalidArgumentException If any argument is `nil`.

 @since 6.3
 */
-(PTDiffusionRecordV2UpdateStream *)recordUpdateStreamWithPath:(NSString *)path;

/**
 Creates an update stream to use for updating a specific topic with record
 values if a constraint is satisfied.

 Update streams send a sequence of updates for a specific topic. The updates may
 be delivered to the server as binary deltas. They do not provide exclusive
 access to the topic. If exclusive access is required update streams should be
 used with session locks as constraints.

 Streams are validated lazily when the first 'set' or 'validate' operation is
 completed. Once validated a stream can be invalidated, after which it rejects
 future updates.

 @param path The path of the topic.

 @param constraint The constraint that must be satisfied for the update stream
 to be validated.

 @return An update stream.

 @exception NSInvalidArgumentException If any argument is `nil`.

 @since 6.3
 */
-(PTDiffusionRecordV2UpdateStream *)recordUpdateStreamWithPath:(NSString *)path
                                                    constraint:(PTDiffusionUpdateConstraint *)constraint;

/**
 Creates an update stream to use for creating and updating a specific topic with
 record values.

 Update streams send a sequence of updates for a specific topic. The updates may
 be delivered to the server as binary deltas. They do not provide exclusive
 access to the topic. If exclusive access is required update streams should be
 used with session locks as constraints.

 Streams are validated lazily when the first 'set' or 'validate' operation is
 completed. Once validated a stream can be invalidated, after which it rejects
 future updates.

 @param path The path of the topic.

 @param specification The required specification of the topic.

 @return An update stream.

 @exception NSInvalidArgumentException If any argument is `nil` or if the topic
 type defined in the specification is incompatible with
 PTDiffusionDataTypes#recordV2.

 @since 6.3
 */
-(PTDiffusionRecordV2UpdateStream *)recordUpdateStreamWithPath:(NSString *)path
                                                 specification:(PTDiffusionTopicSpecification *)specification;

/**
 Creates an update stream to use for creating and updating a specific topic with
 record values if a constraint is satisfied.

 Update streams send a sequence of updates for a specific topic. The updates may
 be delivered to the server as binary deltas. They do not provide exclusive
 access to the topic. If exclusive access is required update streams should be
 used with session locks as constraints.

 Streams are validated lazily when the first 'set' or 'validate' operation is
 completed. Once validated a stream can be invalidated, after which it rejects
 future updates.

 @param path The path of the topic.

 @param specification The required specification of the topic.

 @param constraint The constraint that must be satisfied for the update stream
 to be validated.

 @return An update stream.

 @exception NSInvalidArgumentException If any argument is `nil` or if the topic
 type defined in the specification is incompatible with
 PTDiffusionDataTypes#recordV2.

 @since 6.3
 */
-(PTDiffusionRecordV2UpdateStream *)recordUpdateStreamWithPath:(NSString *)path
                                                 specification:(PTDiffusionTopicSpecification *)specification
                                                    constraint:(PTDiffusionUpdateConstraint *)constraint;

@end

NS_ASSUME_NONNULL_END
