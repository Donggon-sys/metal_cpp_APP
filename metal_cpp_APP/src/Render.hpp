//
//  Render.hpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/15.
//

#pragma once

#include <Metal/Metal.hpp>
#include <QuartzCore/CAMetalLayer.hpp>
#include <QuartzCore/QuartzCore.hpp>

class Render {
private:
    MTL::Library *_pDefaultLibrary;
    MTL::CommandQueue *_pCommandQueue;
    MTL::CommandBuffer *_pCommandBuffer;
    MTL::RenderPipelineState *_pRenderPSO;
    MTL::Buffer *triangleBuffer;
    MTL::Device *_pDevice;
    CA::MetalLayer *_pLayer;
    CA::MetalDrawable *_pMetalDrawable;
    
    void createTriangleBuffer();
    void createDefaultLibrary();
    void createCommandQueue();
    void createRenderPipeLine();
    
    void encodeRenderCommand(MTL::RenderCommandEncoder *encoder);
    void sendRenderCommand();
    
public:
    Render();
    ~Render();
    void draw();
    void setDevice(MTL::Device *device);
    void setLayer(CA::MetalLayer *layer);
    void init();
};
