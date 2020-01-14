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
#import <Diffusion/PTDiffusionRecordV2Model.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A mutable data model based upon a schema.

 An initial version of such a model can be created from a schema using
 PTDiffusionRecordV2Schema#createMutableModel. A model created in this way will
 have all mandatory fields set to default values.

 The model may then be updated as required and then at any time a
 PTDiffusionRecordV2 object can be generated from the current state by reading
 the PTDiffusionRecordV2Model#value property. That object may then be used to
 update a topic.

 When values for integer or decimal type fields are supplied the values are
 validated and normalized. All number values will have any insignificant
 leading zeroes removed. A decimal value will also be rounded to its specified
 scale using half-up rounding.

 @since 6.0
 */
@interface PTDiffusionMutableRecordV2Model : PTDiffusionRecordV2Model

/**
 Appends a new initialized record occurrence to the end of a variable
 multiplicity record list.

 As the only variable multiplicity record can be the last one there is no need
 to name the record. This method will add to the list of occurrences of the last
 defined record. The record will be initialized with default values appropriate
 to the schema definition and may then have individual field items set
 separately.

 @param error If this method returns `NO` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return `YES` on success; or `NO` if an error occurred, in which case `*error`
 will be populated with the failure reason. Reasons for failure include:
 - the last or only record is not a variable repeating record or has already
   reached the maximum number of occurrences.
 
 @since 6.0
 */
-(BOOL)addRecordError:(NSError **)error;

/**
 Appends new values to the end of a variable length field list.

 This is a convenience method for adding to the end of the last record and is
 therefore useful when there is only one record type.

 @param fieldValues The values to add.

 @param error If this method returns `NO` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return `YES` on success; or `NO` if an error occurred, in which case `*error`
 will be populated with the failure reason. Reasons for failure include:
 - details conflict with the schema, possibly because the last field of the last
   record is not a variable multiplicity field or the maximum number of
   occurrences for the field would be breached.
 - one of the values is incompatible with the field type.
 
 @exception NSInvalidArgumentException If fieldValues is `nil`.
 
 @note This method does nothing if fieldValues is an empty array.

 @since 6.0
 */
-(BOOL)addFieldValues:(NSArray<NSString *> *)fieldValues
                error:(NSError **)error;

/**
 Appends new values to the end of a variable length field list.

 This can only be used for a variable multiplicity field which can only be the
 last field in a record and therefore the field does not need to be named.

 @param recordName The name of the record.

 @param recordIndex The index identifying the occurrence of the record.

 @param fieldValues The values to add.

 @param error If this method returns `NO` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return `YES` on success; or `NO` if an error occurred, in which case `*error`
 will be populated with the failure reason. Reasons for failure include:
 - details conflict with the schema, possibly because the last field of the
   record is not a variable multiplicity field or the maximum number of
   occurrences for the field would be breached.
 - one of the values is incompatible with the field type.
 - `recordIndex` is out of bounds.

 @exception NSInvalidArgumentException If either recordName or fieldValues is
 `nil`, or if recordIndex is negative.

 @note This method does nothing if fieldValues is an empty array.

 @since 6.0
 */
-(BOOL)addToRecordName:(NSString *)recordName
           recordIndex:(SInt32)recordIndex
           fieldValues:(NSArray<NSString *> *)fieldValues
                 error:(NSError **)error;

/**
 Remove all optional instances of a variable multiplicity field.

 As a variable repeating field can only be the last or only field within a
 record then the field name does not need to be specified.

 This will only remove field occurrences down to the minimum number of
 occurrences specified by the schema.

 If the last or only field within the record is not defined as variable
 multiplicity, this would have no effect.

 @param recordName The name of the record.

 @param recordIndex The index of the record.

 @param error If this method returns `NO` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return `YES` on success; or `NO` if an error occurred, in which case `*error`
 will be populated with the failure reason. Reasons for failure include:
 - `recordName` is not defined in the schema.
 - `recordIndex` is out of bounds.
 
 @exception NSInvalidArgumentException If recordName is `nil`, or if recordIndex
 is negative.

 @since 6.0
 */
-(BOOL)clearVariableFieldsForRecordName:(NSString *)recordName
                            recordIndex:(SInt32)recordIndex
                                  error:(NSError **)error;

/**
 Removes all optional instances of a variable multiplicity record.

 As a variable repeating record can only be the last or only record then the
 record name does not need to be specified.

 This will only remove record occurrences down to the minimum number of
 occurrences specified by the schema.

 If the last or only record is not defined as variable multiplicity, calling
 this method has no effect.
 
 @since 6.0
 */
-(void)clearVariableRecords;

/**
 Removes the specified occurrence of a variable multiplicity field.

 A variable multiplicity field must be the last or only field within a record
 and therefore the field name is not required.

 @param recordName The name of the record.

 @param recordIndex The record index.

 @param fieldIndex The index of the field to remove.

 @param error If this method returns `NO` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return `YES` on success; or `NO` if an error occurred, in which case `*error`
 will be populated with the failure reason. Reasons for failure include:
 - the record is not known or the last or only field within the record is not a
   variable repeating field or can not be removed as it would violate the
   minimum number of occurrences.
 - either `recordIndex` or `fieldIndex` is out of bounds.

 @exception NSInvalidArgumentException If recordName is `nil`, recordIndex is
 negative or fieldIndex is negative.

 @since 6.0
 */
-(BOOL)removeFieldWithIndex:(SInt32)fieldIndex
             fromRecordName:(NSString *)recordName
                recordIndex:(SInt32)recordIndex
                      error:(NSError **)error;

/**
 Removes the specified occurrence of a variable multiplicity record.

 A variable multiplicity record must be the last or only record within a schema
 and therefore the record name is not required.

 @param recordIndex The index of the record to remove.

 @param error If this method returns `NO` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return `YES` on success; or `NO` if an error occurred, in which case `*error`
 will be populated with the failure reason. Reasons for failure include:
 - the last or only record is not a variable multiplicity record or can not be
   removed as it would violate the minimum number of occurrences.
 - `recordIndex` is out of bounds.

 @exception NSInvalidArgumentException If recordIndex is negative.

 @since 6.0
 */
-(BOOL)removeRecordWithIndex:(SInt32)recordIndex
                       error:(NSError **)error;

/**
 Sets a specified field value.

 @param recordName The name of the record containing the field.

 @param recordIndex The index of the record containing the field.

 @param fieldName The name of the field.

 @param fieldIndex The index of the field.

 @param fieldValue The new value.

 @param error If this method returns `NO` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return `YES` on success; or `NO` if an error occurred, in which case `*error`
 will be populated with the failure reason. Reasons for failure include:
 - the details given conflict with the schema or the value is incompatible with
   the schema field type.
 - either `recordIndex` or `fieldIndex` is out of bounds.

 @exception NSInvalidArgumentException If recordName is `nil`, recordIndex is
 negative, fieldName is `nil`, fieldIndex is negative or fieldValue is `nil`.

 @since 6.0
 */
-(BOOL)setRecordName:(NSString *)recordName
         recordIndex:(SInt32)recordIndex
           fieldName:(NSString *)fieldName
          fieldIndex:(SInt32)fieldIndex
        toFieldValue:(NSString *)fieldValue
               error:(NSError **)error;

/**
 Sets a specified field value.

 This allows an item to be addressed using a key of the form
 `recordName(recordIndex).fieldName(fieldIndex)`. Indexes may be omitted in
 which case 0 is assumed. The record part may also be omitted in which case the
 first occurrence of the first record is assumed.

 @param key The field key.

 @param fieldValue The field value.

 @param error If this method returns `NO` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return `YES` on success; or `NO` if an error occurred, in which case `*error`
 will be populated with the failure reason. Reasons for failure include:
 - the key does not address a valid field.
 - a specified index is out of bounds.
 - the key format is invalid.
 - a specified index is not a valid number.

 @exception NSInvalidArgumentException If either key or fieldValue is `nil`.

 @since 6.0
 */
-(BOOL)setFieldValue:(NSString *)fieldValue
              forKey:(NSString *)key
               error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
