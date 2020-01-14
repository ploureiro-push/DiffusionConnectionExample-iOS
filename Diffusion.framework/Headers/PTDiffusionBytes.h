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
 @brief A value that is internally represented as binary data.

 A bytes object is immutable.

 @since 5.9
 */
@interface PTDiffusionBytes : NSObject <NSCopying>

/**
 Returns a bytes object initialized with the given data.

 @param data A data object encapsulating the bytes.
 
 @note Since Diffusion 5.9 this method has been moved from PTDiffusionContent
 to this new super interface.

 @since 5.9
 */
-(instancetype)initWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;

/**
 The data encapsulated by the receiver.

 @note Since Diffusion 5.9 this property has been moved from PTDiffusionContent
 to this new super interface.

 @since 5.9
 */
@property(nonatomic, readonly, copy) NSData* data;

/**
 Compares the receiver to the given bytes.

 @param bytes The bytes object with which to compare the receiver.

 @return `YES` if the bytes are equal to the contents of the receiver, otherwise `NO`.

 @note Two bytes objects are equal if they hold the same number of bytes, and if the
 bytes at the same position in the objects are the same.

 @since 5.9
 */
-(BOOL)isEqualToBytes:(nullable PTDiffusionBytes *)bytes;

@end

NS_ASSUME_NONNULL_END
