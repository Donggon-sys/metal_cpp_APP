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
#include <Metal/Metal.h>
#include <QuartzCore/CAMetalLayer.h>

void ViewLayerTransfer::Transfer(GLFWwindow *window, CA::MetalLayer *layer) {
    @autoreleasepool {
        metalLayer = (__bridge_transfer CAMetalLayer *)layer;
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
