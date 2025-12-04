//
//  Tool.cpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/23.
//

#include "Tool.hpp"
#include <cmath>

double radian(double angle) {
    return angle * (M_PI / 180);
}

simd::float4x4 translate(float x, float y, float z) {
    return simd::float4x4 {
        simd::make_float4(1.0f, 0.0f, 0.0f,   x),
        simd::make_float4(0.0f, 1.0f, 0.0f,   y),
        simd::make_float4(0.0f, 0.0f, 1.0f,   z),
        simd::make_float4(0.0f, 0.0f, 0.0f, 1.0f)
    };
}

simd::float4x4 scaler(float x, float y, float z) {
    return simd::float4x4 {
        simd::make_float4(   x, 0.0f, 0.0f, 0.0f),
        simd::make_float4(0.0f,    y, 0.0f, 0.0f),
        simd::make_float4(0.0f, 0.0f,    z, 0.0f),
        simd::make_float4(0.0f, 0.0f, 0.0f, 1.0f)
    };
}

simd::float4x4 rotate(double angleX, double angleY, double angleZ) {
    float radianX = radian(angleX);
    float radianY = radian(angleY);
    float radianZ = radian(angleZ);
    
    simd::quatf qX = simd::quatf(radianX, simd::make_float3(1, 0, 0));
    simd::quatf qY = simd::quatf(radianY, simd::make_float3(0, 1, 0));
    simd::quatf qZ = simd::quatf(radianZ, simd::make_float3(0, 0, 1));
    simd::quatf q = simd::normalize(qZ * qY * qX);

    return simd::float4x4(q);
}
