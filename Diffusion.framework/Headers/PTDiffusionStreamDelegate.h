//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2015, 2017 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;

@class PTDiffusionStream;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The stream delegate protocol defines the methods to be implemented by
 classes wishing to receive streaming updates.

 @see PTDiffusionTopicsFeature
 @see PTDiffusionMessagingFeature

 @since 5.6
 */
@protocol PTDiffusionStreamDelegate

/**
 The stream closed prematurely.

 @param stream The stream that closed.

 @param error The reason why the stream closed.

 @note No further messages will be sent to the delegate for this stream.

 @since 5.6
 */
-(void)diffusionStream:(PTDiffusionStream *)stream
      didFailWithError:(NSError *)error;

/**
 The stream closed normally.

 @param stream The stream that closed.

 @note No further messages will be sent to the delegate for this stream.

 @since 5.6
 */
-(void)diffusionDidCloseStream:(PTDiffusionStream *)stream;

@end

NS_ASSUME_NONNULL_END
