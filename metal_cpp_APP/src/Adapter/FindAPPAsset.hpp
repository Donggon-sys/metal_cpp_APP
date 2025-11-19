//
//  FindAPPAsset.hpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/19.
//

#pragma once

#include <string>

class FindAPPAsset {
private:
    std::string pFilePath;
    
public:
    std::string find();
    FindAPPAsset(std::string fileName);
    ~FindAPPAsset();
};
