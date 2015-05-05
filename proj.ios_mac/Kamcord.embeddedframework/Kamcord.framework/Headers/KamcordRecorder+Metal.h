//
//  KamcordRecorder+Metal.h
//  Kamcord
//
//  Created by Sam Green on 10/15/14.
//  Copyright (c) 2014 Kamcord. All rights reserved.
//

#if !TARGET_IPHONE_SIMULATOR

#import "KamcordRecorder.h"

#ifdef __arm64__
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>
#endif

@interface KamcordRecorder ()

/// ------------------------------------------------
/// @name Metal
/// ------------------------------------------------

/**
 *
 * Call once when the layer and device are created.
 *
 * @param layer The `CAMetalLayer` you will be rendering your game to.
 * @param device The `MTLDevice` that will be performing the rendering of your game.
 */
+ (void)configureLayer:(CAMetalLayer *)layer
            fromDevice:(id <MTLDevice>)device;

/**
 *
 * Call every frame once you get the new drawable.
 *
 * @param drawable A valid `CAMetalDrawable` retrieved from a `CAMetalLayer`
 */
+ (void)setCurrentDrawable:(id <CAMetalDrawable>)drawable;

/**
 *
 * Call every frame after setCurrentDrawable to record that frame.
 *
 * @param commandBuffer The command buffer that contains your Metal rendering commands
 */
+ (void)addMetalCommands:(id <MTLCommandBuffer>)commandBuffer;

@end

#endif
