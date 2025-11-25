//
//  Window.hpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/15.
//
#pragma once
#include <GLFW/glfw3.h>

#include <simd/simd.h>

#include <Metal/Metal.hpp>
#include <QuartzCore/CAMetalLayer.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <MetalKit/MetalKit.hpp>

#include "Render.hpp"


class Window {
    
private:
    simd_uint2 viewport;
    GLFWwindow *window;
    Render render;
    static void framebufferResizeCallback(GLFWwindow *window, int width, int height);
    void frameSizeChange(int width, int height);
    
public:
    Window();
    ~Window();
    void run();
    void release();
    
};

