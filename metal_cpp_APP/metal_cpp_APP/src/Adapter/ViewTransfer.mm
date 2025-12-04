//
//  ViewTransfer.mm
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/18.
//

#include "ViewTransfer.hpp"

#define GLFW_INCLUDE_ONCE
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

#include <Metal/Metal.h>
#include <MetalKit/MetalKit.h>

ViewTransfer::ViewTransfer() {
//    nsWindow = nil;
}
ViewTransfer::~ViewTransfer() {
//    nsWindow = nil;
}

MTK::View *ViewTransfer::Transfer(GLFWwindow *window) {
//        MTKView *view = (MTKView *)glfwGetCocoaView(window);
//        view.device = MTLCreateSystemDefaultDevice();
//        return ((__bridge MTK::View*)view);
    NSWindow *nsWindow = glfwGetCocoaWindow(window);
    CGRect frame = [nsWindow.contentView frame];
    MTKView *view = [[MTKView alloc] initWithFrame:frame];
    view.device = MTLCreateSystemDefaultDevice();
    view.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;
    [nsWindow.contentView addSubview:view];
    return ((__bridge MTK::View*)view);
}
