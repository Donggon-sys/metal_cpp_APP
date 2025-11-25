//
//  Model.hpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/19.
//

#pragma once

#include <tinygltf/tiny_gltf.h>
#include <string>
#include <vector>
#include <map>
#include <simd/simd.h>

class Model {
private:
    std::map<int, std::string> _pMeshNames;
    std::map<int, std::vector<simd::float3>> _pVerices;
    std::map<int, std::vector<unsigned int>> _pIndices;
    std::map<int, std::vector<simd::float2>> _pTexCoords;
    std::map<int, std::vector<simd::float3>> _pNormals;
    
    std::string _filePath;
    
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    void _loadModel(std::string filePath);
    
public:
    Model() {};
    Model(std::string modelName);
    ~Model();
    void setMesh(std::vector<simd::float3> &mesh);
    void setMeshIndex(std::vector<unsigned int> &meshIndex);
    
};
