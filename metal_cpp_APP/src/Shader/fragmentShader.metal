//
//  fragmentShader.metal
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/16.
//

#include <metal_stdlib>

#include "ShaderType.h"

using namespace metal;

fragment float4 fragmentShader() {
    return float4(182.0f/255.0f, 240.0f/255.0f, 228.0f/255.0f, 1.0f);
}
