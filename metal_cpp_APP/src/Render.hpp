//
//  Render.hpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/15.
//

#pragma once
#include "Camera.hpp"

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>
#include <QuartzCore/CAMetalLayer.hpp>
#include <QuartzCore/QuartzCore.hpp>

class Render {
private:
    MTK::View *_pView;
    MTL::Library *_pDefaultLibrary;
    MTL::CommandQueue *_pCommandQueue;
    MTL::RenderPipelineState *_pRenderPSO;
    MTL::Buffer *triangleBuffer;
    MTL::Device *_pDevice;
    CA::MetalLayer *_pLayer;
    MTL::RenderPassDescriptor *_pRenderPassDescriptor;
    
    Camera _camera;
    
    void createTriangleBuffer();
    void createDefaultLibrary();
    void createCommandQueue();
    void createRenderPipeLine();
    void createRenderPassDescriptor();
    void encodeRenderCommand(MTL::RenderCommandEncoder *encoder);
    void sendRenderCommand(CA::MetalDrawable *metalDrawable);
    
public:
    Render();
    void setMTKView(MTK::View &view);
    ~Render();
    void draw();
    void setDevice(MTL::Device *device);
    void setLayer(CA::MetalLayer *layer);
//    void init();
    void setViewPort(simd::uint2 viewport);
};
