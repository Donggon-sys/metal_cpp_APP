//
//  Model.cpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/19.
//

#include "Model.hpp"

#include <iostream>
#include <thread>
#include <string>
#include <Foundation/Foundation.hpp>
#include <vector>
#include <map>

Model::Model(std::string modelName) {
    
    std::string bundlePath = NS::Bundle::mainBundle()->resourcePath()->utf8String();
    _filePath = bundlePath + "/" + modelName;
    std::thread t(&Model::_loadModel, this, _filePath);
    t.join();
//    std::cout << "_pVerices.size = " << _pVerices.size() << std::endl;
}

void Model::_loadModel(std::string filePath) {
    
    std::string error;
    std::string warning;
    int nodeIndex = -1;
    bool rel = loader.LoadBinaryFromFile(&model, &error, &warning, _filePath);
    if (!warning.empty()) {
        std::cout << warning << std::endl;
    }
    if (!error.empty()) {
        std::cout << error << std::endl;
    }
    if (!rel) {
        std::cout << "失败" << std::endl;
    }else {
        std::cout << "模型成功加载!" << std::endl;
    }
    
    
    
    for (tinygltf::Node &node : model.nodes) {
        //TODO: 这里有旋转，平移或者缩放矩阵没有处理。因为目前并不需要，仅仅加载模型
        
        ++nodeIndex;
        for (tinygltf::Mesh &mesh : model.meshes) {
            int meshIndex = nodeIndex; //MARK: 这里有问题🤨
            //            std::cout << "mesh.name = " << mesh.name << std::endl;
            _pMeshNames.insert({meshIndex, mesh.name});
            
            for (tinygltf::Primitive &primitive : mesh.primitives) {
                //TODO: 处理vertices
                if (primitive.attributes.find("POSITION") != primitive.attributes.end()) {
                    const auto &positionAccessor = model.accessors[primitive.attributes.at("POSITION")];
                    const auto &positionBufferView = model.bufferViews[positionAccessor.bufferView];
                    const auto &positionBuffer = model.buffers[positionBufferView.buffer];
                    
                    std::vector<simd::float3>(_vertices);
                    const float *vertices = reinterpret_cast<const float *>(&positionBuffer.data[positionBufferView.byteOffset + positionAccessor.byteOffset]);
                    for (size_t i = 0; i < positionAccessor.count; ++i) {
                        const auto &p = simd::float3{vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]};
                        _vertices.push_back(p);
                    }
                    _pVerices.insert({meshIndex, _vertices});
                }
                
                //TODO: 处理texCoords
                if (primitive.attributes.find("TEXCOORD_0") != primitive.attributes.end()) {
                    const auto &texCoordAccessor = model.accessors[primitive.attributes.at("TEXCOORD_0")];
                    const auto &texCoordBufferView = model.bufferViews[texCoordAccessor.bufferView];
                    const auto &texCoordBuffer = model.buffers[texCoordBufferView.buffer];
                    
                    std::vector<simd::float2>(_texCoords);
                    const float *texCoord = reinterpret_cast<const float *>(&texCoordBuffer.data[texCoordBufferView.byteOffset + texCoordAccessor.byteOffset]);
                    for (size_t i = 0; i < texCoordAccessor.count; ++i) {
                        const auto &p = simd::float2{texCoord[i * 3], texCoord[i * 3 + 1]};
                        _texCoords.push_back(p);
                    }
                    _pTexCoords.insert({meshIndex, _texCoords});
                }
                
                //TODO: 处理normals
                if (primitive.attributes.find("NORMAL") != primitive.attributes.end()) {
                    const auto &normalAccessor = model.accessors[primitive.attributes.at("NORMAL")];
                    const auto &normalBufferView = model.bufferViews[normalAccessor.bufferView];
                    const auto &normalBuffer = model.buffers[normalBufferView.buffer];
                    
                    std::vector<simd::float3>(_normal);
                    const float *vertices = reinterpret_cast<const float *>(&normalBuffer.data[normalBufferView.byteOffset + normalAccessor.byteOffset]);
                    for (size_t i = 0; i < normalAccessor.count; ++i) {
                        const auto &p = simd::float3{vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]};
                        _normal.push_back(p);
                    }
                    _pNormals.insert({meshIndex, _normal});
                }
                
                //TODO: 处理index
                if (primitive.indices >= 0) {
                    const auto &indexAccessor = model.accessors[primitive.indices];
                    const auto &indexBufferView = model.bufferViews[indexAccessor.bufferView];
                    const auto &indexBuffer = model.buffers[indexBufferView.buffer];
                    
                    std::vector<unsigned int>(_indices);
                    if (indexAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
                        const unsigned int *indices = reinterpret_cast<const unsigned int *>(&indexBuffer.data[indexBufferView.byteOffset + indexAccessor.byteOffset]);
                        for (size_t i = 0; i < indexAccessor.count; ++i) {
                            _indices.push_back(indices[i]);
                        }
//                        std::cout << "是int" << std::endl;
                    }
                    
                    if (indexAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
                        const unsigned short *indices = reinterpret_cast<const unsigned short *>(&indexBuffer.data[indexBufferView.byteOffset + indexAccessor.byteOffset]);
                        for (size_t i = 0; i < indexAccessor.count; ++i) {
                            _indices.push_back(indices[i]);
                        }
//                        std::cout << "是short" << std::endl;
                    }
                    _pIndices.insert({meshIndex, _indices});
                }
                
                //TODO: 处理材质 - 还没有处理
            }
        }
    }
    
}

//TODO: 只处理顶点数据
void Model::setMesh(std::vector<simd::float3> &mesh) {
    
    mesh = _pVerices.at(0);
}

void Model::setMeshIndex(std::vector<unsigned int> &meshIndex) {
    
    meshIndex = _pIndices.at(0);
    
}

Model::~Model() {
    
}

