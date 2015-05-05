/*
 *
 * Kamcord Framework for recording and sharing gameplays on iOS.
 *
 */

#import <UIKit/UIKit.h>
#import <CoreAudio/CoreAudioTypes.h>

/*
 *
 * Kamcord protocols to receive callbacks.
 *
 */
#import "KamcordProtocols.h"

/*
 *
 * Import C interface.
 *
 */
#import "Kamcord-C-Interface.h"

/*
 *
 * Core Kamcord video recording.
 *
 */
#import "KamcordRecorder.h"

/**
 *
 * Current version is 1.9.2 (2014-03-03)
 *
 */
extern NSString *const KamcordVersion;

/**
 *
 * The Kamcord device blacklist options.
 *
 */
typedef NS_ENUM(NSUInteger, KCDeviceType) {
    KCDeviceTypeiPod4G          = 1 << 0,
    KCDeviceTypeiPod5G          = 1 << 1,
    
    KCDeviceTypeiPhone3GS       = 1 << 2,
    KCDeviceTypeiPhone4         = 1 << 3,
    KCDeviceTypeiPhone4S        = 1 << 4,
    KCDeviceTypeiPhone5         = 1 << 5,
    KCDeviceTypeiPhone5C        = 1 << 6,
    KCDeviceTypeiPhone5S        = 1 << 7,
    KCDeviceTypeiPhone6         = 1 << 15,
    KCDevicetypeiPhone6Plus     = 1 << 16,
    
    KCDeviceTypeiPad1           = 1 << 8,
    KCDeviceTypeiPad2           = 1 << 9,
    KCDeviceTypeiPadMini        = 1 << 10,
    KCDeviceTypeiPad3           = 1 << 11,
    KCDeviceTypeiPad4           = 1 << 12,
    KCDeviceTypeiPadAir         = 1 << 13,
    KCDeviceTypeiPadMiniRetina  = 1 << 14,
    
    KCDeviceTypeSingleCore      = (KCDeviceTypeiPod4G | KCDeviceTypeiPhone3GS | KCDeviceTypeiPhone4 | KCDeviceTypeiPad1)
};

/**
 *
 * @warning This is now deprecated.
 * @see KCDeviceType
 */
__deprecated typedef NS_ENUM(NSUInteger, KC_DEVICE_TYPE) {
    KC_DEVICE_TYPE_IPOD_4G          = 1 << 0,
    KC_DEVICE_TYPE_IPOD_5G          = 1 << 1,
    KC_DEVICE_TYPE_IPHONE_3GS       = 1 << 2,
    KC_DEVICE_TYPE_IPHONE_4         = 1 << 3,
    KC_DEVICE_TYPE_IPHONE_4S        = 1 << 4,
    KC_DEVICE_TYPE_IPHONE_5         = 1 << 5,
    KC_DEVICE_TYPE_IPHONE_5C        = 1 << 6,
    KC_DEVICE_TYPE_IPHONE_5S        = 1 << 7,
    KC_DEVICE_TYPE_IPAD_1           = 1 << 8,
    KC_DEVICE_TYPE_IPAD_2           = 1 << 9,
    KC_DEVICE_TYPE_IPAD_MINI        = 1 << 10,
    KC_DEVICE_TYPE_IPAD_3           = 1 << 11,
    KC_DEVICE_TYPE_IPAD_4           = 1 << 12,
    KC_DEVICE_TYPE_IPAD_AIR         = 1 << 13,
    // Equivalent to (KC_DEVICE_TYPE_IPOD_4G | KC_DEVICE_TYPE_IPHONE_3GS | KC_DEVICE_TYPE_IPHONE_4 | KC_DEVICE_TYPE_IPAD_1)
    KC_DEVICE_TYPE_SINGLE_CORE      = (1 << 0 | 1 << 2 | 1 << 3 | 1 << 8)
};


/**
 * 
 * The various tabs in the Kamcord UI.
 *
 */
typedef NS_ENUM(NSUInteger, KCUITab) {
/// The watch tab - Allows a user to watch other videos from this game.
    KCUITabWatch = 0,
/// The profile tab - Shown for a specific user's profile.
    KCUITabProfile,
/// The promotional
    KCUITabPromo,
/// The share tab - Shown when a recorded video is ready to be shared.
    KCUITabShare,
};

/**
 *  @warning this is now deprecated.
 *  @see KCUITab
 */
__deprecated typedef NS_ENUM(NSUInteger, KC_UI_INITIAL_TAB) {
    KC_WATCH_TAB = 0,
    KC_PROFILE_TAB,
    KC_CROSS_PROMO_TAB,
    KC_SHARE_TAB,
};

/**
 *  Describes the current state of age gating. 
 *
 */
typedef NS_ENUM(NSUInteger, KCAgeGateStatus) {
/**
 The user has not encountered the age gate.
 */
    KCAgeGateStatusUnknown,
/**
 The user is under age and their activites have been restricted
 */
    KCAgeGateStatusRestricted,
/**
 The user is of appropriate age and their activities will not be restricted
 */
    KCAgeGateStatusUnrestricted,
};

/**
 This block will be called when the age gate status has been changed
 */
typedef void(^KCAgeGateStatusUpdatedBlock)(KCAgeGateStatus status);

/**
 *
 * The Kamcord API
 *
 */
@interface Kamcord : NSObject

/// -------------------------------------------------------------------------
/// @name Configuration
/// -------------------------------------------------------------------------

/**
 *
 * The current version of the Kamcord SDK in the format X.Y.Z.
 *
 * @returns     A string describing the current Kamcord SDK.
 *
 */
+ (NSString *)SDKVersion;

/** Gracefully disable Kamcord on certain devices.
 *
 * @param   blacklist       An integer bitmap of KC_DEVICE_TYPE describing the devices to disable Kamcord for.
 * @warning If you use this method, make sure it's the first Kamcord call you make.
 *
 * `[Kamcord setDeviceBlacklist:(KCDeviceTypeiPod4G | KCDeviceTypeiPhone3GS | KCDeviceTypeiPad1)];`
 *
 */
+ (void)setDeviceBlacklist:(KCDeviceType)blacklist;

/**
 *
 * Kamcord initialization. Set your developer key, secret, app name,
 * and the UIViewController that will present the Kamcord UI when 
 * you call `[Kamcord showView]`.
 *
 * @param   key                     Your Kamcord developer key.
 * @param   secret                  Your Kamcord developer secret.
 * @param   appName                 The name of your application.
 * @param   parentViewController    The UIViewController that will present the Kamcord UI.
 *
 */
+ (void)setDeveloperKey:(NSString *)key
        developerSecret:(NSString *)secret
                appName:(NSString *)appName
   parentViewController:(UIViewController *)parentViewController;

/**
 *
 * @return The previously set developer key
 *
 */
+ (NSString *)developerKey;

/**
 * @return The previously set developer secret.
 */
+ (NSString *)developerSecret;

/**
 * @return The previously set application name
 */
+ (NSString *)appName;

/**
 * @return The previously set parent view controller, from which the Kamcord UI will be presented.
 */
+ (UIViewController *)parentViewController;

/**
 *
 * Set the UIViewController that will later present the Kamcord UI when you call `[Kamcord showView]`.
 *
 * @param       viewController      The view controller that will present the Kamcord UI.
 *
 * This should initially be set by `setDeveloperKey:developerSecret:appName:parentViewController:`
 * but can still be used if your app's parent view controller changes.
 */
+ (void)setParentViewController:(UIViewController *)viewController;

/**
 *
 * Returns YES if and only if the device is running iOS 5+ and
 * has not been blacklisted via `setDeviceBlacklist:`.
 *
 * @returns Whether or not Kamcord is enabled on the current device.
 *
 */
+ (BOOL)isEnabled;

/**
 *
 * Returns the current interface orientation.
 *
 * @returns     The app's current interface orientation.
 *
 */
+ (UIInterfaceOrientation)interfaceOrientation;

/**
 *
 * Turns on and off Kamcord video push notifications.
 *
 *
 * @param       enabled     Whether or not to enable video push notifications.
 *
 * Today, we schedule 4 "Gameplay of the Week" notifications for each of the
 * next 4 weeks.
 */
+ (void)setNotificationsEnabled:(BOOL)enabled;

/**
 *
 * Returns whether or not video push notifications are enabled.
 *
 * @returns     Whether or not video push notifications are enabled.
 *
 */
+ (BOOL)notificationsEnabled;

/**
 *
 * Pass Kamcord the local notifications from `didReceiveLocalNotification:` and
 * `didFinishLaunchingWithOptions:` if the notification data has the "Kamcord" key.
 * You can also pass us all your local notifications and we will handle the ones
 * relevant to Kamcord and ignore the rest.
 *
 * @param       notification        The local notification for the Kamcord video push notification.
 *
 */
+ (void)handleKamcordNotification:(UILocalNotification *)notification;

/**
 *
 * Fires a test notification - makes it possible to experience the behavior
 * in an app without waiting for Kamcord's servers to fire a weekly notification.
 * This is intended for test purposes only - do not ship with this.
 *
 */
+ (void)fireTestNotification;

/// -------------------------------------------------------------------------
/// @name Recording
/// -------------------------------------------------------------------------

/// Start recording a new video
+ (void)startRecording;

/// Stop recording the current video
+ (void)stopRecording;

/// Resume a paused recording
+ (void)resume;

/// Pause a recording in progress
+ (void)pause;

/**
 *
 * Is a video currently being recorded?
 *
 * @returns     Whether or not a video is currently recording.
 *              The only time this video returns `YES` is when frames are
 *              in the process of being written to a video.
 *              Note that this will return `NO` if the video is paused.
 *
 */
+ (BOOL)isRecording;

/**
 *
 * Is the current recording paused?
 *
 * @returns     Whether or not the current video recording has been paused.
 *
 */
+ (BOOL)isPaused;

/**
 *
 * Show the Kamcord share view and watch view inside the previously set `parentViewController`;
 * This is identical to `[Kamcord showViewInViewController:[Kamcord parentViewController]]`.
 *
 */
+ (void)showView;

/**
 *
 * Show the Kamcord view inside the given `UIViewController`.
 *
 * @param       parentViewController    The `UIViewController` that will show the Kamcord UI.
 *
 */
+ (void)showViewInViewController:(UIViewController *)parentViewController;

/**
 *
 * Show the Kamcord watch view inside the previously set `parentViewController`.
 * This is identical to `[Kamcord showWatchViewInViewController:[Kamcord parentViewController] initialTab:KC_WATCH_TAB]`.
 *
 */
+ (void)showWatchView;

/**
 *
 * Show the Kamcord watch view inside the given UIViewController.
 *
 * @param       parentViewController    The UIViewController that will show the Kamcord watch view.
 *
 */
+ (void)showWatchViewInViewController:(UIViewController *)parentViewController;

/**
 *
 * Show the Kamcord watch view inside the given UIViewController.
 *
 * @param       parentViewController    The UIViewController that will show the Kamcord watch view.
 * @param       initialTab              The initial tab that will be open. Can either be the watch tab,
 *                                      the profile tab, or the cross promotion tab if you have the cross
 *                                      promotion feature enabled for your game. The default screen is
 *                                      the watch screen.
 *
 */
+ (void)showWatchViewInViewController:(UIViewController *)parentViewController
                           initialTab:(KCUITab)initialTab;

/**
 *
 * Is a Kamcord view showing?
 *
 * @returns     Whether or not a Kamcord view is showing.
 *
 */
+ (BOOL)isViewShowing;

/**
 *
 * Receive callbacks about the life of a recorded video. Please note that this
 * object is *NOT* retained by Kamcord.
 *
 * The KamcordDelegate protocol is defined in <Kamcord/KamcordProtocols.h>.
 *
 * @param       delegate        The delegate to receive Kamcord callbacks.
 * @see KamcordDelegate
 */
+ (void)setDelegate:(id <KamcordDelegate>)delegate;

/**
 *
 * Returns the current Kamcord delegate.
 *
 * @returns     The current Kamcord delegate.
 *
 */
+ (id <KamcordDelegate>)delegate;

/**
 *
 * Set the quality of the recorded video. The default setting
 * is `KCVideoQualityStandard`;
 *
 * @param   quality     The desired recorded video quality.
 *
 */
+ (void)setVideoQuality:(KCVideoQuality)quality;

/**
 *
 * Returns the quality of the recorded videos.
 *
 * @returns     The quality of the recorded videos.
 *
 */
+ (KCVideoQuality)videoQuality;

/**
 *
 * Set the maximum length of a recorded video in seconds. If the gameplay lasts longer
 * than that, only the last N seconds will get recorded in the final video.
 *
 * @param       seconds     The maximum video length.
 *
 */
+ (void)setMaximumVideoLength:(NSUInteger)seconds;

/**
 *
 * Returns the maximum possible recorded video length.
 *
 * @returns     The maximum possible recorded video length.
 *
 */
+ (NSUInteger)maximumVideoLength;

/**
 *
 * Is there a valid video such that `[Kamcord showView]` would show the Kamcord UI?
 * Note that `[Kamcord showView]` is always safe to call, even if there is no video.
 *
 * @returns     Whether or not there's a valid video that [Kamcord showView] could present.
 *
 */
+ (BOOL)hasValidVideo;

/**
 * Returns true if there is at least one video matching the constraints
 *
 * @param      constraints              A dictionary of (NSString *) metadataDisplayKey ->
 *                                      (NSObject *) value. NSString and NSNumber are supported for value.
 *
 */
+ (BOOL)videoExistsForMetadataConstraints:(NSDictionary *)constraints;

/**
 * Shows a Kamcord Video player playing a video with all metadata conforming to the constraints
 * given
 *
 * @param      constraints              A dictionary of (NSString *) metadataDisplayKey ->
 *                                      (ID *) value. NSString and NSNumber are supported for
 * @param      title                    The desired title to be displayed in the shown player.
 *                                      If nil is passed in, it uses the title the video was shared with.
 *
 */
+ (void)showVideoWithMetadataConstraints:(NSDictionary *)constraints
                               withTitle:(NSString *)title;

/**
 *
 * Shows a Kamcord Video player playing the video corresponding to the Id
 *
 * @param      videoID                  ID of the video to be played.
 * @param      title                    The desired title to be displayed in the shown player.
 *                                      If nil is passed in, it uses the title the video was shared with.
 *
 */
+ (void)showVideoWithVideoID:(NSString *)videoID
                   withTitle:(NSString *)title;

/// -------------------------------------------------------------------------
/// @name Audio
/// -------------------------------------------------------------------------

/**
 *
 * Note: This method is only to be used for non-OpenAL/Unity game engines.
 *       For cocos2d/cocos2d-x/Unity (and other OpenAL-based sound engines),
 *       Kamcord will figure out the correct AudioStreamBasicDescription and 
 *       set it automatically. Using this method in those cases will most 
 *       likely break audio recording.
 *
 * Declare the description of the audio stream. This method MUST be called before
 * any audio data is written and before startRecording is called.
 *
 * @param       asbd        The AudioStreamBasicDescription of the byte stream to record.
 *
 */
+ (void)setASBD:(AudioStreamBasicDescription)asbd;

/**
 *
 * Write the live audio bytes to the recorded video. This is ONLY for custom audio engines.
 * If you use OpenAL or Unity's game engine, there is no need for this method.
 *
 * @param       data        A pointer to the raw PCM bytes to record into the currently recording video.
 *                          The data format of this data must match the previously set asbd.
 * @param       numSamples  The number of PCM samples pointed to by the given data pointer.
 *
 */
+ (void)writeAudioBytes:(void *)data
             numSamples:(UInt32)numSamples;


/// -------------------------------------------------------------------------
/// @name Voice
/// -------------------------------------------------------------------------

/**
 *
 * This enables or disables voice recording.
 *
 *      1. Your user can activate (i.e. turn on microphone voice recording) 
 *          in the Kamcord Settings UI
 *      2. You can activate it on behalf of the user by calling 
 *          `[Kamcord activateVoiceOverlay:YES]`.
 *
 * The main reason this method exists is to disable voice overlay in your games
 * so that your users cannot enable voice overlay via the Kamcord Settings UI.
 * @param enabled Whether or not voice overlay is enabled for this game
 * @see activateVoiceOverlay:
 */
+ (void)setVoiceOverlayEnabled:(BOOL)enabled;

/// @returns Whether or not voice overlay has been enabled for this game
+ (BOOL)voiceOverlayEnabled;

/**
 *
 * Once voice overlay is enabled, the user must activate it by going to the
 * Kamcord Settings UI and enabling it there. You can also programatically 
 * activate it with the following API calls.
 *
 * Please note that voice overlay *MUST* first be enabled before trying to
 * activate it.
 * @param activate Whether or not you want to programmatically activate voice overlay
 * @see setVoiceOverlayEnabled:
 */
+ (void)activateVoiceOverlay:(BOOL)activate;

/// @returns Whether or not the user has activated voice overlay
+ (BOOL)voiceOverlayActivated;

/// -------------------------------------------------------------------------
/// @name Video Metadata and Social Media Settings
/// -------------------------------------------------------------------------

/**
 *
 * Sets the WeChat App ID so you can set it as a share target in the share grid.
 *
 * In order to use WeChat, you *MUST* link you app against libWeChatSDK.a and
 * add "-ObjC" to Build Settings => Other Linker Flags.
 *
 * @param       weChatAppId   The WeChat App ID.
 *
 */
+ (void)setWeChatAppId:(NSString *)weChatAppId;

/**
 *
 * Returns whether or not WeChat sharing is enabled. In order to enable WeChat
 * sharing, you *MUST* do the following:
 *
 *      1. Link you app against libWeChatSDK.a.
 *      2. Add "-ObjC" to Build Settings => Other Linker Flags.
 *      3. `[Kamcord setWeChatAppID:]` with a valid WeChat app ID.
 *
 * @warning **ATTENTION**: As of 2014-04-14, the latest available WeChat static lib (libWeChatSDK.a)
 * only contains slices for armv7, armv7s, and i386. This means that if you
 * want WeChat to work on arm64 devices like the iPhone 5S, iPad Air, and
 * iPad Mini Retina, you *MUST* build your app to target the armv7 and armv7s
 * architectures but *NOT* include arm64. If you include arm64 as a valid architecture,
 * WeChat will only be available on non arm64 devices (and this method wil return NO on arm64 devices)!
 * This restriction will be removed as soon as WeChat releases a new SDK that has an arm64 slice.
 *
 * @returns     Whether or not WeChat sharing is enabled on the current device.
 *
 */
+ (BOOL)isWeChatEnabled;

/**
 *
 * Set the ways users can share their videos. You can use this method to choose which 
 * forms of social media users will have access to when they go to share a replay. By default
 * the sharing options are Facebook, Twitter, Youtube, Email. You must pass in
 * exactly four valid distinct KCShareDestination enums, else nothing will be changed. The order
 * of these parameters will affect how the share options are laid out in the UI.
 *
 * The possible values are defined in <Kamcord/Kamcord-C-Interface.h>.
 *
 * Note: If you select KCShareDestinationWeChat as an option, you *MUST* call
 *       [Kamcord setWeChatAppID:...] with a valid WeChat App ID, else your
 *       user will not be able to share to WeChat.
 *
 *       You *MUST* also link your app against libWeChatSDK.a and
 *       add "-ObjC" to Build Settings => Other Linker Flags.
 *
 * @param       target1             The top-left element of the share grid
 * @param       target2             The top-right element of the share grid
 * @param       target3             The bottom-left element of the share grid
 * @param       target4             The bottom-right element of the share grid
 *
 */
+ (void)setShareTargetsWithTarget1:(KCShareDestination)target1
                           target2:(KCShareDestination)target2
                           target3:(KCShareDestination)target3
                           target4:(KCShareDestination)target4;

/**
 *
 * Set a piece of metadata for the recorded video
 * All metadata is cleared with the start of a recorded video
 *
 * @param       metadataType       The type of metaData (see the enum `KCMetadataType` for more info)
 * @param       displayKey         Describe what the metadata is
 * @param       displayValue       A string representation of the value for this metadata
 * @see KCMetadataType
 */
+ (void)setDeveloperMetadata:(KCMetadataType)metadataType
                  displayKey:(NSString *)displayKey
                displayValue:(NSString *)displayValue;

/**
 *
 * Set a piece of metadata for the recorded video
 * All metadata is cleared with the start of a recorded video
 *
 * @param       metadataType       The type of metaData (see the enum `KCMetadataType` for more info)
 * @param       displayKey         Describe what the metadata is
 * @param       displayValue       A string representation of the value for this metadata
 * @param       numericValue       A numeric representation of the value for this metadata
 * @see KCMetadataType
 */
+ (void)setDeveloperMetadata:(KCMetadataType)metadataType
                  displayKey:(NSString *)displayKey
                displayValue:(NSString *)displayValue
                numericValue:(NSNumber *)numericValue;

/**
 *
 * Return the level of the last video (after it's been set).
 *
 */
+ (NSString *)level;

/**
 *
 * Return the score of the last video (after it's been set).
 *
 */
+ (NSNumber *)score;

/**
 *
 * Returns the developer metadata pieces currently set
 *
 */
+ (NSDictionary *)developerMetadata;

/// ---------------------------------------------------
/// @name Social Networks & Sharing
/// ---------------------------------------------------
/**
 *
 * Set title of the video on Kamcord watch pages and on YouTube.
 * If the user enters their own title in the Kamcord Share UI,
 * their title will override this.
 *
 * @param       title       The title of the video on the Kamcord watch page and on YouTube.
 *
 */
+ (void)setVideoTitle:(NSString *)title;

/**
 *
 * Returns the previously set video tite.
 *
 * @returns     The title of the last video.
 *
 */
+ (NSString *)videoTitle;

/**
 *
 * Set the YouTube description and tags of the shared video.
 *
 * @param       description     The YouTube description for this video.
 * @param       tags            The YouTube tags for this video.
 *
 */
+ (void)setYouTubeDescription:(NSString *)description
                         tags:(NSString *)tags;

/**
 *
 * Returns the previously set YouTube description.
 *
 */
+ (NSString *)youtubeDescription;

/**
 *
 * Returns the previously set YouTube tags.
 *
 */
+ (NSString *)youtubeTags;

/**
 *
 * Set the NicoNico description of the shared video.
 *
 * @param       clientID        The NicoNico client id for this video.
 * @param       clientSecret    The NicoNico client secret for this video.
 *
 */
+ (void)setNicoNicoClientID:(NSString *)clientID
                  andSecret:(NSString *)clientSecret;

/*
 *
 * Set the NicoNico description of the shared video.
 *
 * @param       description     The NicoNico description for this video.
 *
 */
+ (void)setNicoNicoDescription:(NSString *)description;

/*
 *
 * Returns the previously set NicoNico client id.
 *
 */
+ (NSString *)niconicoClientID;

/*
 *
 * Returns the previously set NicoNico client secret.
 *
 */
+ (NSString *)niconicoClientSecret;

/*
 *
 * Returns the previously set NicoNico description.
 *
 */
+ (NSString *)niconicoDescription;

/*
 *
 * For iOS 6+, if you have a Facebook app you'd like to share from, you can set its
 * Facebook App ID here for native iOS 6 sharing. Setting sharedAuth to YES
 * will give Kamcord access to the app's Facebook auth instead of Kamcord requesting
 * its own permissions. To use sharedAuth, you *MUST* request the publish_actions
 * permission and be using Facebook SDK 3.1 or later. The advantage of sharedAuth is
 * that the user is not prompted for auth again. If you aren't using the Facebook SDK
 * in your game, you can set sharedAuth to NO and we'll take care of things using the
 * Kamcord Facebook appID.
 *
 * @param       facebookAppID   The Facebook App ID.
 * @param       sharedAuth      Whether Facebook auth should be shared between the app and Kamcord.
 *
 */
+ (void)setFacebookAppID:(NSString *)facebookAppID
              sharedAuth:(BOOL)sharedAuth;

/**
 *
 * By default, all shares to Facebook will be done via the Kamcord Facebook appID.
 * However, for iOS 6+, if you have a Facebook app you'd like to share from, you can set its
 * Facebook App ID here for native iOS 6+ sharing.
 *
 * @param       facebookAppID   The Facebook App ID.
 *
 */
+ (void)setFacebookAppID:(NSString *)facebookAppID;

/**
 *
 * Returns the previously set Facebook App ID.
 *
 * @returns     The previously set Facebook App ID.
 *
 */
+ (NSString *)facebookAppID;

/** If you use Facebook shared auth and want to use SSO, you must call this method when
    Facebook calls back into your app. This is typically done in your application delegate like so:

            - (BOOL)application:(UIApplication *)application
                        openURL:(NSURL *)url
             sourceApplication:(NSString *)sourceApplication
                    annotation:(id)annotation
           {
               // Call FBAppCall's handleOpenURL:sourceApplication to handle Facebook app responses
               BOOL wasHandled = [FBAppCall handleOpenURL:url sourceApplication:sourceApplication] &&
                                 [Kamcord handleOpenURL:url];
         
               return wasHandled;
           }
 
   @param       url         The URL that was passed to your app from the Facebook app callback.
 
 */
+ (BOOL)handleOpenURL:(NSURL *)url;

/**
 *
 * Optional method that will log Kamcord out of the shared Facebook auth. If Facebook auth
 * sharing is not enabled, this method does nothing. This method should typically be called
 * when the user logs out of Facebook (outside of Kamcord) and if you want to also nullify
 * Kamcord's shared Facebook auth. If not, then the user will still be able to share to Facebook
 * via the shared Facebook auth.
 *
 */
+ (void)logoutOfSharedFacebookAuth;

/**
 *
 * Returns whether Facebook authentication is shared between the app and Kamcord.
 *
 * @returns     The previously set Facebook shared auth.
 *
 */
+ (BOOL)facebookAuthShared;

/**
 *
 * Set the Facebook description for Facebook shares.
 *
 * @param       description     The description of the shared video.
 *
 */
+ (void)setFacebookDescription:(NSString *)description;

/**
 *
 * Returns the previously set Facebook description for shared videos.
 *
 * @returns     The previously set Facebook description for shared videos.
 *
 */
+ (NSString *)facebookDescription;

/**
 *
 * Sets the default tweet, which is used if the user doesn't enter a message when
 * they share a video.
 *
 * @param       tweet           The default tweet if the video is shared to Twitter.
 *
 */
+ (void)setDefaultTweet:(NSString *)tweet;

/**
 *
 * Returns the previously set default tweet.
 *
 * @returns     The previously set default tweet.
 *
 */
+ (NSString *)defaultTweet;

/**
 *
 * Videos that are shared to Twitter are embedded via a Twitter card.
 * You can set the description in that Twitter card with this method.
 *
 * @param       description     The Twitter card description for the shared video.
 *
 */
+ (void)setTwitterDescription:(NSString *)description;

/**
 *
 * Returns the previously set Twitter description.
 *
 * @returns     The previously set Twitter description.
 *
 */
+ (NSString *)twitterDescription;

/**
 *
 * Returns the previously set WeChat App ID.
 *
 * @returns     The previously set WeChat App ID.
 *
 */
+ (NSString *)weChatAppId;

/**
 *
 * Set the default email subject if the user shares a video via email.
 *
 * @param       subject         The default email subject.
 *
 */
+ (void)setDefaultEmailSubject:(NSString *)subject;

/**
 *
 * Returns the previously default email subject.
 *
 * @returns     The previously set default email subject.
 *
 */
+ (NSString *)defaultEmailSubject;

/**
 *
 * Set the default email body if the user shares a video via email.
 *
 * @param       body            The default email body.
 *
 */
+ (void)setDefaultEmailBody:(NSString *)body;

/**
 *
 * Returns the previously set default email body.
 *
 * @returns     The previously set default email body.
 *
 */
+ (NSString *)defaultEmailBody;

/// -------------------------------------------------------------------------
/// @name Advanced Settings
/// -------------------------------------------------------------------------

/**
 *
 * Controls the target frames-per-second of the recorded video.
 * By default, most of our games run at 60 FPS while the recorded video is at 30 FPS.
 *
 * Valid values are 15, 20, 30.
 *
 * @param       videoFPS            Set the FPS of the recorded video.
 *
 */
+ (void)setVideoFPS:(NSUInteger)videoFPS;

/**
 *
 * Returns the target recording FPS.
 *
 * @returns     The target recording FPS.
 *
 */
+ (NSUInteger)videoFPS;

/**
 *
 * If doing cross promo between your games, you can set the icon for
 * the extra cross promo watch tab.
 *
 * @param       imageName           The name of the image in the main bundle.
 *                                  If you have both retina and non-retina images
 *                                  named "crossPromoIcon.png" and "crossPromoIcon2@x.png",
 *                                  pass in @"crossPromoIcon.png" and we will automatically
 *                                  use the @2x version on retina devices.
 *
 */
+ (void)enableCrossPromotionWithImageName:(NSString *)imageName;

/**
 *
 * Should we pause/unpause the game engine when the Kamcord UI appears/disappears?
 * By default, set to true. Works for cocos2d(-x), GLKit, SpriteKit, and Unity.
 *
 * @param   shouldPause     Should we pause the game engine when the Kamcord UI appears?
 *
 */
+ (void)setShouldPauseGameEngine:(BOOL)shouldPause;

/**
 * @return The previously set value, indicating whether the game engine should be paused when the Kamcord UI appears
 */
+ (BOOL)shouldPauseGameEngine;

/// ------------------------------------------------------------------
/// @name Age Restriction
/// ------------------------------------------------------------------
/**
 *
 * Requires users to verify they are at least thirteen years old prior to allowing 
 * them to turn on voice overlay.
 *
 * @param       restricted  Require age check before allowing the user to enable voice overlay?
 */
+ (void)setAgeRestrictionEnabled:(BOOL)restricted;

/**
 *
 * Requires users to verify they are at least thirteen years old prior to allowing
 * them to turn on voice overlay.
 *
 * @param       restricted  Require age check before allowing the user to enable voice overlay?
 * @param       block       A block that will be executed when the user's age gate status is updated
 */
+ (void)setAgeRestrictionEnabled:(BOOL)restricted
          withStatusUpdatedBlock:(KCAgeGateStatusUpdatedBlock)block;

/**
 *
 * Returns a boolean indicating whether or not the user is required to be of age in order
 * to use turn on voice overlay. Reflects the above setting.
 * @warning This is now deprecated.
 * @see setAgeRestrictionEnabled:withStatusUpdatedBlock:
 */
+ (BOOL)isAgeRestrictionEnabled __deprecated;

/**
 * This will return the current status of the age gate. You may also use the optional block when setting 
 * age restriction enabled.
 *
 * @returns     The current status of the age gate for the user.
 */
+ (KCAgeGateStatus)ageGateStatus;

/// -------------------------------------------------------------------------
/// @name OpenGL Commands
/// -------------------------------------------------------------------------

/**
 *
 * Call this method to save the current state of the rendered frame out to video.
 * This is useful if you have HUD layer and would like to capture a video
 * without the HUD. You can call this method before your HUD draws and
 * Kamcord will write that pre-HUD frame to the video.
 *
 */
+ (void)captureFrame;

/**
 *
 * Returns a snapshot of the currently rendered frame. If the frame is only partially
 * rendered, this will return a snapshot of that. If you'd like to get a snapshot
 * of the next fully rendered frame, please call snapshotNextFrameWithCompletionHandler:
 *
 */
+ (UIImage *)snapshot;

/**
 *
 * Takes a snapshot of the next frame and calls back when the frame is captured.
 *
 * Returns YES if a snashot will be taken. Returns NO if you've previously called this
 * but haven't gotten a callback yet.
 *
 * @param   handler         The completion handler once the next frame's snapshot is ready.
 *                          If you passed in a non-nil destinationURL (below), the second
 *                          argument will be the local URL of the image on disk.
 * @param   destinationURL  If non-nil, the snapshot will be saved to the given local URL.
 *
 */
+ (BOOL)snapshotNextFrameWithCompletionHandler:(void(^)(UIImage * image, NSURL * imageURL))handler
                                     saveToURL:(NSURL *)destinationURL;

/// -------------------------------------------------------------------------
/// @name Deprecated methods
/// -------------------------------------------------------------------------


/*
 *
 *
 * Attach arbitrary key/value metadata to the last recorded video
 * that you can retrieve later from the Kamcord servers.
 *
 * @param       metadata        The dictionary of key-value pairs to attach to the previously recorded video.
 * @warning This is now deprecated.
 */
+ (void)setVideoMetadata:(NSDictionary *)metadata __deprecated;

/*
 *
 * Returns the previously set video metadata.
 * @warning This is now deprecated.
 */
+ (NSDictionary *)videoMetadata __deprecated;

/*
 *
 *
 * This method will query the Kamcord servers for metadata you've previously
 * associated with an uploaded video via the setVideoMetadata API call.
 * When the server request returns, the original metadata you had set
 * will be returned to you as the first argument of the block.
 * There is also NSError argument in the block that will indicate if the
 * request was successful (for example, if the connection failed due to
 * a poor internet connection). The returned NSDictionary is valid if and only if
 * the NSError object is nil.
 *
 * You can get the Kamcord Video ID to pass to this method by implementing the
 * KamcordDelegate protocol defined in Common/Core/KamcordProtocols.h.
 * Implement the videoFinishedUploadingWithSuccess:kamcordVideoID: callback
 * to get the Kamcord Video ID.
 *
 * @param       kamcordVideoID      The unique Kamcord ID for a previously shared video.
 * @param       completionHandler   A block that handles the returned metadata from the server.
 * @warning This is now deprecated.
 */
+ (void)retrieveMetadataForVideoWithID:(NSString *)kamcordVideoID
                 withCompletionHandler:(void (^)(NSMutableDictionary *, NSError *))completionHandler __deprecated;

/*
 *
 * The metadata documentation can be found here:
 *      https://github.com/kamcord/kamcord-ios-sdk/wiki/Kamcord-Settings-and-Features#general-video-metadata
 *
 * Set the level and score of the last recorded video. This information may be used
 * in the Kamcord Watch View, so we recommend that, if appropriate for your game, you
 * set it after every [Kamcord stopRecording] and before [Kamcord showView].
 * Set the level and score of the last recorded video.
 * Note: Older API, bias towards setDeveloperMetadata
 *
 * @param       level       The level of the last recorded video.
 * @param       score       The score of the last recorded video.
 *
 *
 * @see setDeveloperMetadata:displayKey:displayValue:
 * @see setDeveloperMetadata:displayKey:displayValue:numericValue:
 * @warning This is now deprecated.
 */
+ (void)setLevel:(NSString *)level
           score:(NSNumber *)score __deprecated;

/*
 *
 * This method allows you to add one background audio track to the recorded video.
 * @param filename The string path to the audio file you would like to mux with the video.
 * @warning This is now deprecated.
 */
+ (void)overlayBackgroundTrack:(NSString *)filename __deprecated;

/*
 *
 * This method allows you to add one background audio track to the recorded video.
 * @param fileURL The URL to the audio file you would like to mux with the video.
 * @warning This is now deprecated.
 */
+ (void)overlayBackgroundTrackAtURL:(NSURL *)fileURL __deprecated;

/// -------------------------------------------------------------------------
/// @name Private APIs - Do not use
/// -------------------------------------------------------------------------
+ (void)setMode:(unsigned long long)mode;
+ (void)uploadVideoToFacebookWithAccessToken:(NSString *)accessToken
                                       title:(NSString *)title
                                 description:(NSString *)description;


@end
