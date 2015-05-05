//
//  KamcordRecorder.h
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <QuartzCore/QuartzCore.h>

/** 
 * This class is responsible for all the behind the scenes work required to actually get graphics from your game
 * in to a Kamcord video.
 */
@interface KamcordRecorder : NSObject

typedef NS_ENUM(NSUInteger, KamcordBufferType)
{
    // The default buffer type, should be sufficient in majority of cases.
    KamcordBufferTypeDefault,

    // Use double buffering technique to save GPU time at the expense of CPU time and GPU memory.
    // May improve performance in some scenarios.
    KamcordBufferTypeDouble,

    // Use a double buffering technique with GPU down sampling, might prevent some dropped video frames at the expense of more GPU memory.
    // May improve performance in some scenarios.
    KamcordBufferTypeDoubleWithHardwareDownSampling,

    // Use triple buffering technique to save some GPU time and prevent some dropped video frames but has high GPU memory usage.
    KamcordBufferTypeTriple,
    
    // Use triple buffering technique with GPU down sampling, might prevent some dropped video frames at the expense of more GPU memory.
    KamcordBufferTypeTripleWithHardwareDownSampling
};


/// ------------------------------------------
/// @name OpenGL
/// ------------------------------------------

/**
 *
 * OpenGL setup. Should be called once before any OpenGL rendering
 * is done.
 */
+ (BOOL)initWithEAGLContext:(EAGLContext *)context
                      layer:(CAEAGLLayer *)layer;

/**
 * OpenGL setup. Should be called once before any OpenGL rendering
 * is done and specifying the buffering type used for recording.
 * Each buffering type has different benefits and trade offs.
 * Returns YES if the KamcordRecorder was initialized properly, NO otherwise.
 */
+ (BOOL)initWithEAGLContext:(EAGLContext *)context
                      layer:(CAEAGLLayer *)layer
                 bufferType:(KamcordBufferType)bufferType;

/**
 *
 * OpenGL setup. Should be called once before any OpenGL rendering
 * is done.
 */
+ (BOOL)initWithEAGLContext:(EAGLContext *)context
                      layer:(CAEAGLLayer *)layer
                   rotation:(int)degrees;

/**
 * OpenGL setup. Should be called once before any OpenGL rendering
 * is done. Specifies the rotation of the recorded video as
 * well as and specifying the buffering type used for recording.
 * Each buffering type has different benefits and trade offs.
 * Returns YES if the KamcordRecorder was initialized properly, NO otherwise.
 */
+ (BOOL)initWithEAGLContext:(EAGLContext *)context
                      layer:(CAEAGLLayer *)layer
                   rotation:(int)degrees
                 bufferType:(KamcordBufferType)bufferType;

/**
 *
 * Call this method to create framebuffers if you *don't* use MSAA.
 *
 */
+ (BOOL)createFramebuffers:(GLuint)defaultFramebuffer;

/**
 *
 * Call this method to create framebuffers if you *do* use MSAA.
 *
 */
+ (BOOL)createFramebuffers:(GLuint)defaultFramebuffer
           msaaFramebuffer:(GLuint)msaaFramebuffer;

/**
 *
 * Call this method to create framebuffers *without* MSAA.
 * The resulting video will be cropped to the given boundaries.
 *
 */
+ (BOOL)createFramebuffers:(GLuint)defaultFramebuffer
                boundaries:(CGRect)boundaries;

/**
 *
 * Call this method to create framebuffers *with* MSAA.
 * The resulting video will be cropped to the given boundaries.
 *
 */
+ (BOOL)createFramebuffers:(GLuint)defaultFramebuffer
           msaaFramebuffer:(GLuint)msaaFramebuffer
                boundaries:(CGRect)boundaries;

/**
 *
 * Call this method to create framebuffers where the size of the screen
 * isn't equal to the size of the primary buffer. For the target size,
 * pass in the desired size of the primary buffer.
 *
 */
+ (BOOL)createFramebuffers:(GLuint)defaultFramebuffer
           msaaFramebuffer:(GLuint)msaaFramebuffer
               primarySize:(CGSize)primarySize;

/**
 *
 * Call this alongside any code you have that deletes your framebuffers.
 *
 */
+ (void)deleteFramebuffers;


/**
 *
 * Call every render loop before `[context presentRenderbuffer:GL_RENDERBUFFER]`.
 * Pass the OpenGL framebuffer to which the renderbuffer you are presenting
 * is attached.  
 *
 * @return `NO` on a failure, or if Kamcord is disabled.
 */
+ (BOOL)beforePresentRenderbuffer:(GLuint)framebuffer;

/**
 *
 * Call every render loop before `[context presentRenderbuffer:GL_RENDERBUFFER]`.
 *
 * @return `NO` on a failure, or if Kamcord is disabled.
 */
+ (BOOL)beforePresentRenderbuffer;

/**
 *
 * Call every render loop after `[context presentRenderbuffer:GL_RENDERBUFFER]`.
 *
 */
+ (BOOL)afterPresentRenderbuffer;

/**
 *
 * Call to capture a frame of video before the call to `beforePresentRenderbuffer`.
 * For instance if the game has a HUD, call captureFrame before drawing the HUD;
 * the HUD will not appear in the final video.
 *
 */
+ (BOOL)captureFrame;

/**
 *
 * Anywhere in your OpenGL code where you would normally bind your defaultFramebuffer
 * for rendering, instead bind `[KamcordRecorder activeFramebuffer]`.
 *
 */
+ (GLuint)activeFramebuffer;

/*
 * @warning This has been deprecated in v1.6.1
 * @see activeFramebuffer
 */
+ (GLuint)kamcordFramebuffer __deprecated;

/// -------------------------------------
/// @name Snapshots
/// -------------------------------------

/**
 *
 * Takes a snapshot of the current screen and returns an UIImage.
 *
 */
+ (UIImage *)snapshot;

/**
 *
 * Takes a snapshot of the next frame and calls back when the frame is captured.
 *
 * Returns `YES` if a snapshot will be taken. Returns `NO` if you've previously called this
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

/// -----------------------------------
/// @name Utility
/// -----------------------------------

/**
 *
 * Set the target video FPS. The default value is 30 FPS.
 *
 * @param fps The target FPS for a recorded video. Valid values are 30 or 60. Typically only newer devices can handle 60 FPS.
 *
 */
+ (void)setTargetVideoFPS:(NSUInteger)fps;

/**
 * @return The target video FPS previously set. Defaults to 30 FPS.
 */
+ (NSUInteger)targetVideoFPS;

/**
 *
 * @return Whether the current frame is recording or not.
 *
 */
+ (BOOL)isRecording;

/**
 *
 * Sets the parent view controller. Identical to calling `[Kamcord setParentViewController:...]`;
 *
 */
+ (void)setParentViewController:(UIViewController *)parentViewController;

@end
