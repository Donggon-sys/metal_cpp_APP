//
//  Model.cpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/19.
//

#include "Model.hpp"
#include "Adapter/FindAPPAsset.hpp"
#include <iostream>
#include <string>
#include <Foundation/Foundation.hpp>

Model::Model(std::string modelName) {
    std::string error;
    std::string warning;
    
    FindAPPAsset *find = new FindAPPAsset(modelName);
    
    bool rel = loader.LoadBinaryFromFile(&model, &error, &warning, find->find());
    if (!warning.empty()) {
        std::cout << warning << std::endl;
    }
    if (!error.empty()) {
        std::cout << error << std::endl;
    }
    if (!rel) {
        std::cout << "失败" << std::endl;
    }else {
        std::cout << "模型成功加载" << std::endl;
    }
}

Model::~Model() {
    
}

