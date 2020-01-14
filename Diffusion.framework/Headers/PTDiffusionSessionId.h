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
 @brief A session ID is a unique session identifier, allocated by the server.
 
 @see PTDiffusionSession

 @since 5.6
 */
@interface PTDiffusionSessionId : NSObject  <NSCopying>

+(instancetype)new NS_UNAVAILABLE;

-(instancetype)init NS_UNAVAILABLE;

/**
 Returns a session ID object initialized with the given string.
 
 @param string A string, previously returned by the `description` method on an
 instance of this class.

 @param error If this method returns `nil` to indicate that an error occured
 then this will be populated with the reason for that failure.

 @note The string representation used is the same as that provided by our Java
 client library (see the `toString()` method on `SessionId`). This is a client
 operation. A session that has been closed will not be recreated.

 @exception NSInvalidArgumentException If the given string is `nil`.

 @since 6.0
 */
-(nullable instancetype)initWithString:(NSString *)string
                                 error:(NSError **)error NS_DESIGNATED_INITIALIZER;

/**
 Compares the receiver to the given session ID.

 @param sessionId The session ID object with which to compare the receiver.

 @return `YES` if the given session ID is equal to the receiver, otherwise `NO`.

 @since 5.6
 */
-(BOOL)isEqualToSessionId:(nullable PTDiffusionSessionId *)sessionId;

@end

NS_ASSUME_NONNULL_END
