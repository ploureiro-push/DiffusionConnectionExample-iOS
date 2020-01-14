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
#import <Diffusion/PTDiffusionStreamDelegate.h>

@class PTDiffusionRecordV2;
@class PTDiffusionResponder;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Methods implemented by classes handling record messaging requests.

 @see PTDiffusionRecordV2
 @see PTDiffusionMessagingFeature

 @since 6.0
 */
@protocol PTDiffusionRecordV2RequestStreamDelegate <PTDiffusionStreamDelegate>

/**
 Called when a record request has been received.
 
 @param stream The stream that received the request.

 @param record The request that was received.
 
 @param responder Responder object to be used for responding to the request.

 @since 6.0
 */
-(void)         diffusionStream:(PTDiffusionStream *)stream
    didReceiveRequestWithRecord:(PTDiffusionRecordV2 *)record
                      responder:(PTDiffusionResponder *)responder;

@end

NS_ASSUME_NONNULL_END
