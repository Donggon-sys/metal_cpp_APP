//
//  Window.mm
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/15.
//

#include "Window.hpp"
#include "Adapter/ViewLayerTransfer.hpp"

void Window::init() {
    initDevice();
    initWindow();
}
void Window::run() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void Window::release() {
    glfwTerminate();
    device->release();
}

void Window::initDevice() {
    device = MTL::CreateSystemDefaultDevice();
}
void Window::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(800, 600, "window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    layer = CA::MetalLayer::layer();
    layer->setDevice(device);
    layer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
    ViewLayerTransfer Transfer;
    Transfer.Transfer(window, layer);
}
