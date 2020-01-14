//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2016 Push Technology Ltd., All Rights Reserved.
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
 @brief Details returned in response to a ping to the server.
 
 A ping details object is immutable.
 
 @see PTDiffusionPingsFeature

 @since 5.7
 */
@interface PTDiffusionPingDetails : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 The round trip time from when the ping was sent to the time
 the response was received.

 @since 5.7
 */
@property(nonatomic, readonly) NSTimeInterval roundTripTime;

/**
 The time the ping was sent.

 @since 5.7
 */
@property(nonatomic, readonly) NSDate* timestamp;

/**
 Compares the receiver to the given content.

 @param pingDetails The ping details object with which to compare the receiver.

 @return `YES` if the ping details is equal to the contents of the receiver, otherwise `NO`.

 @since 5.7
 */
-(BOOL)isEqualToPingDetails:(nullable PTDiffusionPingDetails *)pingDetails;

@end

NS_ASSUME_NONNULL_END
