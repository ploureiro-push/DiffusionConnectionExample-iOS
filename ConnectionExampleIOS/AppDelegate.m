//  Diffusion Example for iOS, tvOS and OS X / macOS
//
//  Copyright (C) 2015, 2020 Push Technology Ltd.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#import "AppDelegate.h"
#import "BackOffReconnectionStrategy.h"

#import "DiffusionManager.h"
#import "DiffusionManagerWithReconnectionStrategy.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

static NSString *const _ServerAddress = @"ws://XXX.XXX.XXX.XXX:8080";
static NSString *const _TopicSelectorExpression = @"*Demos/Sportsbook/Football/England//";
static NSString *const _TopicSelectorExpressionForAll = @"*Demos//";


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    return YES;
}


#pragma mark - App delegates


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
    NSLog(@"Application: will resign active");
    [self.window.rootViewController.view setBackgroundColor:UIColor.grayColor];
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    NSLog(@"Application: in the background");
    [self.window.rootViewController.view setBackgroundColor:UIColor.systemPinkColor];
    //
    //NSLog(@"Application: attempting to unsubscribe from topics");
    //[DiffusionManager.sharedManager unsubscribeFrom:_TopicSelectorExpression];
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
    NSLog(@"Application: entering the foreground");
    //
    
    [self.window.rootViewController.view setBackgroundColor:UIColor.yellowColor];
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    NSLog(@"Application: active");
    
    NSURL *url = [NSURL URLWithString:_ServerAddress];
    [DiffusionManagerWithReconnectionStrategy.sharedManager connectToURL:url withCompletionHandler:^(PTDiffusionSession * _Nullable session, NSError * _Nullable error) {
        if (session)
        {
            NSLog(@"Application: session is active");
            [self.window.rootViewController.view setBackgroundColor:UIColor.greenColor];
            
            //NSLog(@"Application: attempting to subscribe to topics");
            //[DiffusionManager.sharedManager subscribeTo:_TopicSelectorExpression];
        }
        else
        {
            NSLog(@"Application: error while creating session: %@", error);
            [self.window.rootViewController.view setBackgroundColor:UIColor.redColor];
        }
    }];
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    NSLog(@"Application: will terminate");
    
    [DiffusionManagerWithReconnectionStrategy.sharedManager closeSession];
}


@end
