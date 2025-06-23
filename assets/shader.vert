#version 450
layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inUV;
layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragUV;
layout(set = 0, binding = 1) uniform MVP {
    mat4 uMVP;
};
void main() {
    gl_Position = uMVP * vec4(inPosition, 0.0, 1.0);
    fragColor = inColor;
    fragUV = inUV;
} 