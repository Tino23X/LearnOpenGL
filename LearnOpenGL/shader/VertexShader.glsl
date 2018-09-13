#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aTexCoord;

uniform float outPosx;
out vec4 vectorColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos.x - outPosx, aPos.yz, 1.0);
    vectorColor = vec4(aColor, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}