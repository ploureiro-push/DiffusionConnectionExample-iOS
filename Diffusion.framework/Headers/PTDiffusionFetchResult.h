//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2018 Push Technology Ltd., All Rights Reserved.
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

@class PTDiffusionFetchTopicResult;

/**
 @brief Base class for results from fetch operations issued to the server.

 A fetch operation is issued using a PTDiffusionFetchRequest.

 @since 6.2
 */
@interface PTDiffusionFetchResult : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 The results from the fetch operation, in path order, each representing a single
 topic selected by the fetch operation.

 @since 6.2
 */
@property(nonatomic, readonly) NSArray<PTDiffusionFetchTopicResult *> * results;

/**
 Indicates whether the fetch could have returned more results if it had not been
 constrained by the PTDiffusionFetchRequest#first: ,
 PTDiffusionFetchRequest#last: or
 PTDiffusionFetchRequest#maximumResultSize: limits.

 `YES` if more results could have been returned, otherwise `NO`.

 @since 6.2
 */
@property(nonatomic, readonly, getter=hasMore) BOOL more;

@end

NS_ASSUME_NONNULL_END
