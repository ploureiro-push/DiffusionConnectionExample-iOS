//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2015, 2017 Push Technology Ltd., All Rights Reserved.
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
 @brief A version represents a released build of the client library.
 
 Version numbers are described with dotted notation in the form
 `<major>.<minor>.<patch>`.

 @since 5.6
 */
@interface PTDiffusionVersion : NSObject <NSCopying>

/**
 Return the product version of this client library.

 @since 5.6
 */
+(instancetype)versionOfClientLibrary;

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 The major (left, most significant) component of the version number.

 @since 5.6
 */
@property(nonatomic, readonly) NSUInteger major;

/**
 The minor (middle) component of the version number.

 @since 5.6
 */
@property(nonatomic, readonly) NSUInteger minor;

/**
 The patch (right, least significant) component of the version number.

 @since 5.6
 */
@property(nonatomic, readonly) NSUInteger patch;

/**
 Additional information about this build of the client library.

 @since 5.6.6
 */
@property(nonatomic, readonly) NSDictionary<NSString *, NSString *>* manifest;

/**
 Compares the receiver to the given version.

 @param version The version object with which to compare the receiver.

 @return `YES` if the receiver and the given version are the same.

 @since 5.6
 */
-(BOOL)isEqualToVersion:(nullable PTDiffusionVersion *)version;

@end

NS_ASSUME_NONNULL_END
