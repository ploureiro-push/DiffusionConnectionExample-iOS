//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2015, 2018 Push Technology Ltd., All Rights Reserved.
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

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Content can represent the state of a topic.

 It may also form the body of a message received from a client.
 A content object is immutable.

 @note The use of this interface is being phased out in favor of specific data
 types. The only remaining places where it must be used is in implementations
 conforming to the older messaging delegate protocols
 PTDiffusionMessageDelegate and PTDiffusionMessageStreamDelegate, and in
 implementations conforming to the fetch delegate protocol
 PTDiffusionFetchStreamDelegate. In all other cases its use should be avoided.

 @since 5.6
 */
@interface PTDiffusionContent : PTDiffusionBytes

/**
 Compares the receiver to the given content.

 @param content The content object with which to compare the receiver.

 @return `YES` if the data in content is equal to the contents of the receiver, otherwise `NO`.

 @note Two content objects are equal if they hold the same number of data bytes, and if the
 bytes at the same position in the objects are the same.

 @since 5.6
 */
-(BOOL)isEqualToContent:(nullable PTDiffusionContent *)content;

@end

NS_ASSUME_NONNULL_END
