//
//  Camera.hpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/22.
//

#pragma once

#include <simd/simd.h>

class Camera {
private:
    float _fovyRadians;
    float _nearZ;
    float _farZ;
    simd::uint2 _viewport;
    simd::float3 _position;
    
//    simd::float4x4 _ModelMatrix;
    simd::float4x4 _ViewMatrix;
    simd::float4x4 _ProjectionMatrix;
    void _viewMatrix();
    void _perspectiveProjectionMatrix();
    
public:
    
    void setAspect(const simd::uint2 &viewport);
    void setPosition(const simd::float3 &position);
    Camera();
    Camera(float fovyRadians, float nearZ, float farZ);
    ~Camera();
    simd::float4x4 viewProjectionMatrix();
    
};
