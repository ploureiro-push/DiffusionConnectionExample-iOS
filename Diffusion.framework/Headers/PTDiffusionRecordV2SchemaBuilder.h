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

@class PTDiffusionRecordV2Schema;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief Used to build an immutable PTDiffusionRecordV2Schema.

 A schema defines the records and fields that may occur in a RecordV2 topic
 value.

 The schema must declare at least one record type and every record must have at
 least one field type declared.

 Every record type and field type has a 'multiplicity' which defines the number
 of times that the record or field may occur within the data. Multiplicity is
 specified as a 'minimum' and 'maximum' number of occurrences or where the
 minimum and maximum are the same (fixed multiplicity) then the multiplicity may
 be specified as a single 'occurs' value. If the minimum and maximum are
 different, this is referred to a 'variable' multiplicity. Only the last record
 declared or the last field within a record may have variable multiplicity. The
 maximum value may be declared as -1 to indicate that the record or field can
 have an unlimited number of occurrences.

 The builder is used to add a record definition followed by the fields within
 it. After all fields have been added to a record another may then be added, and
 so on, and then finally #schema is queried to return an immutable schema
 object.

 Every mutating method returns the builder instance allowing calls to be
 chained.

 @since 6.0
 */
@interface PTDiffusionRecordV2SchemaBuilder : NSObject

/**
 Returns an immutable schema from the current state of this builder.
 
 @exception NSInternalInconsistencyException No records have been specified yet
 for this builder instance.

 @since 6.0
 */
-(PTDiffusionRecordV2Schema *)build;

/**
 Add a new single occurrence record to the schema.
 
 This is the equivalent to calling #addRecordWithName:occurs: with a value of
 `1` for `occurs`.

 @param name The record name.

 @return This builder.

 @exception NSInvalidArgumentException If `name` is `nil`.

 @exception NSInternalInconsistencyException If schema rules are violated.

 @since 6.0
 */
-(instancetype)addRecordWithName:(NSString *)name;

/**
 Add a new fixed multiplicity record to the schema.

 This is the equivalent to calling #addRecordWithName:min:max: with the value of
 `occurs` for both `min` and `max`.

 @param name The record name.
 
 @param occurs The number of times the record is to occur. This must be a
 positive value.

 @return This builder.
 
 @exception NSInvalidArgumentException If `name` is `nil` or `occurs` is less
 than one.

 @exception NSInternalInconsistencyException If schema rules are violated.

 @since 6.0
 */
-(instancetype)addRecordWithName:(NSString *)name
                          occurs:(SInt32)occurs;

/**
 Add a new record to the schema.

 @param name The record name.

 @param min The minimum number of occurrences of the record.

 @param max The maximum number of occurrences of the record. This must either be
 `-1` to indicate an unlimited number or it must be a positive number greater
 than or equal to `min`.

 @return This builder.

 @exception NSInvalidArgumentException If `name` is `nil` or `max` is invalid.

 @exception NSInternalInconsistencyException If schema rules are violated.

 @since 6.0
 */
-(instancetype)addRecordWithName:(NSString *)name
                             min:(SInt32)min
                             max:(SInt32)max;

/**
 Add a new single occurrence string field to the current record.

 This is the equivalent to calling #addStringWithName:occurs: with a value of
 `1` for `occurs`.

 @param name The field name. This must not be the same as any field already
 added to the record.

 @return This builder.

 @exception NSInvalidArgumentException If `name` is `nil`.

 @exception NSInternalInconsistencyException If schema rules are violated.

 @since 6.0
 */
-(instancetype)addStringWithName:(NSString *)name;

/**
 Add a new fixed multiplicity string field to the current record.

 This is the equivalent to calling #addStringWithName:min:max: with the value of
 `occurs` for both `min` and `max`.

 @param name The field name. This must not be the same as any field already
 added to the record.

 @param occurs The number of times the field is to occur within the record. This
 must be a positive value.

 @return This builder.

 @exception NSInvalidArgumentException If `name` is `nil` or `occurs` is less
 than one.

 @exception NSInternalInconsistencyException If schema rules are violated.

 @since 6.0
 */
-(instancetype)addStringWithName:(NSString *)name
                          occurs:(SInt32)occurs;

/**
 Add a new string field to the current record.

 @param name The field name. This must not be the same as any field already
 added to the record.

 @param min The minimum number of occurrences of the field within the record.

 @param max The maximum number of occurrences of the field within the record.
 This must either be `-1` to indicate an unlimited number or it must be a
 positive number greater than or equal to `min`.

 @return This builder.

 @exception NSInvalidArgumentException If `name` is `nil` or `max` is invalid.

 @exception NSInternalInconsistencyException If schema rules are violated.

 @since 6.0
 */
-(instancetype)addStringWithName:(NSString *)name
                             min:(SInt32)min
                             max:(SInt32)max;

/**
 Add a new single occurrence integer field to the current record.

 This is the equivalent to calling #addIntegerWithName:occurs: with a value of
 `1` for `occurs`.

 @param name The field name. This must not be the same as any field already
 added to the record.

 @return This builder.

 @exception NSInvalidArgumentException If `name` is `nil`.

 @exception NSInternalInconsistencyException If schema rules are violated.

 @since 6.0
 */
-(instancetype)addIntegerWithName:(NSString *)name;

/**
 Add a new fixed multiplicity integer field to the current record.

 This is the equivalent to calling #addIntegerWithName:min:max: with the value
 of `occurs` for both `min` and `max`.

 @param name The field name. This must not be the same as any field already
 added to the record.

 @param occurs The number of times the field is to occur within the record. This
 must be a positive value.

 @return This builder.

 @exception NSInvalidArgumentException If `name` is `nil` or `occurs` is less
 than one.

 @exception NSInternalInconsistencyException If schema rules are violated.

 @since 6.0
 */
-(instancetype)addIntegerWithName:(NSString *)name
                           occurs:(SInt32)occurs;

/**
 Add a new integer field to the current record.

 @param name The field name. This must not be the same as any field already
 added to the record.

 @param min The minimum number of occurrences of the field within the record.

 @param max The maximum number of occurrences of the field within the record.
 This must either be `-1` to indicate an unlimited number or it must be a
 positive number greater than or equal to `min`.

 @return This builder.

 @exception NSInvalidArgumentException If `name` is `nil` or `max` is invalid.

 @exception NSInternalInconsistencyException If schema rules are violated.

 @since 6.0
 */
-(instancetype)addIntegerWithName:(NSString *)name
                              min:(SInt32)min
                              max:(SInt32)max;

/**
 Add a new single occurrence decimal field to the current record.

 This is the equivalent to calling #addDecimalWithName:scale:occurs: with a
 value of `1` for `occurs`.

 @param name The field name. This must not be the same as any field already
 added to the record.
 
 @param scale The scale of the field (the number of decimal places). This must
 must be a positive value.

 @return This builder.

 @exception NSInvalidArgumentException If `name` is `nil` or `scale` is less
 than one.

 @exception NSInternalInconsistencyException If schema rules are violated.

 @since 6.0
 */
-(instancetype)addDecimalWithName:(NSString *)name
                            scale:(SInt32)scale;

/**
 Add a new fixed multiplicity decimal field to the current record.

 This is the equivalent to calling #addDecimalWithName:scale:min:max: with the
 value of `occurs` for both `min` and `max`.

 @param name The field name. This must not be the same as any field already
 added to the record.

 @param scale The scale of the field (the number of decimal places). This must
 must be a positive value.

 @param occurs The number of times the field is to occur within the record. This
 must be a positive value.

 @return This builder.

 @exception NSInvalidArgumentException If `name` is `nil`, `scale` is less than
 one or `occurs` is less than one.

 @exception NSInternalInconsistencyException If schema rules are violated.

 @since 6.0
 */
-(instancetype)addDecimalWithName:(NSString *)name
                            scale:(SInt32)scale
                           occurs:(SInt32)occurs;

/**
 Add a new decimal field to the current record.

 @param name The field name. This must not be the same as any field already
 added to the record.

 @param scale The scale of the field (the number of decimal places). This must
 must be a positive value.

 @param min The minimum number of occurrences of the field within the record.

 @param max The maximum number of occurrences of the field within the record.
 This must either be `-1` to indicate an unlimited number or it must be a
 positive number greater than or equal to `min`.

 @return This builder.

 @exception NSInvalidArgumentException If `name` is `nil` or `max` is invalid.

 @exception NSInternalInconsistencyException If schema rules are violated.

 @since 6.0
 */
-(instancetype)addDecimalWithName:(NSString *)name
                            scale:(SInt32)scale
                              min:(SInt32)min
                              max:(SInt32)max;

@end

NS_ASSUME_NONNULL_END
