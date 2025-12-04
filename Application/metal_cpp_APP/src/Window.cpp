//
//  Window.mm
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/15.
//

#include "Window.hpp"
#include "Render.hpp"
#include "Adapter/ViewTransfer.hpp"
#include <iostream>

void Window::framebufferResizeCallback(GLFWwindow *window, int width, int height) {
    Window *self = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (self) {
        self->frameSizeChange(width, height);
    }
}

void Window::frameSizeChange(int width, int height) {
    viewport.x = width;
    viewport.y = height;
    render.setViewPort(viewport);
}

Window::Window() {
    render = Render("sphere2.glb");
    int width; int height;
    
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(853, 533, "window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, Window::framebufferResizeCallback);
    glfwGetFramebufferSize(window, &width, &height);
    frameSizeChange(width, height);
    
    ViewTransfer transfer;
    MTK::View *view = transfer.Transfer(window);
    render.setMTKView(*view);
}

Window::~Window() {
    
}

void Window::run() {
    while (!glfwWindowShouldClose(window)) {
        //TODO: 以后在里面使用 -> [render->draw(_pView)]
        render.draw();
        glfwPollEvents();
    }
}

void Window::release() {
    glfwTerminate();
}
