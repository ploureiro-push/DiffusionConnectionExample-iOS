//
//  DiffusionManager.h
//  ConnectionExampleIOS
//
//  Created by Pedro Loureiro on 14/01/2020.
//  Copyright © 2020 Pedro Loureiro. All rights reserved.
//

#import <Foundation/Foundation.h>

@import Diffusion;

NS_ASSUME_NONNULL_BEGIN

@interface DiffusionManager : NSObject <PTDiffusionJSONValueStreamDelegate, PTDiffusionFetchStreamDelegate, PTDiffusionSessionResponseStreamDelegate>

// only one session in the Diffusion Manager
@property (nullable) PTDiffusionSession *session;
@property (nullable) NSURL *url;


- (void)connectToURL:(NSURL *)url withCompletionHandler:(void (^ _Nullable)(PTDiffusionSession * _Nullable session, NSError * _Nullable error)) completionHandler;
- (void)closeSession;

- (void)subscribeTo:(NSString *)selector;
- (void)unsubscribeFrom:(NSString *)selector;

- (void)testConnectionWithServer;

- (PTDiffusionSessionConfiguration *)sessionConfiguration;
- (NSString *)LogHeader;

+ (id)sharedManager;

@end

NS_ASSUME_NONNULL_END
