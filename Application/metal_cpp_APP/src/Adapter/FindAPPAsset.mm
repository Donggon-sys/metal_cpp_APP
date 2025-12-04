//
//  FindAPPAsset.cpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/19.
//

#include "FindAPPAsset.hpp"
#include <Foundation/Foundation.h>
#include <string>

FindAPPAsset::FindAPPAsset(std::string fileName) {
    NSString *_fileName = [NSString stringWithUTF8String:fileName.c_str()];
    NSURL *url = [NSURL URLWithString:[[NSBundle mainBundle]pathForResource:_fileName ofType:nil]];
    
    std::string error;
    std::string warning;
    NSString *fileURL = [url absoluteString];
    const char *_pFileURL = [fileURL UTF8String];
    pFilePath = _pFileURL;
}

FindAPPAsset::~FindAPPAsset() {
    
}

std::string FindAPPAsset::find(){
    return pFilePath;
}
