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
    initDevice();
    initWindow();
    
    render->setDevice(_pDevice);
    render->setLayer(_pLayer);
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
    _pDevice->release();
}

void Window::initDevice() {
    _pDevice = MTL::CreateSystemDefaultDevice();
}
void Window::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(800, 600, "window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    _pLayer = CA::MetalLayer::layer();
    _pLayer->setDevice(_pDevice);
    _pLayer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
    ViewLayerTransfer Transfer;
    Transfer.Transfer(window, _pLayer);
}
