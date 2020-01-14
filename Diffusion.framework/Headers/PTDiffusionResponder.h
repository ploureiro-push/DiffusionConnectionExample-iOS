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

@class PTDiffusionResponse;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Responder provided with requests, used to dispatch responses.

 @see PTDiffusionRequestHandler
 @see PTDiffusionBinary
 @see PTDiffusionJSON
 @see PTDiffusionPrimitive
 @see PTDiffusionRecordV2

 @since 6.0
 */
@interface PTDiffusionResponder : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Dispatch a response to a request.

 @param response The value to send in response.

 @exception NSInvalidArgumentException Raised if the response argument is `nil`.

 @since 6.1
 */
-(void)respondWithResponse:(PTDiffusionResponse *)response;

/**
 Dispatch a rejection to a request, indicating that a response could not be
 generated.
 
 @param reason Freeform text to provide to the requestor by way of explanation
 for this rejection.
 
 @exception NSInvalidArgumentException Raised if the reason argument is `nil`.

 @since 6.0
 */
-(void)rejectWithReason:(NSString *)reason;

@end

NS_ASSUME_NONNULL_END
