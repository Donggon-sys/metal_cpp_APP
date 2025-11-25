//
//  Tool.hpp
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/23.
//

#include <simd/simd.h>

//SQT
namespace Tool {
simd::float4x4 translate(float x, float y, float z);
simd::float4x4 scaler(float x, float y, float z);
simd::float4x4 rotate(double angleX, double angleY, double angleZ);
}
