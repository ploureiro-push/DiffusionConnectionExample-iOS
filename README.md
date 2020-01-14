#Diffusion Connection Example - Objective C

##Information

This project was built using XCode 11.3 and tested on an iPhone 6S, running iOS 13.3.
The Diffusion version is 6.4, running the SportsBook example.

## How to run the example

1. Open `ConnectionExampleIOS.xcodeproj`
2. Go to `AppDelegate.m` and edit the variable named `_ServerAddress` placing your servers IP adress in the correct format `ws://XXX.XXX.XXX.XXX:8080`
3. Connect an iOS device to your computer, wait for XCode to detect it
4. Press `Run` with the Target `ConnectionExampleIOS` and your device selected


## What to expect from this example

This example shows a reconnection strategy that is more sympathetic to the iOS app lifecycle.

A common source of disconnection is placing the App in the background for long period of time, after which the server closes session and its connection, as the iOS cannot respond to server ping requests.

You can place your App in the background by either going to the home screen (pressing the home button) or pressing the power button (triggering the lock screen).

When the App starts it creates a new session with the Diffusion server. When the App becomes active, it will check if there is a session in the `DiffusionManager`. If so, it pings the server to validate it.


Please look at the following console logs:

```
2020-01-14 10:27:26.827199+0000 ConnectionExampleIOS[13088:5475939] Application: active
2020-01-14 10:27:26.827344+0000 ConnectionExampleIOS[13088:5475939] DiffusionManagerWithReconnectionStrategy: no session detected. Creating a new one
2020-01-14 10:27:26.904919+0000 ConnectionExampleIOS[13088:5475939] DiffusionManagerWithReconnectionStrategy: session opened [6c600e92e7b2bff0-0000000300000001]
2020-01-14 10:27:26.905055+0000 ConnectionExampleIOS[13088:5475939] DiffusionManagerWithReconnectionStrategy: setting up a fallback stream for JSON
2020-01-14 10:27:26.905253+0000 ConnectionExampleIOS[13088:5475939] DiffusionManagerWithReconnectionStrategy: setting up a session state observer
2020-01-14 10:27:26.905380+0000 ConnectionExampleIOS[13088:5475939] Application: session is active
2020-01-14 10:27:26.905498+0000 ConnectionExampleIOS[13088:5475939] Application: setting up a timer that pings the server every 3 seconds
2020-01-14 10:27:26.905701+0000 ConnectionExampleIOS[13088:5475939] DiffusionManagerWithReconnectionStrategy: Session State Change: to 'Connected Active' from 'Connecting'
2020-01-14 10:27:29.966882+0000 ConnectionExampleIOS[13088:5475939] DiffusionManagerWithReconnectionStrategy: ping successful (0ms)
```

Once the App detects it is active, it detects that no session had been created (first run), creates a session and successfully pings the server.


Please look at the following console logs:

```
2020-01-14 10:27:48.017984+0000 ConnectionExampleIOS[13088:5476102] SocketStream read error [0x2807b6040]: 1 54
2020-01-14 10:27:48.018803+0000 ConnectionExampleIOS[13088:5475939] BackOffReconnectionStrategy --> session wishes to reconnect. Current state of strategy --> attempt:[1] delay:[0] maxDelay:[5]
2020-01-14 10:27:48.019342+0000 ConnectionExampleIOS[13088:5475939] DiffusionManagerWithReconnectionStrategy: Session State Change: to 'Recovering Reconnect' from 'Failing'
2020-01-14 10:27:48.019453+0000 ConnectionExampleIOS[13088:5475939] BackOffReconnectionStrategy --> attempt starting now
2020-01-14 10:27:48.136848+0000 ConnectionExampleIOS[13088:5476105] [] nw_socket_handle_socket_event [C2.1:1] Socket SO_ERROR [61: Connection refused]
2020-01-14 10:27:48.137658+0000 ConnectionExampleIOS[13088:5476105] [] nw_connection_get_connected_socket [C2] Client called nw_connection_get_connected_socket on unconnected nw_connection
2020-01-14 10:27:48.137871+0000 ConnectionExampleIOS[13088:5476105] TCP Conn 0x2807b09c0 Failed : error 0:61 [61]
2020-01-14 10:27:48.139345+0000 ConnectionExampleIOS[13088:5475939] BackOffReconnectionStrategy --> elapsed time since last attempt: 0.12054
2020-01-14 10:27:48.139421+0000 ConnectionExampleIOS[13088:5475939] BackOffReconnectionStrategy --> session wishes to reconnect. Current state of strategy --> attempt:[2] delay:[1] maxDelay:[5]
...
2020-01-14 10:27:51.616943+0000 ConnectionExampleIOS[13088:5475939] BackOffReconnectionStrategy --> elapsed time since last attempt: 2.26328
2020-01-14 10:27:51.617151+0000 ConnectionExampleIOS[13088:5475939] BackOffReconnectionStrategy --> session wishes to reconnect. Current state of strategy --> attempt:[4] delay:[3] maxDelay:[5]
2020-01-14 10:27:51.617662+0000 ConnectionExampleIOS[13088:5475939] DiffusionManagerWithReconnectionStrategy: Session State Change: to 'Recovering Reconnect' from 'Failing'
2020-01-14 10:27:51.618962+0000 ConnectionExampleIOS[13088:5475939] DiffusionManagerWithReconnectionStrategy: Session State Change: to 'Failing' from 'Recovering Reconnecting'
2020-01-14 10:27:54.876957+0000 ConnectionExampleIOS[13088:5475939] BackOffReconnectionStrategy --> attempt starting now
2020-01-14 10:27:54.998789+0000 ConnectionExampleIOS[13088:5475939] DiffusionManagerWithReconnectionStrategy: Session State Change: to 'Connected Active' from 'Recovering Reconnecting'
2020-01-14 10:27:57.033965+0000 ConnectionExampleIOS[13088:5475939] DiffusionManagerWithReconnectionStrategy: ping successful (0ms)
```
In this example, a proxy was set up between the iOS client and the server. The proxy was killed, resulting in the App attempting to reconnect to the server.
The proxy was brought back up, leading to a successfull re-connection.

The `BackOffReconnectionStrategy` is the custom reconnection strategy in `DiffusionManagerWithReconnectionStrategy`.
The first attempt is immediate, and each further attempt is delayed by an additional 1.0 seconds up to a maximum of 5.0 seconds.
Should the connection fall again, if the elapsed time since the last successful reconnection attempt and the next attempt be longer than 10.0 seconds, the next attempt will not incurr of any delay.
This reconnection strategy was inspired in the [Exponential Backoff Algorithm](https://en.wikipedia.org/wiki/Exponential_backoff) in Carrier Sense Multiple Access with Collision Detection networks.


##Why does this happen?

To better understand an iOS App lifecycle, we recommend reading about [how to manage your app's life cycle](https://developer.apple.com/documentation/uikit/app_and_environment/managing_your_app_s_life_cycle).

When an iOS App goes into the background, the App needs to treat this as it can/will be terminated soon and the developer needs to save the state in a permanent manner.
When `- (void)applicationDidEnterBackground:(UIApplication *)application` is triggered, the App doesn't know if it's going to be reopenned soon, as the User is just answering a call, sending a message, checking something else in another App, returning briefly or simply pressing the Power Button and leaving the device idle for a couple of hours.

For the App to recover from this situation, when `- (void)applicationDidBecomeActive:(UIApplication *)application` is triggered, the developers need to treat this call as one of possible 3 situations:

1. It's the first run of the App or the App was previously closed and the App needs to setup the session with the Diffusion server

2. The App is returning from a short pause, the previously created session is still valid and no further setup is required

3. The App is returning from a long pause, the previously created session is no longer valid (ie. closed by the Diffusion server) and further setup is required to create new one.

This example bundles case [1] and [3] together, as the first setup and recovery from lost session is the same.
