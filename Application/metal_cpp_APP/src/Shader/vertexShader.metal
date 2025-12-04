//
//  vertexShader.metal
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/16.
//

#include <metal_stdlib>

#include "ShaderType.h"

using namespace metal;

vertex vertexOut vertexShader(vertexIn in [[stage_in]],
                              constant float4x4& viewProjectionMatrix[[buffer(11)]]
                              ){
                                  
    vertexOut out;
    
    out.vertexPosition = viewProjectionMatrix * float4(in.vertexPosition, 1.0f);
    out.texCoord = in.texCoord;
    
//    out.texCoord.y = 1.0f - out.texCoord.y;
//    out.texCoord.x = 1.0f - out.texCoord.x;
//    
    return out;
}
