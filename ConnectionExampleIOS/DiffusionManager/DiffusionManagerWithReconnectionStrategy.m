//
//  DiffusionManagerWithReconnectionStrategy.m
//  ConnectionExampleIOS
//
//  Created by Pedro Loureiro on 14/01/2020.
//  Copyright © 2020 Pedro Loureiro. All rights reserved.
//

#import "DiffusionManagerWithReconnectionStrategy.h"

#import "BackOffReconnectionStrategy.h"

@implementation DiffusionManagerWithReconnectionStrategy


- (PTDiffusionSessionConfiguration *)sessionConfiguration
{
    PTDiffusionMutableSessionConfiguration *config = [[[PTDiffusionSessionConfiguration alloc] initWithPrincipal:nil credentials:nil] mutableCopy];
    config.reconnectionStrategy = [[BackOffReconnectionStrategy alloc] initWithMaxDelay:5.0];
    
    return config;
}

- (NSString *)LogHeader
{
    return @"DiffusionManagerWithReconnectionStrategy";
}



@end
