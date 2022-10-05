#version 330 core

in vec3 Color;
in vec2 TexCoord;

uniform sampler2D u_Texture;

void main()
{
    gl_FragColor = mix(vec4(Color, 1.0f), texture2D(u_Texture, TexCoord), 0.7f);
}