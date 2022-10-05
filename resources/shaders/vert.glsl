#version 330 core
layout (location = 0) in vec3 v_Pos;
layout (location = 1) in vec3 v_Color;
layout (location = 2) in vec2 v_TexCoord;

out vec3 Color;
out vec2 TexCoord;

uniform mat4 u_MVP = mat4(1.0f);
uniform float time = 0.0;

void main()
{
    gl_Position = u_MVP * vec4(v_Pos, 1.0f);
    Color = v_Color;
    TexCoord = v_TexCoord;
}