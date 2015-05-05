
#ifndef __KAMCORD_C_INTERFACE_H__
#define __KAMCORD_C_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif

#if __ANDROID__

#include <stdbool.h>
#include <jni.h>

typedef enum KC_VIDEO_QUALITY
{
    KC_STANDARD_VIDEO_QUALITY = 0,
    KC_TRAILER_VIDEO_QUALITY = 1,  // Trailers only. Do not release your game with this setting.
} KC_VIDEO_QUALITY;

typedef enum KC_METADATA_TYPE
{
    KC_LEVEL = 0,
    KC_SCORE = 1,
    KC_LIST = 2,
    KC_OTHER = 1000
} KC_METADATA_TYPE;

typedef enum KC_SHARE_TARGET
{
    KC_SHARE_BLANK = -1,
    KC_SHARE_FACEBOOK = 0,
    KC_SHARE_TWITTER = 1,
    KC_SHARE_YOUTUBE = 2,
    KC_SHARE_EMAIL = 3,
    KC_SHARE_LINE = 5
} KC_SHARE_TARGET;

/*
 *
 * Kamcord initialization. Must be called before you can start recording.
 *
 * @param   developerKey            Your Kamcord developer key.
 * @param   developerSecret         Your Kamcord developerSecret.
 * @param   appName                 The name of your application.
 * @param   KC_VIDEO_QUALITY        The quality level.  Please use
 *                                  KC_STANDARD_VIDEO_QUALITY in production.
 *
 */
void Kamcord_Init(
    const char* developerKey,
    const char* developerSecret,
    const char* appName,
    KC_VIDEO_QUALITY videoQuality);

void Kamcord_InitJVM(JavaVM* vm);

void Kamcord_InitActivity(jobject activity);

/*
 * Sets a flag that overrides the internal device whitelist for testing.
 * DEPRECATED.  Use WhitelistAll() instead.
 */
void Kamcord_WhitelistAllBoards();

/*
 * Clears the device whitelist.
 * DEPRECATED.  Use BlacklistAll() instead.
 */
void Kamcord_BlacklistAllBoards();

/*
 * Sets a flag that overrides the internal whitelist for testing.
 */
void Kamcord_WhitelistAll();

/*
 * Clears the whitelist.
 */
void Kamcord_BlacklistAll();

/*
 * Adds a specific board (hardware configuration) to the whitelist.
 * Takes the same sort of board name that is returned by Kamcord_GetBoard()
 *
 * @param  boardName      Name of the board to add.
 */
void Kamcord_WhitelistBoard(const char* boardName);

/*
 * Removes a specific board (hardware configuration) from the whitelist.
 * Takes the same sort of board name that is returned by Kamcord_GetBoard()
 *
 * @param  boardName      Name of the board to remove.
 */
void Kamcord_BlacklistBoard(const char* boardName);

/*
 * Adds a specific device (hardware configuration) to the whitelist.
 * Takes the same sort of device name that is returned by Kamcord_GetDevice()
 *
 * @param  deviceName      Name of the device to add.
 */
void Kamcord_WhitelistDevice(const char* deviceName);

/*
 * Removes a specific device (hardware configuration) from the whitelist.
 * Takes the same sort of device name that is returned by Kamcord_GetDevice()
 *
 * @param  deviceName      Name of the device to remove.
 */
void Kamcord_BlacklistDevice(const char* deviceName);

/**
 * Adds a specific board (hardware configuration) to the whitelist.
 * Takes the same sort of board name that is returned by Kamcord_GetBoard()
 *
 * @param  boardName      Name of the board to add.
 * @param  sdkVersion     API level of Android.
 */
void Kamcord_WhitelistBoardOnSDK(const char* boardName, int sdkVersion);

/**
 * Removes a specific board (hardware configuration) from the whitelist.
 * Takes the same sort of board name that is returned by Kamcord_GetBoard()
 *
 * @param  boardName      Name of the board to remove.
 * @param  sdkVersion     API level of Android.
 */
void Kamcord_BlacklistBoardOnSDK(const char* boardName, int sdkVersion);

/**
 * Adds a specific device (hardware configuration) to the whitelist.
 * Takes the same sort of device name that is returned by Kamcord_GetDevice()
 *
 * @param  deviceName     Name of the device to add.
 * @param  sdkVersion     API level of Android.
 */
void Kamcord_WhitelistDeviceOnSDK(const char* deviceName, int sdkVersion);

/**
 * Removes a specific device (hardware configuration) from the whitelist.
 * Takes the same sort of device name that is returned by Kamcord_GetDevice()
 *
 * @param  deviceName     Name of the device to remove.
 * @param  sdkVersion     API level of Android.
 */
void Kamcord_BlacklistDeviceOnSDK(const char* deviceName, int sdkVersion);

/*
 * Gets the current board name.  Equivalent to the java: Build.BOARD
 */
const char* Kamcord_GetBoard();

/*
 * Gets the current device name.  Equivalent to the java: Build.DEVICE
 */
const char* Kamcord_GetDevice();

/*
 * Gets a version string from kamcord.jar.
 */
const char* Kamcord_Version();

/*
 *
 * Returns true if and only if Kamcord is enabled. Kamcord is disabled if the version of
 * android is < 4.1, or if the device's device name does not appear on the whitelist.
 *
 */
bool Kamcord_IsEnabled();

/*
 * Returns true if the current device is whitelisted. A device which is whitelisted still may not
 * be enabled for recording if the hardware or operating system does not support recording.
 */
bool Kamcord_IsWhitelisted();

/*
 * Returns the reason that Kamcord is disabled if Kamcord_IsEnabled() is false
 */
const char* Kamcord_GetDisabledReason();

/*
 *
 * Start video recording.
 *
 */
void Kamcord_StartRecording();

/*
 *
 * Stop video recording.
 *
 */
void Kamcord_StopRecording();

/*
 *
 * Pause video recording.
 *
 */
void Kamcord_Pause();

/*
 *
 * Resume video recording.
 *
 */
void Kamcord_Resume();

/*
 *
 * Returns true if the video is recording. Note that there might be a slight
 * delay after you call Kamcord_StartRecording() before this method returns true.
 *
 */
bool Kamcord_IsRecording();

/*
 *
 * Returns true if video recording is currently paused.
 *
 */
bool Kamcord_IsPaused();

/*
 *
 * Enable or disable the live voice overlay.
 *
 * @param   enabled             Whether to enable or disable the live voiced overlay feature.
 *                              By default, this is disabled.
 *
 */
void Kamcord_SetVoiceOverlayEnabled(bool enabled);

/*
 *
 * Returns true if live voice overlay has been enabled.
 *
 */
bool Kamcord_VoiceOverlayEnabled();

/*
 *
 * Call this function to force the OpenGL framebuffers Kamcord uses to capture frames of
 * video to allocate.  If you omit this call, they will allocate automatically just in
 * time.
 *
 * @param  width    The width of the framebuffer's renderbuffer.
 * @param  height   The height of the framebuffer's renderbuffer.
 *
 */
void Kamcord_CreateFramebuffers(int width, int height);

/*
 *
 * Call this function to explicitly delete the OpenGL framebuffers Kamcord uses to
 * capture frames of video to allocate.
 *
 */
void Kamcord_DeleteFramebuffers();

/*
 *
 * Surround OpenGL calls that draw graphics which are meant to be captured to video with
 * BeginDraw() and EndDraw().
 *
 */
void Kamcord_BeginDraw();

/*
 *
 * Surround OpenGL calls that draw graphics which are meant to be captured to video with
 * Kamcord_BeginDraw() and Kamcord_EndDraw().
 *
 */
void Kamcord_EndDraw();

/*
 *
 * After every video is recorded (i.e. after you call StopRecording()), you should
 * call this method to set the title for the video in case it is shared.
 *
 * We suggest you set the title to contain some game-specific information such as
 * the level, score, and other relevant game metrics.
 *
 * @param  title   The title of the last recorded video.
 *
 */
void Kamcord_SetVideoTitle(const char* title);

/*
 *
 * Set the level and score for the recorded video.
 * This metadata is used to rank videos in the watch view.
 *
 * @param   level   The level for the last recorded video.
 * @param   score   The score the user just achieved on the given level.
 *
 */
void Kamcord_SetLevelAndScore(
    const char* level,
    double score);

/*
 *
 * Set a key/value pair for the metadata attached to the current video.
 *
 * @param   metadataType            The type of value for the metadata.
 * @param   key                     The key for the metadata.
 * @param   value                   The value for the metadata.
 *
 */
void Kamcord_SetDeveloperMetadata(
    KC_METADATA_TYPE metadataType,
    const char* key,
    const char* value);

/*
 *
 * Set a key/value pair for the metadata attached to the current video.
 *
 * @param   metadataType            The type of value for the metadata.
 * @param   key                     The key for the metadata.
 * @param   value                   The value for the metadata.
 * @param   numericValue            The numeric value for the metadata, used for sorting.
 *
 */
void Kamcord_SetDeveloperMetadataWithNumericValueDouble(
    KC_METADATA_TYPE metadataType,
    const char* key,
    const char* value,
    double numericValue);

/*
 *
 * Set a key/value pair for the metadata attached to the current video.
 *
 * @param   metadataType            The type of value for the metadata.
 * @param   key                     The key for the metadata.
 * @param   value                   The value for the metadata.
 * @param   numericValue            The numeric value for the metadata, used for sorting.
 *
 */
void Kamcord_SetDeveloperMetadataWithNumericValueFloat(
    KC_METADATA_TYPE metadataType,
    const char* key,
    const char* value,
    float numericValue);

/*
 *
 * Set a key/value pair for the metadata attached to the current video.
 *
 * @param   metadataType            The type of value for the metadata.
 * @param   key                     The key for the metadata.
 * @param   value                   The value for the metadata.
 * @param   numericValue            The numeric value for the metadata, used for sorting.
 *
 */
void Kamcord_SetDeveloperMetadataWithNumericValueInt(
    KC_METADATA_TYPE metadataType,
    const char* key,
    const char* value,
    int numericValue);

/*
 *
 * Show the Kamcord view, which will let the user share the most
 * recently recorded video.
 *
 */
void Kamcord_ShowView();

/*
 *
 * Show the watch view, which has a feed of videos shared by other users.
 *
 */
void Kamcord_ShowWatchView();

/*
 *
 * Set the description for when the user shares to Facebook.
 *
 * @param   description     Your app's description when a user shares a video on Facebook.
 *
 */
void Kamcord_SetFacebookDescription(
    const char* description);

/*
 *
 * Set the video description and tags for YouTube.
 *
 * @param   description     The video's description when it's shared on YouTube.
 * @param   tags            The video's tags when it's shared on YouTube.
 *
 */
void Kamcord_SetYouTubeSettings(
    const char* description,
    const char * tags);

/*
 *
 * Set the default tweet.
 *
 * @param   tweet           The default tweet.
 *
 */
void Kamcord_SetDefaultTweet(
    const char* tweet);

/*
 *
 * Set the default tweet.
 *
 * @param   tweet           The default tweet.
 *
 */
void Kamcord_SetTwitterDescription(
    const char* twitterDescription);

/*
 *
 * Set the default email subject.
 *
 * @param   subject         The default subject if the user shares via email.
 *
 */
void Kamcord_SetDefaultEmailSubject(
    const char* subject);

/*
 *
 * Set the default email body.
 *
 * @param   body            The default email body if the user shares via email.
 *
 */
void Kamcord_SetDefaultEmailBody(
    const char* body);

/*
 *
 * Set the sharing options of the Kamcord UI. There MUST be exactly four unique options.
 * The order of the array affects the order in which the share options appear on the UI.
 *
 * @param   target          The array of share targets which will be displayed.
 *
 */
void Kamcord_SetShareTargets(
    KC_SHARE_TARGET targets[]);

/*
 *
 * Sets the use of FMOD for audio recording
 *
 * @param   usingFmod       Whether to use FMOD
 * @param   sampleRate		The sample rate of the audio
 *
 */
void Kamcord_SetUsingFmod(
    bool usingFmod,
    int sampleRate);

/**
 * Sets the "app rendering" framebuffer (usually the screen) that content is being rendered to
 * in between calls to begin/end draw.
 * Use this method if the application is rendering to some other frame buffer besides the screen
 * at the end of every frame.
 * Requires Kamcord to be enabled and Kamcord initialization to have finished to complete
 * successfully.
 * 
 * @param framebufferID The OpenGL ID of the app rendering framebuffer.
 *
 * @return true if the setting of the framebuffer was successful, false otherwise.
 */
bool Kamcord_SetAppRenderingFramebuffer(int framebufferID);

/**
 * Sets the currently bound framebuffer to be the "app rendering" framebuffer
 * 
 * @return true if the setting of the framebuffer was successful, false otherwise.
 */
bool Kamcord_SetCurrentlyBoundFramebufferToBeAppRenderingFramebuffer();

#endif // __ANDROID__

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ifndef

