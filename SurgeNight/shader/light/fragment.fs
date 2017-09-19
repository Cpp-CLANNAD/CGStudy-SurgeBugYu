#version 330 core

uniform vec3 clr;

out vec4 tclr;

void main()
{
    tclr = vec4(clr, 1.0f);
}
