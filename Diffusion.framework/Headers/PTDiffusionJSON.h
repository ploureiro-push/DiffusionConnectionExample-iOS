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
@class PTDiffusionJSONFetchResult;
@class PTDiffusionJSONTimeSeriesQueryResult;
@class PTDiffusionJSONUpdateStream;
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

@protocol PTDiffusionJSONRequestDelegate;
@protocol PTDiffusionJSONRequestStreamDelegate;
@protocol PTDiffusionJSONSessionResponseStreamDelegate;
@protocol PTDiffusionJSONValueStreamDelegate;
@protocol PTDiffusionJSONTimeSeriesEventValueStreamDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief An immutable JSON value with support for both binary and JSON deltas.
 
 JSON is "JavaScript Object Notation", a lightweight data-interchange format.
 See [www.json.org](http://www.json.org).
 
 Internally the value is stored and transmitted not as a JSON string, but in
 CBOR format to reduce memory and network overhead. CBOR (Concise Binary
 Object Representation) is a standardized format for binary representation of
 structured data defined by [RFC 7049](https://tools.ietf.org/html/rfc7049).
 See [www.cbor.io](http://www.cbor.io).

 Each JSON value is represented as a single CBOR data item. CBOR supports
 composite data types just like JSON, so this data item can be an array or a
 map of other data items. The `null` value is represented by the CBOR `Null`
 value.

 @since 5.9
 */
@interface PTDiffusionJSON : PTDiffusionBytes

/**
 Return a JSON object initialised with the given object.
 
 Object hierarchies passed to this method must be constructed from Foundation
 objects which can be logically encoded with CBOR. This provides flexibility
 above and beyond the basic capabilities of a 'pure JSON' encoding as well as
 being less restrictive than the capabilities of NSJSONSerialization.
 
 This means:
 - All objects are instances of `NSString`, `NSData`, `NSNumber`, `NSArray`,
   `NSDictionary` or `NSNull`.
 - Dictionary keys may be instances of any supported type.
 - The top level object may be of any supported type.
 
 Being more permissive than NSJSONSerialization in that:
 - `NSData` instances may be used.
 - Dictionary keys are not restricted to instances of `NSString`.
 - The top level object is not restricted to being a container (`NSArray` or
   `NSDictionary`).
 
 Applications may take advantage of the more permissive nature of the
 underlying CBOR encoding by using these capabilities, assuming:
 1. Encoding to JSON string is not required.
 2. Other client applications, perhaps developed in a different language and
    against a different library, can also support the capabilities.

 @param object The object to be serialized to CBOR and stored internally to
 represent the receiver.
 
 @param error If this method returns `nil` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @exception NSInvalidArgumentException Raised if the `object` argument is `nil`.

 @since 5.9
 */
-(nullable instancetype)initWithObject:(id)object
                                 error:(NSError **)error;

/**
 Convenience wrapper around initWithObject:error: that first uses
 NSJSONSerialization to generate the object to be serialized.
 
 @param jsonData A data object containing JSON data. See Apple's
 NSJSONSerialization documentation for detailed information regarding
 supported encodings.
 
 @param error If this method returns `nil` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @exception NSInvalidArgumentException Raised if the `jsonData` argument is `nil`.

 @since 5.9
 */
-(nullable instancetype)initWithJSONData:(NSData *)jsonData
                                   error:(NSError **)error;

/**
 Convenience wrapper around initWithJSONData:error: that first encodes the
 given string as UTF-8 (NSUTF8StringEncoding), requiring lossless conversion.

 @param jsonString A JSON string.

 @param error If this method returns `nil` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @exception NSInvalidArgumentException Raised if the `jsonString` argument is `nil`.

 @since 6.0
 */
-(nullable instancetype)initWithJSONString:(NSString *)jsonString
                                     error:(NSError **)error;

/**
 Compare the receiver's JSON value with another (e.g. an earlier version) to
 create a binary delta.
 
 @param json The original to which the delta should be able to be applied in
 order to generate the value represented by the receiver.
 
 @param error If an error occurs, upon return contains an `NSError` object
 that describes the problem.
 
 @return A delta representing the difference between json and the receiver,
 or `nil` if there was an error (e.g. either the original or the receiver
 don't represent a valid JSON value).

 @exception NSInvalidArgumentException Raised if the json argument is `nil`.

 @since 5.9
 */
-(nullable PTDiffusionBinaryDelta *)binaryDiffFromJSON:(PTDiffusionJSON *)json
                                                 error:(NSError **)error;

/**
 Apply a binary delta to the receiver's JSON value to create a new value.
 
 @param delta The delta describing the changes to be applied to the receiver's
 value in order to create the value to be returned.
 
 @param error If an error occurs, upon return contains an `NSError` object
 that describes the problem.
 
 @return The new JSON value, or `nil` if there was an error (e.g. the receiver
 does not represent a valid JSON value).
 
 @exception NSInvalidArgumentException Raised if the delta argument is `nil`.

 @since 5.9
 */
-(nullable PTDiffusionJSON *)applyDelta:(PTDiffusionBinaryDelta *)delta
                                  error:(NSError **)error;

/**
 Check whether the receiver is valid.

 @param error If not valid, upon return contains an `NSError` object that
 describes the problem.

 @return `YES` if this instance is valid.

 @since 5.9
 */
-(BOOL)validateWithError:(NSError **)error;

/**
 Creates a Foundation object from the receiver's JSON value.

 @param error If an error occurs, upon return contains an `NSError` object
 that describes the problem.

 @return An object, or `nil` if there was an error (e.g. the receiver doesn't
 represent a valid JSON value).

 @since 5.9
 */
-(nullable id)objectWithError:(NSError **)error;

/**
 Convenience wrapper around objectError: that then uses NSJSONSerialization to
 generate the JSON data.

 @param error If an error occurs, upon return contains an `NSError` object
 that describes the problem.

 @return A data object containing JSON, or `nil` if there was an error (e.g.
 the receive doesn't represent a valid JSON value or cannot be converted to
 pure JSON).
 
 @since 5.9
 */
-(nullable NSData*)JSONDataWithError:(NSError **)error;

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
 Creates a value stream capable of receiving JSON values.

 @param delegate The object which will handle the incoming stream. A weak
 reference is maintained to this object by the returned stream.

 @return An object reliant on the supplied delegate that can be added as a
 receiver of values using the Topics feature.

 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.

 @see PTDiffusionTopicsFeature

 @since 5.9
 */
+(PTDiffusionValueStream *)valueStreamWithDelegate:(id<PTDiffusionJSONValueStreamDelegate>)delegate;

/**
 Creates a value stream capable of receiving JSON time series events.

 @param delegate The object which will handle the incoming stream. A weak
 reference is maintained to this object by the returned stream.

 @return An object reliant on the supplied delegate that can be added as a
 receiver of values using the Topics feature.

 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.

 @see PTDiffusionTopicsFeature

 @since 6.0
 */
+(PTDiffusionValueStream *)timeSeriesEventValueStreamWithDelegate:(id<PTDiffusionJSONTimeSeriesEventValueStreamDelegate>)delegate;

/**
 Creates a request handler capable of receiving JSON requests for a handler
 registered at the server.
 
 @param delegate The object which will handle the incoming requests. A weak
 reference is maintained to this object by the returned handler.
 
 @return An object reliant on the supplied delegate that can be registered at
 the server using the Messaging Control feature.
 
 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.
 
 @see PTDiffusionMessagingControlFeature

 @since 6.0
 */
+(PTDiffusionRequestHandler *)requestHandlerWithDelegate:(id<PTDiffusionJSONRequestDelegate>)delegate;

/**
 Creates a request stream capable of receiving JSON requests.

 @param delegate The object which will handle the incoming requests. A weak
 reference is maintained to this object by the returned stream.

 @return An object reliant on the supplied delegate that can be set as the
 receiver of requests using the Messaging feature.

 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.

 @see PTDiffusionMessagingFeature

 @since 6.0
 */
+(PTDiffusionRequestStream *)requestStreamWithDelegate:(id<PTDiffusionJSONRequestStreamDelegate>)delegate;

/**
 Creates a response stream capable of receiving JSON responses from discrete
 sessions.

 @param delegate The object which will handle the incoming responses. A weak
 reference is maintained to this object by the returned stream.

 @return An object reliant on the supplied delegate that can be set as the
 receiver of requests using the Messaging Control feature.

 @exception NSInvalidArgumentException Raised if the delegate argument is `nil`.

 @see PTDiffusionMessagingControlFeature

 @since 6.1
 */
+(PTDiffusionSessionResponseStream *)sessionResponseStreamWithDelegate:(id<PTDiffusionJSONSessionResponseStreamDelegate>)delegate;

/**
 Compares the receiver to the given JSON.

 @param json The JSON object with which to compare the receiver.

 @return `YES` if the data in json is equal to the contents of the receiver, otherwise `NO`.

 @note Two JSON objects are equal if they are internally represented by the
 same CBOR encoding.

 @since 5.9
 */
-(BOOL)isEqualToJSON:(nullable PTDiffusionJSON *)json;

@end

/**
 @brief Extension adding support for responding to requests using JSON values.
 
 @since 6.0
 */
@interface PTDiffusionResponder (PTDiffusionJSON)

/**
 Dispatch a response to a request.
 
 @param json The value to send in response.

 @exception NSInvalidArgumentException Raised if the json argument is `nil`.

 @since 6.0
 */
-(void)respondWithJSON:(PTDiffusionJSON *)json;

@end

/**
 @brief Extension adding support to the Messaging feature for sending requests
 accepting a JSON response.

 @since 6.0
 */
@interface PTDiffusionMessagingFeature (PTDiffusionJSON)

/**
 Send a request for which a JSON response is expected.
 
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
-(void)       sendRequest:(PTDiffusionRequest *)request
                   toPath:(NSString *)path
    JSONCompletionHandler:(void (^)(PTDiffusionJSON * _Nullable json, NSError * _Nullable error))completionHandler;

@end

/**
 @brief Extension adding support to the Messaging Control feature for sending
 requests accepting a JSON response.

 @since 6.0
 */
@interface PTDiffusionMessagingControlFeature (PTDiffusionJSON)

/**
 Send a request to a session for which a JSON response is expected.

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
-(void)       sendRequest:(PTDiffusionRequest *)request
              toSessionId:(PTDiffusionSessionId *)sessionId
                     path:(NSString *)path
    JSONCompletionHandler:(void (^)(PTDiffusionJSON * _Nullable json, NSError * _Nullable error))completionHandler;

@end

/**
 @brief Extension adding support to the Time Series feature for appending and
 editing events using JSON values.
 
 @since 6.0
 */
@interface PTDiffusionTimeSeriesFeature (PTDiffusionJSON)

/**
 Update a time series topic by appending a new JSON value.
 
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
               JSONValue:(PTDiffusionJSON *)value
       completionHandler:(void (^)(PTDiffusionTimeSeriesEventMetadata * _Nullable eventMetadata, NSError * _Nullable error))completionHandler;

/**
 Update a time series topic by appending a new JSON value that overrides the
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
             JSONValue:(PTDiffusionJSON *)value
     completionHandler:(void (^)(PTDiffusionTimeSeriesEventMetadata * _Nullable eventMetadata, NSError * _Nullable error))completionHandler;

/**
 Evaluate a query for a time series topic where events have JSON values.

 @param query The configured query.
 
 @param topicPath The path of the time series topic to query.
 
 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil`. The completion handler will be called asynchronously on
 the main dispatch queue.

 @exception NSInvalidArgumentException Raised if any supplied arguments are `nil`.

 @since 6.0
 */
-(void)     evaluateQuery:(PTDiffusionTimeSeriesRangeQuery *)query
              atTopicPath:(NSString *)topicPath
    JSONCompletionHandler:(void (^)(PTDiffusionJSONTimeSeriesQueryResult * _Nullable result, NSError * _Nullable error))completionHandler;

@end

/**
 @brief Extension adding support to Topics feature fetch requests allowing them
 to be constrained to only those topics with a data type compatible with JSON.

 @since 6.2
 */
@interface PTDiffusionFetchRequest (PTDiffusionJSON)

/**
 Sends a fetch request to the server, specifying that values should be returned
 for selected topics, constraining the selection to only those topics with a
 data type compatible with JSON.

 The JSON data type constrains the topic types. So, any topic types specified
 in a previous call to #topicTypes: that cannot be read as JSON will be removed
 from the list of topic types.

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
-(void)fetchJSONValuesWithTopicSelectorExpression:(NSString *)expression
                                completionHandler:(void (^)(PTDiffusionJSONFetchResult * _Nullable result, NSError * _Nullable error))completionHandler;

@end

/**
 @brief Extension adding support to the Topic Update feature for updating topics
 with JSON values.

 @since 6.3
 */
@interface PTDiffusionTopicUpdateFeature (PTDiffusionJSON)

/**
 Sets a topic to a specified JSON value.

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
          toJSONValue:(PTDiffusionJSON *)value
    completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 Sets a topic to a specified JSON value if a constraint is satisfied.

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
          toJSONValue:(PTDiffusionJSON *)value
           constraint:(PTDiffusionUpdateConstraint *)constraint
    completionHandler:(void (^)(NSError * _Nullable error))completionHandler;

/**
 Ensures a topic exists and sets it to a JSON value.

 If a topic does not exist at the path, one will be created using the
 specification. If a topic does exist, its specification must match
 specification, otherwise the operation will fail.

 In other respects this method works in the same way as
 setWithPath:toJSONValue:completionHandler:.

 @param path The path of the topic.

 @param value The value.

 @param specification The required specification of the topic.

 @param completionHandler Block to be called asynchronously on success or
 failure. If the operation was successful, the `error` argument passed to the
 block will be `nil` and `result` will be non-`nil`. The completion handler will
 be called asynchronously on the main dispatch queue.

 @exception NSInvalidArgumentException If any argument is `nil` or if the topic
 type defined in the specification is incompatible with
 PTDiffusionDataTypes#json.

 @since 6.3
 */
-(void)   addWithPath:(NSString *)path
        specification:(PTDiffusionTopicSpecification *)specification
    andSetToJSONValue:(PTDiffusionJSON *)value
    completionHandler:(void (^)(PTDiffusionTopicCreationResult * _Nullable result, NSError * _Nullable error))completionHandler;

/**
 Ensures a topic exists and sets it to a JSON value if a constraint is
 satisfied.

 If a topic does not exist at the path, one will be created using the
 specification. If a topic does exist, its specification must match
 specification, otherwise the operation will fail.

 In other respects this method works in the same way as
 setWithPath:toJSONValue:constraint:completionHandler:.

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
 PTDiffusionDataTypes#json.

 @since 6.3
 */
-(void)   addWithPath:(NSString *)path
        specification:(PTDiffusionTopicSpecification *)specification
    andSetToJSONValue:(PTDiffusionJSON *)value
           constraint:(PTDiffusionUpdateConstraint *)constraint
    completionHandler:(void (^)(PTDiffusionTopicCreationResult * _Nullable result, NSError * _Nullable error))completionHandler;

/**
 Creates an update stream to use for updating a specific topic with JSON values.

 Update streams send a sequence of updates for a specific topic. The updates may
 be delivered to the server as binary deltas. They do not provide exclusive
 access to the topic. If exclusive access is required update streams should be
 used with session locks as constraints.

 Streams are validated lazily when the first 'set' or 'validate' operation is
 completed. Once validated a stream can be invalidated, after which it rejects
 future updates.

 @param path The path of the topic.

 @return An update stream.

 @exception NSInvalidArgumentException If path is `nil`.

 @since 6.3
 */
-(PTDiffusionJSONUpdateStream *)jsonUpdateStreamWithPath:(NSString *)path;

/**
 Creates an update stream to use for updating a specific topic with JSON values
 if a constraint is satisfied.

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

 @exception NSInvalidArgumentException If either argument is `nil`.

 @since 6.3
 */
-(PTDiffusionJSONUpdateStream *)jsonUpdateStreamWithPath:(NSString *)path
                                              constraint:(PTDiffusionUpdateConstraint *)constraint;

/**
 Creates an update stream to use for creating and updating a specific topic with
 JSON values.

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
 PTDiffusionDataTypes#json.

 @since 6.3
 */
-(PTDiffusionJSONUpdateStream *)jsonUpdateStreamWithPath:(NSString *)path
                                           specification:(PTDiffusionTopicSpecification *)specification;

/**
 Creates an update stream to use for creating and updating a specific topic with
 JSON values if a constraint is satisfied.

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
 PTDiffusionDataTypes#json.

 @since 6.3
 */
-(PTDiffusionJSONUpdateStream *)jsonUpdateStreamWithPath:(NSString *)path
                                           specification:(PTDiffusionTopicSpecification *)specification
                                              constraint:(PTDiffusionUpdateConstraint *)constraint;

@end

NS_ASSUME_NONNULL_END
