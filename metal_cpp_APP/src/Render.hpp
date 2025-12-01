//
//  Render.hpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/15.
//

#pragma once
#include "Camera.hpp"
#include "Model.hpp"

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
    
   
    void createTriangleBuffer();
    void createDefaultLibrary();
    void createCommandQueue();
    void createRenderPipeLine();
    void createRenderPassDescriptor();
    void encodeRenderCommand(MTL::RenderCommandEncoder *encoder);
    void sendRenderCommand(CA::MetalDrawable *metalDrawable);
    
    Camera _camera;
    Model _sphere;
    MTL::Buffer *_pSphereBuffer;
    MTL::Buffer *_pSphereUV;
    MTL::Texture *_pTexture;
    std::vector<simd::float3> _sphereMesh;
    std::vector<simd::float2> _sphereUV;
    MTL::Buffer *_pSphereIndex;
    std::vector<unsigned int> _sphereMeshIndex;
    int _indexCount;
    
public:
    Render();
    Render(std::string modelName);
    void setMTKView(MTK::View &view);
    ~Render();
    void draw();
    void setDevice(MTL::Device *device);
    void setLayer(CA::MetalLayer *layer);
//    void init();
    void setViewPort(simd_uint2 viewport);
};
