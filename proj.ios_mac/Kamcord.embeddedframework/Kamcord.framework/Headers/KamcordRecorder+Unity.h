//
//  KamcordRecorder+Unity.h
//  Kamcord
//
//  Copyright (c) 2014 Kamcord. All rights reserved.
//

#if (KC_IS_UNITY || KAMCORD_UNITY_VERSION)

#ifndef __KAMCORDRECORDER_UNITY_H__
#define __KAMCORDRECORDER_UNITY_H__

#import "KamcordRecorder.h"
#import <CoreGraphics/CGAffineTransform.h>

@interface Kamcord

/*
 *
 * For Facebook SSO
 *
 */
+ (BOOL)handleOpenURL:(NSURL *)url;

@end

@interface KamcordRecorder()

/*
 *
 * Use this texture as our primary.
 *
 */
+ (void)usePixelBuffer:(CVPixelBufferRef)pixelBuffer
               texture:(GLint)textureId;

/*
 *
 * Set whether or not to use the new fast render. Defaults to on
 *
 */
+ (void)setUseFastRender:(BOOL)useFastRender __deprecated;

/*
 *
 * Are we using the safe render method?
 *
 */
+ (BOOL)useFastRender __deprecated;

/*
 *
 * Write the given buffer to the video.
 *
 */
+ (void)writeBufferToVideo:(void *)buffer;

/*
 *
 * Per-frame checkup.
 *
 */
+ (void)framecheck;

/*
 *
 * Apply a video transform.
 *
 */
+ (void)setVideoTransform:(CGAffineTransform)transform;

@end

#endif

#endif
