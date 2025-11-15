//
//  ViewLayerTransfer.mm
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/13.
//

#import "ViewLayerTransfer.hpp"

void ViewLayerTransfer::Transfer(GLFWwindow *window, CA::MetalLayer *layer) {
    @autoreleasepool {
        metalLayer = (__bridge_transfer CAMetalLayer *)layer;
        nsWindow = glfwGetCocoaWindow(window);
        nsWindow.contentView.layer = metalLayer;
        nsWindow.contentView.wantsLayer = YES;
    }
}
