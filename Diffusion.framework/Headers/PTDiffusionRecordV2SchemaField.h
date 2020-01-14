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
#import <Diffusion/PTDiffusionRecordV2SchemaNode.h>

@class PTDiffusionRecordV2SchemaFieldType;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A field definition within a schema.

 @since 6.0
 */
@interface PTDiffusionRecordV2SchemaField : PTDiffusionRecordV2SchemaNode

/**
 The field type.
 
 @since 6.0
 */
@property(nonatomic, readonly) PTDiffusionRecordV2SchemaFieldType* type;

/**
 The scale of a decimal field or zero for other types.

 @since 6.0
 */
@property(nonatomic, readonly) SInt32 scale;

/**
 Compares the receiver to the given schema field.

 @param field The schema field object with which to compare the receiver.

 @return `YES` if the field is equal to the contents of the receiver, otherwise
 `NO`.

 @since 6.0
 */
-(BOOL)isEqualToRecordV2SchemaField:(nullable PTDiffusionRecordV2SchemaField *)field;

@end

NS_ASSUME_NONNULL_END
