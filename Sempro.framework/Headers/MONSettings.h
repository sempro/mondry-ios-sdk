//
//  MONSettings.h
//  Sempro
//

#import <UIKit/UIKit.h>
#import "MONAuthenticationDelegate.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *  @abstract When added to allowedMenuItems, enables the option to take a photo from the conversation view
 */
extern NSString * const MONMenuItemCamera;

/**
 *  @abstract When added to allowedMenuItems, enables the option to select an image or video from gallery from the conversation view
 */
extern NSString * const MONMenuItemGallery;

/**
 *  @abstract When added to allowedMenuItems, enables the option to upload a document from the conversation view
 */
extern NSString * const MONMenuItemDocument;

/**
 *  @abstract When added to allowedMenuItems, enables the option to share location from the conversation view
 */
extern NSString * const MONMenuItemLocation;

@interface MONSettings : NSObject

/**
 *  @abstract Initializes a settings object with the given app id.
 *
 *  @param appId A valid app id retrieved from the Sempro web portal.
 */
+(instancetype)settingsWithAppId:(NSString*)appId;

/**
 *  @abstract Initializes a settings object with the given app id and auth code.
 *
 *  @param appId A valid app id retrieved from the Sempro web portal.
 *  @param authCode A valid auth code generated from the Sempro API.
 */
+(instancetype)settingsWithAppId:(NSString*)appId andAuthCode:(NSString*)authCode;

/**
 *  @abstract The app id corresponding to your application.
 *
 *  @discussion App id can be retrieved from the Sempro web portal
 *
 *  This value may only be set once, and must be set at init time.
 */
@property(nonatomic, copy) NSString* appId;

/**
 *  @abstract The auth code being used to authenticate as an existing user.
 *
 *  @discussion Auth code can be retrieved from the Sempro API
 *
 *  This value may only be set once, and must be set at init time.
 */
@property(nonatomic, copy) NSString* authCode;

/**
 *  @abstract The Sempro region for this account.
 *
 *  @discussion Leave unspecified to use the default region (US). Set to "eu-1" to use the EU region.
 *
 */
@property(nonatomic, copy) NSString* region;

/**
 *  @abstract The accent color for the conversation screen.
 *
 *  @discussion Used as the color of user message bubbles, as well as the color of the send button and text input caret.
 *
 *  The default value is #00B0FF.
 */
@property(nonatomic, strong) UIColor* conversationAccentColor;

/**
 *  @abstract The text color for user messages.
 *
 *  @discussion Used as the text color of user message bubbles.
 *
 *  The default value is #FFFFFF.
 */
@property(nonatomic, strong) UIColor* userMessageTextColor;

/**
 *  @abstract The status bar style to use on the conversation screen.
 *
 *  @discussion You should use this property if your app uses UIAppearance to style UINavigationBar, and your styling requires a specific status bar color.
 *
 *  The default value is UIStatusBarStyleDefault.
 */
@property UIStatusBarStyle conversationStatusBarStyle;

/**
 *  @abstract The items to display in the conversation menu
 *
 *  @discussion Valid values are MONMenuItemCamera, MONMenuItemGallery, MONMenuItemDocument and MONMenuItemLocation
 *
 *  All options are displayed by default. Setting this value to nil or an empty array will hide the menu button
 */
@property(nonatomic, strong, nullable) NSArray<NSString *>* allowedMenuItems;

/**
 *  @abstract Allow sending messages from the conversation view when offline
 *
 *  @discussion Setting this to `YES` allows the user to send messages even when the device is offline. It also prevents an network error banner from showing when offline.
 *
 *  Note that messages that are sent while offline will fail to send and the message will display an option for the user to retry
 */
@property BOOL allowOfflineUsage;

/**
 *  @abstract Maximum number of seconds to display in-app notifications before dismissing.
 *
 *  @discussion Setting this value to 0 will cause notications to stay on-screen until the user acts on them.
 *
 *  The default value is 8.
 */
@property NSUInteger notificationDisplayTime;

/**
 *  @abstract Whether or not to swizzle app delegate methods for handling push notifications.
 *
 *  @discussion When set to YES, Sempro will swizzle the following methods of your UIApplicationDelegate in order to automatically handle push notification receiving and registering, as well as user notification handling.
 *
 *  1. -application:didRegisterForRemoteNotificationsWithDeviceToken:
 *  2. -application:didFailToRegisterForRemoteNotificationsWithError:
 *  3. -application:didReceiveRemoteNotification:
 *  4. -application:didReceiveRemoteNotification:fetchCompletionHandler:
 *  5. -application:handleActionWithIdentifier:forRemoteNotification:withResponseInfo:completionHandler:
 *
 *  If set to NO, Sempro will not perform swizzling. It is up to the app to handle Sempro push notifications by doing the following:
 *
 *  1. When a new push token is received in -application:didRegisterForRemoteNotificationsWithDeviceToken:, you must call Sempro +setPushToken.
 *  2. In your -application:didReceiveRemoteNotification: or -application:didReceiveRemoteNotification:fetchCompletionHandler: callback, you must call Sempro +handlePushNotification: with the passed userInfo dictionary.
 *  3. In your -application:handleActionWithIdentifier:forRemoteNotification:withResponseInfo:completionHandler: callback, you must call Sempro +handleUserNotificationActionWithIdentifier:withResponseInfo:completionHandler: with the correct parameters.
 *
 *  The default value is YES.
 *
 *  @see Sempro
 */
@property BOOL enableAppDelegateSwizzling;

/**
 *  @abstract Whether or not to automatically replace the application's UNUserNotificationCenterDelegate at init time.
 *
 *  @discussion For more information, see the +userNotificationCenterDelegate method of the Sempro class.
 *
 *  If set to NO, the application must forward calls from its own UNUserNotificationCenterDelegate to Sempro to ensure proper handling of notifications on iOS 10.
 *
 *  The default value is YES.
 *
 *  @see Sempro
 */
@property BOOL enableUserNotificationCenterDelegateOverride;

/**
 *  @abstract Whether or not to request user notification privileges after the user sends their first message.
 *
 *  @discussion If your app has a preferred time to request user notification privileges, set this to NO.
 *
 *  If set to NO, the application must make sure to register the Sempro user notification category settings. For more information, see the +userNotificationCategories method of the Sempro class.
 *
 *  The default value is YES.
 *
 *  @see Sempro
 */
@property BOOL requestPushPermissionOnFirstMessage;

/**
 *  @abstract Delegate that will be notified of authentication related events
 *
 *  @discussion This delegate is useful if your app uses expiring tokens for your users. This way you can renew an invalid jwt when needed without having to call +login:jwt:completionHandler. May be nil
 *
 *  This value may only be set once, and must be set at init time.
 *
 *  @see MONAuthenticationDelegate
 */
@property(nullable) id<MONAuthenticationDelegate> authenticationDelegate;

@end
NS_ASSUME_NONNULL_END
