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

@class PTDiffusionRecordV2DeltaChangeType;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Represents a single change between one record value and another.

 @since 6.0.2
 */
@interface PTDiffusionRecordV2DeltaChange : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 @brief A change contained within a record delta.
 
 @since 6.0.2
 */
@property(nonatomic, readonly) PTDiffusionRecordV2DeltaChangeType* type;

/**
 The name of the affected record.
 
 @since 6.0.2
 */
@property(nonatomic, readonly) NSString* recordName;

/**
 The index of the affected record.
 
 This will be `0` for the first (or only) record occurrence with the given name.

 @since 6.0.2
 */
@property(nonatomic, readonly) SInt32 recordIndex;

/**
 The name of the affected field.
 
 This will be a zero length (empty) string if the type is
 PTDiffusionRecordV2DeltaChangeType#recordsAdded or
 PTDiffusionRecordV2DeltaChangeType#recordsRemoved.

 @since 6.0.2
 */
@property(nonatomic, readonly) NSString* fieldName;

/**
 The index of the affected field.

 This will be `0` if the type is
 PTDiffusionRecordV2DeltaChangeType#recordsAdded or
 PTDiffusionRecordV2DeltaChangeType#recordsRemoved.

 @since 6.0.2
 */
@property(nonatomic, readonly) SInt32 fieldIndex;

/**
 The string key representation of the affected item in the form
 `recordName(recordIndex).fieldName(fieldIndex)` or just
 `recordName(recordIndex)` if the type is
 PTDiffusionRecordV2DeltaChangeType#recordsAdded or
 PTDiffusionRecordV2DeltaChangeType#recordsRemoved.

 @since 6.0.2
 */
@property(nonatomic, readonly) NSString* key;

/**
 Compares the receiver to the given recordV2 delta change.

 @param change The object with which to compare the receiver.

 @return `YES` if the change is equal to the contents of the receiver,
 otherwise `NO`.

 @since 6.0.2
 */
-(BOOL)isEqualToRecordV2DeltaChange:(nullable PTDiffusionRecordV2DeltaChange *)change;

@end

NS_ASSUME_NONNULL_END
