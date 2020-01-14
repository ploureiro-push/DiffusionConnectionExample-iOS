//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2016, 2019 Push Technology Ltd., All Rights Reserved.
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

@class PTDiffusionBinaryDelta;
@class PTDiffusionBinaryFetchResult;
@class PTDiffusionBinaryTimeSeriesQueryResult;
@class PTDiffusionBinaryUpdateStream;
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

@protocol PTDiffusionBinaryRequestDelegate;
@protocol PTDiffusionBinaryRequestStreamDelegate;
@protocol PTDiffusionBinarySessionResponseStreamDelegate;
@protocol PTDiffusionBinaryTimeSeriesEventValueStreamDelegate;
@protocol PTDiffusionBinaryValueStreamDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief An immutable binary value with support for binary deltas.

 @since 5.9
 */
@interface PTDiffusionBinary : PTDiffusionBytes

/**
 Apply a binary delta to the receiver's binary value to create a new value.

 @param delta The delta describing the changes to be applied to the receiver's
 value in order to create the value to be returned.

 @param error Location to store a reason if this method returns `nil` to
 indicate failure.

 @return The new binary value or `nil` if there was a failure when applying the
 delta (e.g. either the delta is invalid).

 @exception NSInvalidArgumentException Raised if the delta argument is `nil`.

 @since 5.9
 */
-(nullable PTDiffusionBinary *)applyDelta:(PTDiffusionBinaryDelta *)delta
                                    error:(NSError **)error;

/**
 Compare the receiver's binary value with another (e.g. an earlier version) to
 create a binary delta.

 @param binary The original to which the delta should be able to be applied in
 order to generate the value represented by the receiver.

 @return A binary delta representing the difference between binary and the
 receiver.

 @exception NSInvalidArgumentException Raised if the binary argument is `nil`.

 @since 5.9
 */
-(PTDiffusionBinaryDelta *)diffFromBinary:(PTDiffusionBinary *)binary;

/**
 A request that can be used to send this value using messaging.

 @since 6.0
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
 Creates a value stream capable of receiving binary values.

 @param delegate The object which will handle the incoming stream. A weak
 reference is maintained to this object by the returned stream.

 @return An object reliant on the supplied delegate that can be added as a
 receiver of values using the Topics feature.

 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.

 @see PTDiffusionTopicsFeature

 @since 5.9
 */
+(PTDiffusionValueStream *)valueStreamWithDelegate:(id<PTDiffusionBinaryValueStreamDelegate>)delegate;

/**
 Creates a value stream capable of receiving binary time series events.

 @param delegate The object which will handle the incoming stream. A weak
 reference is maintained to this object by the returned stream.

 @return An object reliant on the supplied delegate that can be added as a
 receiver of values using the Topics feature.

 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.

 @see PTDiffusionTopicsFeature

 @since 6.0
 */
+(PTDiffusionValueStream *)timeSeriesEventValueStreamWithDelegate:(id<PTDiffusionBinaryTimeSeriesEventValueStreamDelegate>)delegate;

/**
 Creates a request handler capable of receiving Binary requests for a handler
 registered at the server.
 
 @param delegate The object which will handle the incoming requests. A weak
 reference is maintained to this object by the returned handler.
 
 @return An object reliant on the supplied delegate that can be registered at
 the server using the Messaging Control feature.
 
 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.
 
 @see PTDiffusionMessagingControlFeature

 @since 6.0
 */
+(PTDiffusionRequestHandler *)requestHandlerWithDelegate:(id<PTDiffusionBinaryRequestDelegate>)delegate;

/**
 Creates a request stream capable of receiving Binary requests.

 @param delegate The object which will handle the incoming requests. A weak
 reference is maintained to this object by the returned stream.

 @return An object reliant on the supplied delegate that can be set as the
 receiver of requests using the Messaging feature.

 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.

 @see PTDiffusionMessagingFeature

 @since 6.0
 */
+(PTDiffusionRequestStream *)requestStreamWithDelegate:(id<PTDiffusionBinaryRequestStreamDelegate>)delegate;

/**
 Creates a response stream capable of receiving Binary responses from discrete
 sessions.

 @param delegate The object which will handle the incoming responses. A weak
 reference is maintained to this object by the returned stream.

 @return An object reliant on the supplied delegate that can be set as the
 receiver of requests using the Messaging Control feature.

 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.

 @see PTDiffusionMessagingControlFeature

 @since 6.1
 */
+(PTDiffusionSessionResponseStream *)sessionResponseStreamWithDelegate:(id<PTDiffusionBinarySessionResponseStreamDelegate>)delegate;

/**
 Compares the receiver to the given binary.

 @param binary The binary object with which to compare the receiver.

 @return `YES` if the data in binary is equal to the contents of the receiver, otherwise `NO`.

 @note Two binary objects are equal if they hold the same number of data bytes, and if the
 bytes at the same position in the objects are the same.

 @since 5.9
 */
-(BOOL)isEqualToBinary:(nullable PTDiffusionBinary *)binary;

@end

/**
 @brief Extension adding support for responding to requests using Binary values.
 
 @since 6.0
 */
@interface PTDiffusionResponder (PTDiffusionBinary)

/**
 Dispatch a response to a request.
 
 @param binary The value to send in response.

 @exception NSInvalidArgumentException Raised if the binary argument is `nil`.

 @since 6.0
 */
-(void)respondWithBinary:(PTDiffusionBinary *)binary;

@end

/**
 @brief Extension adding support to the Messaging feature for sending requests
 accepting a binary response.

 @since 6.0
 */
@interface PTDiffusionMessagingFeature (PTDiffusionBinary)

/**
 Send a request for which a binary response is expected.
 
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
    binaryCompletionHandler:(void (^)(PTDiffusionBinary * _Nullable binary, NSError * _Nullable error))completionHandler;

@end

/**
 @brief Extension adding support to the Messaging Control feature for sending
 requests accepting a binary response.

 @since 6.0
 */
@interface PTDiffusionMessagingControlFeature (PTDiffusionBinary)

/**
 Send a request to a session for which a binary response is expected.

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
    binaryCompletionHandler:(void (^)(PTDiffusionBinary * _Nullable binary, NSError * _Nullable error))completionHandler;

@end

/**
 @brief Extension adding support to the Time Series feature for appending and
 editing events using binary values.
 
 @since 6.0
 */
@interface PTDiffusionTimeSeriesFeature (PTDiffusionBinary)

/**
 Update a time series topic by appending a new binary value.
 
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
             binaryValue:(PTDiffusionBinary *)value
       completionHandler:(void (^)(PTDiffusionTimeSeriesEventMetadata * _Nullable eventMetadata, NSError * _Nullable error))completionHandler;

/**
 Update a time series topic by appending a new binary value that overrides the
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
           binaryValue:(PTDiffusionBinary *)value
     completionHandler:(void (^)(PTDiffusionTimeSeriesEventMetadata * _Nullable eventMetadata, NSError * _Nullable error))completionHandler;

/**
 Evaluate a query for a time series topic where events have binary values.
 
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
    binaryCompletionHandler:(void (^)(PTDiffusionBinaryTimeSeriesQueryResult * _Nullable result, NSError * _Nullable error))completionHandler;

@end

/**
 @brief Extension adding support to Topics feature fetch requests allowing them
 to be constrained to only those topics with a data type compatible with Binary.

 @since 6.2
 */
@interface PTDiffusionFetchRequest (PTDiffusionBinary)

/**
 Sends a fetch request to the server, specifying that values should be returned
 for selected topics, constraining the selection to only those topics with a
 data type compatible with Binary.

 The Binary data type constrains the topic types. So, any topic types specified
 in a previous call to #topicTypes: that cannot be read as Binary will be
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
-(void)fetchBinaryValuesWithTopicSelectorExpression:(NSString *)expression
                                  completionHandler:(void (^)(PTDiffusionBinaryFetchResult * _Nullable result, NSError * _Nullable error))completionHandler;

@end

/**
 @brief Extension adding support to the Topic Update feature for updating topics
 with binary values.

 @since 6.3
 */
@interface PTDiffusionTopicUpdateFeature (PTDiffusionBinary)

/**
 Sets a topic to a specified binary value.

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
        toBinaryValue:(PTDiffusionBinary *)value
    completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 Sets a topic to a specified binary value if a constraint is satisfied.

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
        toBinaryValue:(PTDiffusionBinary *)value
           constraint:(PTDiffusionUpdateConstraint *)constraint
    completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 Ensures a topic exists and sets it to a binary value.

 If a topic does not exist at the path, one will be created using the
 specification. If a topic does exist, its specification must match
 specification, otherwise the operation will fail.

 In other respects this method works in the same way as
 setWithPath:toBinaryValue:completionHandler:.

 @param path The path of the topic.

 @param value The value.

 @param specification The required specification of the topic.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil` and `result` will be non-`nil`. The completion handler will
 be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException If any argument is `nil` or if the topic
 type defined in the specification is incompatible with
 PTDiffusionDataTypes#binary.

 @since 6.3
 */
-(void)     addWithPath:(NSString *)path
          specification:(PTDiffusionTopicSpecification *)specification
    andSetToBinaryValue:(PTDiffusionBinary *)value
      completionHandler:(void (^)(PTDiffusionTopicCreationResult * _Nullable result, NSError * _Nullable error))completionHandler;

/**
 Ensures a topic exists and sets it to a binary value if a constraint is
 satisfied.

 If a topic does not exist at the path, one will be created using the
 specification. If a topic does exist, its specification must match
 specification, otherwise the operation will fail.

 In other respects this method works in the same way as
 setTopicWithPath:toBinaryValue:constraint:completionHandler:.

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
 PTDiffusionDataTypes#binary.

 @since 6.3
 */
-(void)     addWithPath:(NSString *)path
          specification:(PTDiffusionTopicSpecification *)specification
    andSetToBinaryValue:(PTDiffusionBinary *)value
             constraint:(PTDiffusionUpdateConstraint *)constraint
      completionHandler:(void (^)(PTDiffusionTopicCreationResult * _Nullable result, NSError * _Nullable error))completionHandler;

/**
 Creates an update stream to use for updating a specific topic with binary
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
-(PTDiffusionBinaryUpdateStream *)binaryUpdateStreamWithPath:(NSString *)path;

/**
 Creates an update stream to use for updating a specific topic with binary
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
-(PTDiffusionBinaryUpdateStream *)binaryUpdateStreamWithPath:(NSString *)path
                                                  constraint:(PTDiffusionUpdateConstraint *)constraint;

/**
 Creates an update stream to use for creating and updating a specific topic with
 binary values.

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
 PTDiffusionDataTypes#binary.

 @since 6.3
 */
-(PTDiffusionBinaryUpdateStream *)binaryUpdateStreamWithPath:(NSString *)path
                                               specification:(PTDiffusionTopicSpecification *)specification;

/**
 Creates an update stream to use for creating and updating a specific topic with
 binary values if a constraint is satisfied.

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
 PTDiffusionDataTypes#binary.

 @since 6.3
 */
-(PTDiffusionBinaryUpdateStream *)binaryUpdateStreamWithPath:(NSString *)path
                                               specification:(PTDiffusionTopicSpecification *)specification
                                                  constraint:(PTDiffusionUpdateConstraint *)constraint;

@end

NS_ASSUME_NONNULL_END
