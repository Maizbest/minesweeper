#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

// uniform mat4 model = mat4(1.0f);
// uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);
uniform float time = 0.0;

void main()
{
    gl_Position = projection * vec4(aPos, 1.0f);
    
    float cosVawe = (cos(time) + 1.0f) / 2.0f;
    float sinVawe = (sin(time) + 1.0f) / 2.0f;
    ourColor = vec3(cosVawe, sinVawe, cosVawe);
}