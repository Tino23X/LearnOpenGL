#version 330 core
out vec4 fragColor;
in vec4 vectorColor;
uniform vec4 outColor;
void main()
{
    fragColor = vectorColor;
}