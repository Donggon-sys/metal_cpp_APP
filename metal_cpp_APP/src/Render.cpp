//
//  Render.cpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/15.
//

#include <simd/simd.h>
#include <iostream>

#include "Render.hpp"

void Render::createTriangleBuffer() {
    simd::float3 TriangleVertices[] = {
        {-0.5f, -0.5f, 0.0f},
        { 0.5f, -0.5f, 0.0f},
        { 0.0f,  0.5f, 0.0f}
    };
    
    triangleBuffer = _pDevice->newBuffer(&TriangleVertices, sizeof(TriangleVertices), MTL::ResourceStorageModeShared);
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

void Render::createRenderPipeLine() {
    
    MTL::Function *vertexFunction = _pDefaultLibrary->newFunction(NS::String::string("vertexShader", NS::ASCIIStringEncoding));
    MTL::Function *fragmentFunction = _pDefaultLibrary->newFunction(NS::String::string("fragmentShader", NS::ASCIIStringEncoding));
    MTL::RenderPipelineDescriptor *pipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    pipelineDescriptor->setLabel(NS::String::string("Triangle render pipeline", NS::ASCIIStringEncoding));
    pipelineDescriptor->setVertexFunction(vertexFunction);
    pipelineDescriptor->setFragmentFunction(fragmentFunction);
    MTL::PixelFormat pixelFormat = _pLayer->pixelFormat();
    pipelineDescriptor->colorAttachments()->object(NS::UInteger(0))->setPixelFormat(pixelFormat);
    
    NS::Error *error;
    _pRenderPSO = _pDevice->newRenderPipelineState(pipelineDescriptor, &error);
    
    pipelineDescriptor->release();
    vertexFunction->release();
    fragmentFunction->release();
}

void Render::draw() {
    _pMetalDrawable = _pLayer->nextDrawable();
    sendRenderCommand();
}

void Render::encodeRenderCommand(MTL::RenderCommandEncoder *encoder) {
    encoder->setRenderPipelineState(_pRenderPSO);
    encoder->setVertexBuffer(triangleBuffer, 0, 0);
    
    NS::UInteger vertexStart = 0;
    NS::UInteger vertexCount = 3;
    encoder->drawPrimitives(MTL::PrimitiveTypeTriangle, vertexStart, vertexCount);
}

void Render::sendRenderCommand() {
    _pCommandBuffer = _pCommandQueue->commandBuffer();
    
    MTL::RenderPassDescriptor *renderPassDescriptor = MTL::RenderPassDescriptor::alloc()->init();
    MTL::RenderPassColorAttachmentDescriptor *cd = renderPassDescriptor->colorAttachments()->object(NS::UInteger(0));
    cd->setTexture(_pMetalDrawable->texture());
    cd->setLoadAction(MTL::LoadActionClear);
    cd->setClearColor(MTL::ClearColor(41.0f/255.0f, 42.0f/255.0f, 48.0f/255.0f, 1.0));
    cd->setStoreAction(MTL::StoreActionStore);
    
    MTL::RenderCommandEncoder *encoder = _pCommandBuffer->renderCommandEncoder(renderPassDescriptor);
    encodeRenderCommand(encoder);
    encoder->endEncoding();
    
    _pCommandBuffer->presentDrawable(_pMetalDrawable);
    _pCommandBuffer->commit();
    _pCommandBuffer->waitUntilCompleted();
    
    encoder->release();
    renderPassDescriptor->release();
}

void Render::setDevice(MTL::Device *device) {
    _pDevice = device;
}

void Render::setLayer(CA::MetalLayer *layer) {
    _pLayer = layer;
}

Render::Render() {
    
}

Render::~Render() {
    
}

void Render::init() {
    createTriangleBuffer();
    createDefaultLibrary();
    createCommandQueue();
    createRenderPipeLine();
}
