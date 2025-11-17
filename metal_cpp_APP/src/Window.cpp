//
//  Window.mm
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/15.
//

#include "Window.hpp"
#include "Render.hpp"
#include "Adapter/ViewLayerTransfer.hpp"

void Window::init() {
    render = new Render();
    
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(2560, 1600, "window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    MTL::Device *device = MTL::CreateSystemDefaultDevice();
    CA::MetalLayer *layer = CA::MetalLayer::layer();
    layer->setDevice(device);
    layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
    ViewLayerTransfer Transfer;
    Transfer.Transfer(window, layer);
    
    render->setDevice(device);
    render->setLayer(layer);
    render->init();
    
}


void Window::run() {
    while (!glfwWindowShouldClose(window)) {
        
        render->draw();
        glfwPollEvents();
    }
}

void Window::release() {
    glfwTerminate();
}
