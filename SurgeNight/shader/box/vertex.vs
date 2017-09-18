#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform vec3 viewPos;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNor;

out vec3 oclr;
out vec2 otexcor;
out vec3 onor;
out vec3 olnor;
out vec3 ovnor;

void main()
{
    // gl_Position = vec4(aPos, 1.0);
    // gl_Position = trans * vec4(aPos, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    oclr = aPos;
    otexcor = vec2(aTex.xy);
    onor = aNor;
    olnor = normalize(lightPos - vec3(model * vec4(aPos, 1.0f)));
    ovnor = normalize(viewPos - vec3(model * vec4(aPos, 1.0f)));
}
