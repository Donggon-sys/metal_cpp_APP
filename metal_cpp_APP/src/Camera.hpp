//
//  Camera.hpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/22.
//

#pragma once

#include <simd/simd.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
//#include <glm/ext/scalar_constants.hpp> // glm::pi

class Camera {
private:
    
    simd_uint2 _viewport;
    simd_float3 _cameraPosition;
    simd_float3 _cameraUP;
    simd_float3 _cameraRight;
    
    void _viewMatrix();
    void _perspectiveProjectionMatrix(float fovyRadians, float nearZ, float farZ);
    
public:
    glm::mat4x4 _viewmatrix;
    glm::mat4x4 _projectionmatrix;
    
    void setAspect(const simd_uint2 &viewport);
//    void setPosition(const simd::float3 &position);
    Camera();
//    Camera(float fovyRadians, float nearZ, float farZ);
    ~Camera();
    simd_float4x4 viewProjectionMatrix(float fovyRadians, float nearZ, float farZ);
    void setPosition(float x, float y, float z);
    
};
