//
//  ShaderType.h
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/16.
//

#ifndef ShaderType_h
#define ShaderType_h

#include <simd/simd.h>
//#include <metal_stdlib>

typedef struct {
    float3 vertexPosition [[attribute(0)]];
    float2 texCoord       [[attribute(1)]];
} vertexIn;

typedef struct {
    float4 vertexPosition [[position]];
    float2 texCoord;
} vertexOut;



#endif /* ShaderType_h */
