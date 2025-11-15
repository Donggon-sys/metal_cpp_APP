//
//  Window.hpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/15.
//
#pragma once
#include <GLFW/glfw3.h>

#include <Metal/Metal.hpp>
#include <QuartzCore/CAMetalLayer.hpp>
#include <QuartzCore/QuartzCore.hpp>
class Window {
public:
    void init();
    void run();
    void release();
    
private:
    void initDevice();
    void initWindow();
    GLFWwindow *window;
    MTL::Device *device;
    CA::MetalLayer *layer;
};

