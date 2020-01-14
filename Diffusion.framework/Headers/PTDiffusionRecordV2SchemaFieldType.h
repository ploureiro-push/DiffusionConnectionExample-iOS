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
#import <Diffusion/PTDiffusionEnumeration.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Type of field defined within a schema.
 
 @since 6.0
 */
@interface PTDiffusionRecordV2SchemaFieldType : PTDiffusionEnumeration

/**
 Plain string.

 @since 6.0
 */
+(instancetype)string;

/**
 Integer.

 @since 6.0
 */
+(instancetype)integer;

/**
 Decimal.

 @since 6.0
 */
+(instancetype)decimal;

@end

NS_ASSUME_NONNULL_END
