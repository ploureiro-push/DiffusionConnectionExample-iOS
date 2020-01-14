//
//  BackOffReconnectionStrategy.h
//  ConnectionExampleIOS
//
//  Created by Pedro Loureiro on 13/01/2020.
//  Copyright © 2020 Pedro Loureiro. All rights reserved.
//

#import <Diffusion/Diffusion.h>

NS_ASSUME_NONNULL_BEGIN

@interface BackOffReconnectionStrategy: NSObject<PTDiffusionSessionReconnectionStrategy>

@property(nonatomic, readonly) NSTimeInterval maxDelay;

-(instancetype) initWithMaxDelay:(const NSTimeInterval)delay;


@end

NS_ASSUME_NONNULL_END
