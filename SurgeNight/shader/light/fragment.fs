#version 330 core

uniform sampler2D utex1;
uniform sampler2D utex2;
uniform vec3 clr;

out vec4 tclr;

void main()
{
    tclr = vec4(clr, 1.0f);
}
