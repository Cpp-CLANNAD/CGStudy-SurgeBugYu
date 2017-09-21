#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec2 aTex;

out vec3 oclr;
out vec2 otexcor;
out vec3 onor;
out vec3 oPos;
out mat4 oView;

void main()
{
    // gl_Position = vec4(aPos, 1.0);
    // gl_Position = trans * vec4(aPos, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    oclr = aPos;
    otexcor = vec2(aTex.xy);
    onor = vec3((view * model * vec4(aNor, 0.0f)).xyz);
    oPos = vec3(view * model * vec4(aPos, 1.0f));
    oView = view;
}
