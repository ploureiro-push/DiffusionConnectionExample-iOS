//
//  BackOffReconnectionStrategy.m
//  ConnectionExampleIOS
//
//  Created by Pedro Loureiro on 13/01/2020.
//  Copyright © 2020 Pedro Loureiro. All rights reserved.
//

#import "BackOffReconnectionStrategy.h"

@implementation BackOffReconnectionStrategy
{
    int _currentAttempt;
    NSDate * _lastConnectionAttempt;
}

static const NSTimeInterval _delayIncrementation = 1.0;

@synthesize maxDelay = _maxDelay;

/**
 
    Concept behind this reconnection strategy
 
    When this strategy is called for the first time in its session, the reconnection attempt is immediate
    If the first attempt fails, it waits for 1.0 seconds before trying again. Each subsequent failed attempt will increase the delay by another 1.0 seconds
    If this reconnection strategy is called after an interval greater than the last reconnection attempt delay, it considers that the last attempt was a successful one, and reset the attempt counter.
    For each reconnection attempt, the attempt timestamp is registered in the reconnection strategy
                 
 */
-(instancetype) initWithMaxDelay:(const NSTimeInterval)delay
{
    self = [super init];
    if (!self)
    {
        return nil;
    }
    _maxDelay = delay;
    _currentAttempt = 0;
    
    return self;
}


- (void)diffusionSession:(PTDiffusionSession *)session wishesToReconnectWithAttempt:(PTDiffusionSessionReconnectionAttempt *)attempt
{
    // calculate the delay based on the amount of attempts while reconnecting to the server
    NSTimeInterval delay = MIN(_currentAttempt * _delayIncrementation, _maxDelay);
    
    // if a connection attempt was made in the past of this session, _lastConnectionAttempt has a value set)
    if (_lastConnectionAttempt)
    {
        NSTimeInterval elapsedSinceLastConnection = [[NSDate date] timeIntervalSinceDate:_lastConnectionAttempt];
        NSLog(@"BackOffReconnectionStrategy --> elapsed time since last attempt: %g", elapsedSinceLastConnection);
        
        // if it elapsed more time than twice the expected delay for the last connection attempt (max delay is 5.0s, so if at least 10.0s have elapsed)
        // then we consider than the last attempt was successful and reset the attempt counter
        if (elapsedSinceLastConnection > delay * 2)
        {
            NSLog(@"BackOffReconnectionStrategy --> previous attempt was successful, reseting the reconnection attempts");
            
            // the session is attempting to reconnect again since last disconnection, reset the attempt counter
            _currentAttempt = 0;
            
            // recalculate the delay as well
            delay = MIN(_currentAttempt * _delayIncrementation, _maxDelay);
        }
    }
    // last connection timestamp is being set here (without taking into consideration the delay that is calculated right after
    // this is to prevent multiple calls being made while waiting for the delay
    _lastConnectionAttempt = [NSDate date];
    
    
    NSLog(@"BackOffReconnectionStrategy --> session wishes to reconnect. Current state of strategy --> attempt:[%d] delay:[%g] maxDelay:[%g]", _currentAttempt + 1, delay, _maxDelay);
    
    // increment the attempt counter for the next time this is called and for future calculations of when the connection actually happened
    _currentAttempt += 1;
    
    // wait for [delay] seconds and attempt to reconnect
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        NSLog(@"BackOffReconnectionStrategy --> attempt starting now");
        [attempt start];
    });
}

@end
