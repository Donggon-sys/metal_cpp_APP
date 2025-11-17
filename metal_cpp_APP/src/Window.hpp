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

#include "Render.hpp"


class Window {
    
private:

    GLFWwindow *window;
    Render *render;
    
public:
    void init();
    void run();
    void release();
    
};

