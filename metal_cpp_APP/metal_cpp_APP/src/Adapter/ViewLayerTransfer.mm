//
//  ViewLayerTransfer.mm
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/13.
//

#define GLFW_INCLUDE_ONCE
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

#import "ViewLayerTransfer.hpp"
#include <MetalKit/MetalKit.h>
//#include <MetalKit/MetalKit.hpp>
#include <Metal/Metal.h>
#include <QuartzCore/CAMetalLayer.h>

void ViewLayerTransfer::Transfer(GLFWwindow *window, CA::MetalLayer *layer) {
    @autoreleasepool {
        metalLayer = ((__bridge CAMetalLayer *)layer);
        [metalLayer setDisplaySyncEnabled:true];
        [metalLayer setFramebufferOnly:true];
        nsWindow = glfwGetCocoaWindow(window);
        nsWindow.contentView.layer = metalLayer;
        nsWindow.contentView.wantsLayer = YES;
    }
}

ViewLayerTransfer::ViewLayerTransfer() {
    metalLayer = nil;
    nsWindow = nil;
}
ViewLayerTransfer::~ViewLayerTransfer() {
    metalLayer = nil;
    nsWindow = nil;
}

MTK::View *ViewLayerTransfer::Transfer(GLFWwindow *window) {
    @autoreleasepool {
        MTKView *view = (MTKView *)glfwGetCocoaView(window);
        return ((__bridge MTK::View*)view);
    }
}
