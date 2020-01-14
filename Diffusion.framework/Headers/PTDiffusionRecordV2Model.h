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

@class PTDiffusionRecordV2;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A data model based upon a schema.

 A read only model can be created from any PTDiffusionRecordV2 object using the
 PTDiffusionRecordV2#modelWithSchema: method. The model then provides direct
 access to the fields within the data. Fields may be accessed either by
 explicitly specifying the record and field occurrence or by specifying a key of
 the form:
 
 `recordName(recordIndex).fieldName(fieldIndex)`

 Indexes start from 0 and if omitted then 0 is assumed. The record name may also
 be omitted, in which case the first record definition. This form of addressing
 is useful when there is only one record definition.

 Examples of valid keys include:
 
 | Key                         | Meaning                                                                       |
 | --------------------------- | ----------------------------------------------------------------------------- |
 | `Address(4).AddressLine(3)` | The 4th `AddressLine` occurrence within the 5th `Address` record.             |
 | `Address.Name`              | The first (or only) `Name` field within the first (or only) `Address` record. |
 | `AddressLine(1)`            | The 2nd `AddressLine` field within the first (or only) record.                |
 | `Name`                      | The first (or only) `Name` field within the first (or only) record.           |

 The #recordCountWithRecordName:error: and
 #fieldCountWithRecordName:recordIndex:fieldName:error: methods are useful for
 determining the actual number of occurrences of variable multiplicity items.
 
 @since 6.0
 */
@interface PTDiffusionRecordV2Model : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Returns an immutable record instance generated from this model; or `nil` if an
 error occurred, in which case `*error` will be populated with the failure
 reason.
 
 @param error If this method returns `nil` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @since 6.0
 */
-(nullable PTDiffusionRecordV2 *)valueWithError:(NSError **)error;

/**
 Returns the actual number of occurrences of a named field within a specified
 record occurrence.

 For all but variable fields this returns the schema defined number of
 occurrences of the field.

 @param recordName The record name.

 @param recordIndex The record index.

 @param fieldName The field name.

 @param error If this method returns `nil` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return The actual number of occurrences of the field as an unsigned integer;
 or `nil` if an error occurred, in which case `*error` will be populated with
 the failure reason. Reasons for failure include:
 - either `recordName` or `fieldName` are not defined in the schema.
 - `recordIndex` is out of bounds.

 @exception NSInvalidArgumentException If either recordName or fieldName is
 `nil`, or if recordIndex is negative.

 @since 6.0
 */
-(nullable NSNumber *)fieldCountWithRecordName:(NSString *)recordName
                                   recordIndex:(SInt32)recordIndex
                                     fieldName:(NSString *)fieldName
                                         error:(NSError **)error;

/**
 Returns the actual number of occurrences of a named record.

 If the record is not variable, this is the same as the defined number of
 occurrences in the schema.

 @param recordName The record name.

 @param error If this method returns `nil` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return The actual number of occurrences of the record as an unsigned integer;
 or `nil` if an error occurred, in which case `*error` will be populated with
 the failure reason. Reasons for failure include:
 - `recordName` is not defined in the schema.

 @exception NSInvalidArgumentException If recordName is `nil`.

 @since 6.0
 */
-(nullable NSNumber *)recordCountWithRecordName:(NSString *)recordName
                                          error:(NSError **)error;

/**
 Get a field value.

 This allows an item to be addressed using a key of the form
 `recordName(recordIndex).fieldName(fieldIndex)`. Indexes may be omitted in
 which case 0 is assumed. The record part may also be omitted in which case the
 first occurrence of the first record is assumed.

 @param key The field key.

 @return The field value; or `nil` if an error occurred, in which case `*error`
 will be populated with the failure reason. Reasons for failure include:
 - the key does not address a valid field.
 - an index is out of bounds.
 - the key format is invalid.
 - an index is not a valid number.

 @exception NSInvalidArgumentException If key is `nil`.

 @since 6.0
 */
-(nullable NSString *)fieldValueForKey:(NSString *)key
                                 error:(NSError **)error;

/**
 Get a field value.

 @param recordName The name of the record.

 @param recordIndex the index of the record.

 @param fieldName The name of the field.

 @param fieldIndex The index of the field.

 @param error If this method returns `nil` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return The field value; or `nil` if an error occurred, in which case `*error`
 will be populated with the failure reason. Reasons for failure include:
 - either `recordName` or `fieldName` are not defined in the schema.
 - either `recordIndex` or `fieldIndex` is out of bounds.
 
 @exception NSInvalidArgumentException If either recordName or fieldName is
 `nil`, recordIndex is negative or fieldIndex is negative.

 @since 6.0
 */
-(nullable NSString *)fieldValueForRecordName:(NSString *)recordName
                                  recordIndex:(SInt32)recordIndex
                                    fieldName:(NSString *)fieldName
                                   fieldIndex:(SInt32)fieldIndex
                                        error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
