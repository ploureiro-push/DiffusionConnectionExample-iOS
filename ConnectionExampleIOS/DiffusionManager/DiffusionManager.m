//
//  DiffusionManager.m
//  ConnectionExampleIOS
//
//  Created by Pedro Loureiro on 14/01/2020.
//  Copyright © 2020 Pedro Loureiro. All rights reserved.
//

#import "DiffusionManager.h"

@implementation DiffusionManager



+ (id)sharedManager
{
    static DiffusionManager *_manager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _manager = [[self alloc] init];
    });
    return _manager;
}


#pragma mark - actions

- (void)connectToURL:(NSURL *)url withCompletionHandler:(void (^ _Nullable)(PTDiffusionSession * _Nullable session, NSError * _Nullable error)) completionHandler
{
    if (self.session)
    {
        NSLog(@"%@: detected existing session", self.LogHeader);
        if ([self.url isEqual:url])
        {
            NSLog(@"%@: detected session is connected to the same URL. Pinging server", self.LogHeader);
            [self pingServer];
        }
        else
        {
            NSLog(@"%@: detected session is connected to a different URL. closing current session and opening a new one", self.LogHeader);
            [self.session close];
            
            [self createNewSession:url withCompletionHandler:completionHandler];
        }
    }
    else
    {
        NSLog(@"%@: no session detected. Creating a new one", self.LogHeader);
        [self createNewSession:url withCompletionHandler:completionHandler];
    }
}

- (void) createNewSession:(NSURL *)url withCompletionHandler:(void (^)(PTDiffusionSession * _Nullable session, NSError * _Nullable error)) completionHandler
{
    [PTDiffusionSession openWithURL:url configuration:self.sessionConfiguration completionHandler:^(PTDiffusionSession * _Nullable session, NSError * _Nullable error) {
        if (!session)
        {
            NSLog(@"%@: failed to open session: %@", self.LogHeader, error);
        }
        else
        {
            NSLog(@"%@: session opened [%@]", self.LogHeader, session.sessionId);
            self.session = session;
            self.url = url;
            
            // fallback streams are for subscribed topics that do not have a value/topic stream registered specifically for it
            NSLog(@"%@: setting up a fallback stream for JSON", self.LogHeader);
            PTDiffusionValueStream *const stream = [PTDiffusionJSON valueStreamWithDelegate:self];
            [session.topics addFallbackStream:stream];
            
            NSLog(@"%@: setting up a session state observer", self.LogHeader);
            NSNotificationCenter* nc = [NSNotificationCenter defaultCenter];
            [nc addObserverForName:PTDiffusionSessionStateDidChangeNotification object:session queue:nil usingBlock:^(NSNotification * _Nonnull note) {
                PTDiffusionSessionStateChange* change = note.userInfo[PTDiffusionSessionStateChangeUserInfoKey];
                NSLog(@"%@: Session State Change: %@", self.LogHeader, change);
            }];
        }
        
        if (completionHandler)
        {
            completionHandler(session, error);
        }
    }];
}


- (void) closeSession
{
    if (self.session)
    {
        NSLog(@"%@: closing session", self.LogHeader);
        [self.session close];
        self.session = nil;
    }
}
                  


- (PTDiffusionSessionConfiguration *)sessionConfiguration
{
    return [[PTDiffusionSessionConfiguration alloc] initWithPrincipal:nil credentials:nil];
}

- (NSString *)LogHeader
{
    return @"DiffusionManager";
}

-(void)pingServer
{
    if (self.session)
    {
        [self.session.pings pingServerWithCompletionHandler:^(PTDiffusionPingDetails * _Nullable details, NSError * _Nullable error) {
            if (error)
            {
                // only goes here after attempting all possible solutions in the reconnection strategy
                NSLog(@"%@: Error detected while pinging the server: %@", self.LogHeader, error);
                
                if ([error.domain isEqualToString:PTDiffusionSessionErrorDomain])
                {
                    // error came from the Diffusion API
                    if (error.code == PTDiffusionSessionErrorCode_Disconnected || error.code == PTDiffusionSessionErrorCode_Establishment)
                    {
                        NSLog(@"%@: Session has been closed. Opening a new one", self.LogHeader);
                        [self.session close];
                        self.session = nil;
                        [self connectToURL:self->_url withCompletionHandler:nil];
                    }
                }
            }
            else
            {
                NSLog(@"%@: ping successful (%dms)", self.LogHeader, (int) round(details.roundTripTime * 1000));
            }
        }];
    }
    else
    {
        NSLog(@"%@: no session detected. Aborting", self.LogHeader);
    }
}



- (void)unsubscribeFrom:(NSString *)selector
{
    NSLog(@"DiffusionManager: Unsubscribing from [%@]", selector);
    
    [self.session.topics unsubscribeFromTopicSelectorExpression:selector completionHandler:^(NSError * _Nullable error) {
        if (error)
        {
            NSLog(@"\t\tDiffusionManager: Unsubscribe request ([%@]) failed: %@", selector, error);
        }
        else
        {
            NSLog(@"\t\tDiffusionManagerUnsubscribe request ([%@]) succeeeded", selector);
        }
    }];
}


- (void)subscribeTo:(NSString *)selector
{
    NSLog(@"%@: Subscribing to [%@]", self.LogHeader, selector);
    
    [self.session.topics subscribeWithTopicSelectorExpression:selector completionHandler:^(NSError * _Nullable error) {
        if (error)
        {
            NSLog(@"\t\%@: Subscribe request ([%@]) failed: %@", self.LogHeader, selector, error);
        }
        else
        {
            NSLog(@"\t\%@: Subscribe request ([%@]) succeeded", self.LogHeader, selector);
        }
    }];
}

#pragma mark - Diffusion delegates

- (void)diffusionDidCloseStream:(nonnull PTDiffusionStream *)stream {
    NSLog(@"\t\%@: Stream closed", self.LogHeader);
}

- (void)diffusionStream:(nonnull PTDiffusionStream *)stream didFailWithError:(nonnull NSError *)error {
    NSLog(@"\t\%@: Stream failed with error: %@", self.LogHeader, error);
}

- (void)diffusionStream:(nonnull PTDiffusionStream *)stream didSubscribeToTopicPath:(nonnull NSString *)topicPath specification:(nonnull PTDiffusionTopicSpecification *)specification {
    NSLog(@"\t\%@: Subscribed to %@ (%@)", self.LogHeader, topicPath, specification);
}

- (void)diffusionStream:(nonnull PTDiffusionStream *)stream didUnsubscribeFromTopicPath:(nonnull NSString *)topicPath specification:(nonnull PTDiffusionTopicSpecification *)specification reason:(PTDiffusionTopicUnsubscriptionReason)reason {
    NSLog(@"\t\%@: Unsubscribed from %@ (%@)", self.LogHeader, topicPath, specification);
}

- (void)diffusionStream:(nonnull PTDiffusionValueStream *)stream didUpdateTopicPath:(nonnull NSString *)topicPath specification:(nonnull PTDiffusionTopicSpecification *)specification oldJSON:(nullable PTDiffusionJSON *)oldJson newJSON:(nonnull PTDiffusionJSON *)newJson {
    NSLog(@"\t\%@: Updated %@ = %@", self.LogHeader, topicPath, newJson);
}

- (void)diffusionStream:(nonnull PTDiffusionStream *)stream didFetchTopicPath:(nonnull NSString *)topicPath content:(nonnull PTDiffusionContent *)content {
    NSLog(@"\t\%@: Fetch result: %@ = %@", self.LogHeader, topicPath, content);
}

- (void)diffusionStream:(nonnull PTDiffusionStream *)stream didReceiveError:(nonnull NSError *)error fromSessionId:(nonnull PTDiffusionSessionId *)sessionId {
    NSLog(@"\t\%@: Session error: %@", self.LogHeader, error);
}

@end
