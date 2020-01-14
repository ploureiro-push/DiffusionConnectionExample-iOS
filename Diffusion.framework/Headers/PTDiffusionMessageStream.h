//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2016, 2018 Push Technology Ltd., All Rights Reserved.
//
//  Use is subject to license terms.
//
//  NOTICE: All information contained herein is, and remains the
//  property of Push Technology. The intellectual and technical
//  concepts contained herein are proprietary to Push Technology and
//  may be covered by U.S. and Foreign Patents, patents in process, and
//  are protected by trade secret or copyright law.

@import Foundation;
#import <Diffusion/PTDiffusionStream.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A message stream represents an asynchronous, variable length feed of
 message events from the Diffusion server.

 @see PTDiffusionMessagingFeature

 @deprecated Since 6.2. One-way messaging has been deprecated in favor of
 request-response messaging. This interface will be removed in a future release.
 see: @ref md_messaging "Messaging with the Apple client library".

 @since 5.9
 */
__deprecated_msg("Will be removed in a future release.")
@interface PTDiffusionMessageStream : PTDiffusionStream

@end

NS_ASSUME_NONNULL_END
