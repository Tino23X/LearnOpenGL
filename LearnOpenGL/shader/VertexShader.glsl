#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float outPosx;
out vec4 vectorColor;
void main()
{
    //aPos = vec3(aPos.x - outPosx, aPos.yz);
    gl_Position = vec4(aPos.x - outPosx, aPos.y, aPos.z, 1.0);
    vectorColor = vec4(aColor, 1.0);
}