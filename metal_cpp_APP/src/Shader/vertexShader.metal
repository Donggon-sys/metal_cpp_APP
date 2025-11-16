//
//  vertexShader.metal
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/16.
//

#include <metal_stdlib>

#include "ShaderType.h"

using namespace metal;

vertex vertexOut
vertexShader(uint vertexID [[vertex_id]],
             constant float3* vertexPositions)
{
    vertexOut out;
    out.vertexPosition = float4(vertexPositions[vertexID][0],
                                       vertexPositions[vertexID][1],
                                       vertexPositions[vertexID][2],
                                       1.0f);
    return out;
}
