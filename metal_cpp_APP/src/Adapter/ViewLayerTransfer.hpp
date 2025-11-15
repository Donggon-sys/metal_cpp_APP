//
//  ViewLayerTransfer.hpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/13.
//
#pragma once

#define GLFW_INCLUDE_ONCE
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

#include <Metal/Metal.hpp>
#include <Metal/Metal.h>
#include <QuartzCore/CAMetalLayer.hpp>
#include <QuartzCore/CAMetalLayer.h>
#include <QuartzCore/QuartzCore.hpp>


class ViewLayerTransfer {
private:
    CAMetalLayer *metalLayer = nullptr;
    NSWindow *nsWindow = nullptr;
public:
    void Transfer(GLFWwindow *window, CA::MetalLayer *layer);
};
