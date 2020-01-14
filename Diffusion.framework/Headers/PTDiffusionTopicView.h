//  Diffusion Client Library for iOS, tvOS and OS X / macOS
//
//  Copyright (c) 2019 Push Technology Ltd., All Rights Reserved.
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
 @brief Description of a topic view that has been created.

 @see PTDiffusionTopicViewsFeature

 @since 6.3
 */
@interface PTDiffusionTopicView : NSObject <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 The name of the topic view.

 @since 6.3
 */
@property(nonatomic, readonly) NSString * name;

/**
 The specification of the topic view.

 @since 6.3
 */
@property(nonatomic, readonly) NSString * specification;

/**
 The roles used by the topic view when evaluating permissions.

 @since 6.3
 */
@property(nonatomic, readonly) NSArray<NSString *> * roles;

/**
 Compares the receiver to the given topic view.

 @param topicView The topic view object with which to compare the receiver.

 @return `YES` if it matches the receiver, otherwise `NO`.

 @since 6.3
 */
-(BOOL)isEqualToTopicView:(nullable PTDiffusionTopicView *)topicView;

@end

NS_ASSUME_NONNULL_END
