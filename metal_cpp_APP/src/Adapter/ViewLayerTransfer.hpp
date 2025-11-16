//
//  ViewLayerTransfer.hpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/13.
//
#pragma once

#include <GLFW/glfw3.h>

#include <Metal/Metal.hpp>
#include <QuartzCore/CAMetalLayer.hpp>
#include <QuartzCore/QuartzCore.hpp>

#ifdef __OBJC__
@class CAMetalLayer;
@class NSWindow;
#else
typedef struct CAMetalLayer CAMetalLayer;
typedef struct NSWindow NSWindow;
#endif


class ViewLayerTransfer {
private:
    CAMetalLayer *metalLayer;
    NSWindow *nsWindow;
public:
    ViewLayerTransfer();
    ~ViewLayerTransfer();
    void Transfer(GLFWwindow *window, CA::MetalLayer *layer);
};
