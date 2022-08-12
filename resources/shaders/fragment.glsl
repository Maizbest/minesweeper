#version 330 core
out vec4 FragColor;

in vec3 ourColor;

vec3 accentColor = vec3(0.0f, 0.0f, 0.0f); // black
uniform bool accent = false; 

void main()
{
    if (accent) {
        FragColor = vec4(accentColor, 1.0f);
    } else {
        FragColor = vec4(ourColor, 1.0f);
    };
}