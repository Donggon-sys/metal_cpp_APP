//
//  ViewTransfer.hpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/18.
//

#pragma once

#include <GLFW/glfw3.h>

#include <Metal/Metal.hpp>
#include <QuartzCore/CAMetalLayer.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <MetalKit/MetalKit.hpp>

//#ifdef __OBJC__
//@class NSWindow;
//#else
//typedef struct NSWindow NSWindow;
//#endif


class ViewTransfer {
private:
//    NSWindow *nsWindow;
public:
    ViewTransfer();
    ~ViewTransfer();
    MTK::View *Transfer(GLFWwindow *window);
};
