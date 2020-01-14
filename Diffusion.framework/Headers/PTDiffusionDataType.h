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
 @brief Methods implemented by classes providing data type implementations.
 
 A data type is specified for a particular class (its value class). It provides
 methods to convert values of the value class to and from binary. Diffusion
 provides several data type implementations.

 A data type can optionally support incremental changes to values, represented
 by one or more types of delta.

 @see PTDiffusionDataTypes
 
 @since 6.0
 */
@protocol PTDiffusionDataType

/**
 The unique external identifier for this data type.

 @since 6.0
 */
@property(nonatomic, readonly) NSString* typeName;

@end

NS_ASSUME_NONNULL_END
