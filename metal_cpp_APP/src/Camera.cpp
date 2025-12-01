//
//  Camera.cpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/22.
//

#include "Camera.hpp"
#include <simd/simd.h>
#include <iostream>

void Camera::_viewMatrix() {
    _viewmatrix= glm::lookAtLH(glm::vec3(5.0f, 0.0f, 0.0f),
                               glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::_perspectiveProjectionMatrix(float fovyRadians, float nearZ, float farZ) {
//    std::cout << "_viewport: " << _viewport << std::endl;
    float aspect = float(_viewport.x) / float(_viewport.y);
    _projectionmatrix = glm::perspectiveLH_ZO(fovyRadians, aspect, nearZ, farZ);
}

Camera::~Camera() {
    
}

simd_float4x4 Camera::viewProjectionMatrix(float fovyRadians, float nearZ, float farZ) {
    _viewMatrix();
    _perspectiveProjectionMatrix(fovyRadians, nearZ, farZ);
    glm::mat4x4 m = _projectionmatrix * _viewmatrix;
    return simd_matrix(
                         simd_make_float4(m[0][0], m[0][1], m[0][2], m[0][3]),
                         simd_make_float4(m[1][0], m[1][1], m[1][2], m[1][3]),
                         simd_make_float4(m[2][0], m[2][1], m[2][2], m[2][3]),
                         simd_make_float4(m[3][0], m[3][1], m[3][2], m[3][3])
                                 );
}

void Camera::setPosition(float x, float y, float z) {
    _cameraPosition = simd_make_float3(x, y, z);
}

void Camera::setAspect(const simd_uint2 &viewport) {
    _viewport = viewport;
//    std::cout << "改变了";
}

Camera::Camera(): _cameraPosition{0.0f, 0.0f, 3.0f}, _cameraUP{0.0f, 1.0f, 0.0f}, _cameraRight{0.0f, 0.0f, 0.0f} {}
