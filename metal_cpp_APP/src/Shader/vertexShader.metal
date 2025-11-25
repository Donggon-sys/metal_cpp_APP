//
//  vertexShader.metal
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/16.
//

#include <metal_stdlib>

#include "ShaderType.h"

using namespace metal;

vertex vertexOut vertexShader(uint vertexID [[vertex_id]],
                              constant float3* vertexPositions[[buffer(0)]],
                              constant float4x4& viewProjectionMatrix[[buffer(1)]]
                              ){
                                  
    vertexOut out;
    float3 pos = vertexPositions[vertexID]; //vertexPositions这个也是指针【vertexID】类似于cpp循环中的i
    out.vertexPosition = viewProjectionMatrix * float4(pos, 1.0f);
//    out.vertexPosition = float4(pos, 1.0f);
    return out;
}
