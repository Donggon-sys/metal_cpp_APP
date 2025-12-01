//
//  Render.cpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/15.
//

#include <simd/simd.h>
#include <iostream>
//#include "Shader/ShaderType.h"

#include "Render.hpp"

void Render::createTriangleBuffer() {
    simd::float3 TriangleVertices[] = {
        {-0.5f, -0.5f, 0.0f},
        { 0.5f, -0.5f, 0.0f},
        { 0.0f,  0.5f, 0.0f}
    };
    
    triangleBuffer = _pDevice->newBuffer(&TriangleVertices, sizeof(TriangleVertices), MTL::ResourceStorageModeShared);
    
    //TODO: sphere的
    _sphere.setMesh(_sphereMesh);
//    std::cout << "_sphereMesh.size = " << _sphereMesh.size() << std::endl;
    _pSphereBuffer = _pDevice->newBuffer(_sphereMesh.data(), _sphereMesh.size() * sizeof(simd::float3), MTL::ResourceStorageModeShared);
    
    _sphere.setMeshIndex(_sphereMeshIndex);
    _indexCount = (int)_sphereMeshIndex.size();

    _pSphereIndex = _pDevice->newBuffer(_sphereMeshIndex.data(), _sphereMeshIndex.size() * sizeof(unsigned int), MTL::ResourceStorageModeShared);
    
    _sphere.setTexCoord(_sphereUV);
    _pSphereUV = _pDevice->newBuffer(_sphereUV.data(), _sphereUV.size() * sizeof(simd::float2), MTL::ResourceStorageModeShared);
    
    MTL::TextureDescriptor *TexDescriptor = MTL::TextureDescriptor::alloc()->init();
    TexDescriptor->setPixelFormat(MTL::PixelFormatRGBA8Unorm);
    TexDescriptor->setHeight(376);
    TexDescriptor->setWidth(386);
    _pTexture = _pDevice->newTexture(TexDescriptor);
    TexDescriptor->release();
    
    std::vector<unsigned char> textureSource;
    _sphere.setImage(textureSource);
    
    //TODO: region
    MTL::Region region = MTL::Region::Make2D(0, 0, 386, 376);
    size_t bytesPerPixel = 4;
    size_t bytesPerRow = 386 * bytesPerPixel;
    
    _pTexture->replaceRegion(region, 0, 0, textureSource.data(), bytesPerRow, 0);
    
    std::cout << "_sphereUV.size : " << _sphereUV.size() << std::endl;
    std::cout << "_sphereMesh.size : " << _sphereMesh.size() << std::endl;
    std::cout << "_sphereMeshIndex.size : " << _sphereMeshIndex.size() << std::endl;
}

void Render::createDefaultLibrary() {
    _pDefaultLibrary = _pDevice->newDefaultLibrary();
    if (!_pDefaultLibrary) {
        std::cout << "加载默认library失败！" << std::endl;
        exit(-1);
    }
}

void Render::createCommandQueue() {
    _pCommandQueue = _pDevice->newCommandQueue();
}

void Render::createRenderPassDescriptor() {
    _pRenderPassDescriptor = _pView->currentRenderPassDescriptor();
}

void Render::createRenderPipeLine() {
    
    MTL::Function *vertexFunction = _pDefaultLibrary->newFunction(NS::String::string("vertexShader", NS::ASCIIStringEncoding));
    MTL::Function *fragmentFunction = _pDefaultLibrary->newFunction(NS::String::string("fragmentShader", NS::ASCIIStringEncoding));
    MTL::RenderPipelineDescriptor *pipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    
    pipelineDescriptor->setLabel(NS::String::string("Triangle render pipeline", NS::ASCIIStringEncoding));
    pipelineDescriptor->setVertexFunction(vertexFunction);
    pipelineDescriptor->setFragmentFunction(fragmentFunction);
    MTL::PixelFormat pixelFormat = _pView->colorPixelFormat();
    
    pipelineDescriptor->setRasterizationEnabled(true);
    
    
    pipelineDescriptor->colorAttachments()->object(NS::UInteger(0))->setPixelFormat(pixelFormat);
    
    //TODO: vertex Descriptor
    //attribute
    MTL::VertexDescriptor *vertexDescriptor = MTL::VertexDescriptor::alloc()->init();
    vertexDescriptor->attributes()->object(0)->setFormat(MTL::VertexFormatFloat3);
    vertexDescriptor->attributes()->object(0)->setOffset(0);
    vertexDescriptor->attributes()->object(0)->setBufferIndex(0);
    vertexDescriptor->layouts()->object(0)->setStride(sizeof(simd::float3));
    
    vertexDescriptor->attributes()->object(1)->setFormat(MTL::VertexFormatFloat2);
    vertexDescriptor->attributes()->object(1)->setOffset(0);
    vertexDescriptor->attributes()->object(1)->setBufferIndex(1);
    vertexDescriptor->layouts()->object(1)->setStride(sizeof(simd::float2));
    
    pipelineDescriptor->setVertexDescriptor(vertexDescriptor);
    
    NS::Error *error;
    _pRenderPSO = _pDevice->newRenderPipelineState(pipelineDescriptor, &error);
    
    pipelineDescriptor->release();
    vertexFunction->release();
    fragmentFunction->release();
    vertexDescriptor->release();
}

void Render::draw() {
    NS::AutoreleasePool *pool = NS::AutoreleasePool::alloc()->init();
    
    CA::MetalDrawable *metalDrawable = _pView->currentDrawable();
    if (!metalDrawable) {
        return;
    }
    sendRenderCommand(metalDrawable);
    
    pool->release();
}

void Render::encodeRenderCommand(MTL::RenderCommandEncoder *encoder) {
    encoder->setRenderPipelineState(_pRenderPSO);
    //设置顶点buffer。类似于func（para）中的para
    //TODO: 设置vertex shader Para
    //    encoder->setVertexBuffer(triangleBuffer, 0, 0);
    //TODO: 让camera工作起来
    simd_float4x4 viewProjectionMatrix = _camera.viewProjectionMatrix(65.0f * (M_PI / 180.0f), 0.1f, 100.0f);
    encoder->setVertexBytes(&viewProjectionMatrix, sizeof(viewProjectionMatrix), 11);
    
    encoder->setVertexBuffer(_pSphereBuffer, 0, 0);
    encoder->setVertexBuffer(_pSphereUV, 0, 1);
    
    //TODO: 设置fragment shader Para
    encoder->setFragmentTexture(_pTexture, 1);
    encoder->drawIndexedPrimitives(MTL::PrimitiveTypeTriangle, _indexCount, MTL::IndexTypeUInt32, _pSphereIndex, 0, 1);
//    encoder->drawPrimitives(MTL::PrimitiveTypeTriangle, 0, 3, 1);
}

void Render::sendRenderCommand(CA::MetalDrawable *metalDrawable) {
    
    MTL::CommandBuffer *commandBuffer = _pCommandQueue->commandBuffer();
    
    MTL::RenderPassColorAttachmentDescriptor *cd = _pRenderPassDescriptor->colorAttachments()->object(NS::UInteger(0));
    cd->setTexture(metalDrawable->texture());
    cd->setLoadAction(MTL::LoadActionClear);
    cd->setStoreAction(MTL::StoreActionStore);
    
    MTL::RenderCommandEncoder *encoder = commandBuffer->renderCommandEncoder(_pRenderPassDescriptor);
    encodeRenderCommand(encoder);
//    encoder->setCullMode(MTL::CullModeFront);
    encoder->endEncoding();
    
    commandBuffer->presentDrawable(metalDrawable);
    commandBuffer->commit();
    commandBuffer->waitUntilCompleted();
}

void Render::setDevice(MTL::Device *device) {
    _pDevice = device;
}

void Render::setLayer(CA::MetalLayer *layer) {
    _pLayer = layer;
}

void Render::setMTKView(MTK::View &view) {
    
    _pView = &view;
    _pDevice = view.device();
    createTriangleBuffer();
    createDefaultLibrary();
    createCommandQueue();
    createRenderPipeLine();
    createRenderPassDescriptor();
}

Render::~Render() {
}

void Render::setViewPort(simd_uint2 viewport) {
    //TODO: 以后这里主要是处理mvp矩阵变换中的投影矩阵的
    _camera.setAspect(viewport);
}

Render::Render() {
    _camera = Camera();
}

Render::Render(std::string modelName): _sphere(modelName){
}
