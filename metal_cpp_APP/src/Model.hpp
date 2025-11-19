//
//  Model.hpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/19.
//

#pragma once

#include <tinygltf/tiny_gltf.h>
#include <string>
//#include <Foundation/Foundation.hpp>

class Model {
private:
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
//    void loaderModelWithName(std::string modelName);
    
public:
    Model(std::string modelName);
    ~Model();
    
};
