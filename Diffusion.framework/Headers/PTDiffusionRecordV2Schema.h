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

@class PTDiffusionMutableRecordV2Model;
@class PTDiffusionRecordV2SchemaRecord;

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A schema.
 
 A schema describes data value format in terms of one or more record definitions.
 A record definition describes the layout of a record and comprises one or more
 field definitions.

 Within the data value there can be multiple occurrences of a record or field
 described by a single definition. The defined (or allowed, when describing
 variable numbers) number of occurrences of each definition is referred to as
 its 'multiplicity'. The multiplicity can be fixed (the item occurs a fixed
 number of times), or variable (the item occurs from a minimum number of times
 to a maximum number of times). If a variable field is used it must be the last
 in a record definition and if a variable record is used it must be the last in
 the schema definition.

 A field may be defined as of type 'string', 'integer' or 'decimal'. A decimal
 type has a further property of 'scale' which defines the number of digits to
 the right of the decimal point.
 
 @see PTDiffusionRecordV2SchemaBuilder

 @since 6.0
 */
@interface PTDiffusionRecordV2Schema : NSObject

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Returns a schema object initialized from the given JSON definition.
 
 @param jsonData Encoded JSON string representation of the schema.
 
 @param error If this method returns `nil` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @return An immutable schema derived from the JSON representation; or `nil` if
 an error occurred, in which case `*error` will be populated with the failure
 reason.

 @since 6.0
 */
+(nullable instancetype)schemaWithJSONData:(NSData *)jsonData
                                     error:(NSError **)error;

/**
 Returns the schema in a JSON format.
 
 @since 6.0
 */
-(NSData *)JSONData;

/**
 Create a mutable model based upon the schema.

 The model will be created with all mandatory record occurrences and all
 mandatory field occurrences initialized to default values.

 Such a model may be mutated and used to generate updated PTDiffusionRecordV2
 instances for updating purposes.

 @return a new initialized model.
 
 @since 6.0
 */
-(PTDiffusionMutableRecordV2Model *)createMutableModel;

/**
 An immutable, ordered list of record definitions.

 There will be at least one.

 @since 6.0
 */
@property(nonatomic, readonly) NSArray<PTDiffusionRecordV2SchemaRecord *> * records;

/**
 Compares the receiver to the given schema.

 @param schema The schema object with which to compare the receiver.

 @return `YES` if the schema is equal to the contents of the receiver, otherwise
 `NO`.

 @since 6.0
 */
-(BOOL)isEqualToRecordV2Schema:(nullable PTDiffusionRecordV2Schema *)schema;

@end

NS_ASSUME_NONNULL_END
