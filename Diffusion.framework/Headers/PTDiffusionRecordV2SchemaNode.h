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

NS_ASSUME_NONNULL_BEGIN

/**
 @brief A node within a schema.
 
 @since 6.0
 */
@interface PTDiffusionRecordV2SchemaNode : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 The node name.
 
 @since 6.0
 */
@property(nonatomic, readonly) NSString* name;

/**
 The minimum number of occurrences of the node within its parent.
 
 This may be zero for a variable multiplicity field, otherwise it will be a
 positive value.

 @since 6.0
*/
@property(nonatomic, readonly) SInt32 min;

/**
 The maximum number of occurrances of the node within its parent.
 
 This will be a positive value greater than or equal to the minimum value, or
 -1 to indicate an unlimited number.

 @since 6.0
*/
@property(nonatomic, readonly) SInt32 max;

/**
 `YES` if the node has variable multiplicity - i.e. `min != max`.

 @since 6.0
 */
@property(nonatomic, readonly, getter=isVariable) BOOL variable;

/**
 Compares the receiver to the given schema node.

 @param node The schema node object with which to compare the receiver.

 @return `YES` if the node is equal to the contents of the receiver, otherwise
 `NO`.

 @since 6.0
 */
-(BOOL)isEqualToRecordV2SchemaNode:(nullable PTDiffusionRecordV2SchemaNode *)node;

@end

NS_ASSUME_NONNULL_END
