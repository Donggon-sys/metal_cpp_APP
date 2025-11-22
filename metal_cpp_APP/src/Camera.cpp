//
//  Camera.cpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/22.
//

#include "Camera.hpp"
#include <simd/simd.h>
#include <iostream>

void Camera::setAspect(const simd::uint2 &viewport) {
    _viewport = viewport;
//    std::cout << " viewport 改变了" << std::endl;
}

void Camera::setPosition(const simd::float3 &position) {
    _position = position;
}

void Camera::_viewMatrix() {
    //TODO: camerDirection
    simd::float3 cameraTarget = simd::float3{0.0f, 0.0f, 0.0f};
    simd::float3 camerDirection = simd::normalize(cameraTarget - _position);
    // temp up
    simd::float3 up = simd::float3{0.0f, 1.0f, 0.0f};
    //TODO: cameraRight
    simd::float3 cameraRight = simd::normalize(simd::cross(up, camerDirection));
    //TODO: cameraUP
    simd::float3 cameraUP = simd::normalize(simd::cross(camerDirection, cameraRight));
    
    simd::float4x4 matrixLeft = {
        simd::make_float4(cameraRight     , 0.0f),
        simd::make_float4(cameraUP        , 0.0f),
        simd::make_float4(camerDirection  , 0.0f),
        simd::make_float4(0.0f, 0.0f, 0.0f, 1.0f),
    };
    simd::float4x4 matrixRight = {
        simd::make_float4(1.0f, 0.0f, 0.0f, -_position.x),
        simd::make_float4(0.0f, 1.0f, 0.0f, -_position.y),
        simd::make_float4(0.0f, 0.0f, 1.0f, -_position.z),
        simd::make_float4(0.0f, 0.0f, 0.0f,          1.0f),
    };
    
    _ViewMatrix = matrixLeft * matrixRight;
}

void Camera::_perspectiveProjectionMatrix() {
    float aspect = (float)_viewport.y / _viewport.x;
    float ys = 1 / tan(_fovyRadians * 0.5);
    float xs = ys / aspect;
    float zs = _farZ / (_nearZ - _farZ);
    
    _ProjectionMatrix = {
        simd::make_float4(xs, 0.0f, 0.0f, 0.0f),
        simd::make_float4(0.0f, ys, 0.0f, 0.0f),
        simd::make_float4(0.0f, 0.0f, zs, -zs * _nearZ),
        simd::make_float4(0.0f, 0.0f, 1.0f, 0.0f)
    };
}

Camera::Camera() {
    
}

Camera::Camera(float fovyRadians, float nearZ, float farZ) {
    _fovyRadians = fovyRadians;
    _viewport.x = 0.0f;
    _viewport.y = 0.0f;
    _nearZ = nearZ;
    _farZ = farZ;
}

Camera::~Camera() {
    
}

simd::float4x4 Camera::viewProjectionMatrix() {
    _viewMatrix();
    _perspectiveProjectionMatrix();
    
    return _ProjectionMatrix * _ViewMatrix;
}
