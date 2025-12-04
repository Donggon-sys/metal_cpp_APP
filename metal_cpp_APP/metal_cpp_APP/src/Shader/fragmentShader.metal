//
//  fragmentShader.metal
//  metal_cpp_APP
//
//  Created by Chenruyi on 2025/11/16.
//

#include <metal_stdlib>

#include "ShaderType.h"

using namespace metal;

fragment half4 fragmentShader(
                               vertexOut in [[stage_in]],
                               texture2d<half> texture[[texture(1)]]
                               ) {
                                   
                                   constexpr sampler textureSampler(mag_filter::linear, min_filter::linear);
                                
                                   const half4 out = texture.sample(textureSampler, in.texCoord);
                                   return out;
}
