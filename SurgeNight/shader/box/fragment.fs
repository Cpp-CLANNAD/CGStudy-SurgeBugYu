#version 330 core

uniform sampler2D utex1;
uniform sampler2D utex2;
uniform vec3 light;

in vec3 oclr;
in vec2 otexcor;
in vec3 onor;
in vec3 olnor;
in vec3 ovnor;

out vec4 tclr;

void main()
{
    //tclr = vec4(0.6f, 0.8f, 1.0f, 0.9f);
    // tclr = vec4(oclr, 0.9f);
    // tclr = texture(utex2, otexcor) * vec4(oclr.xyz / 2.0f + 0.5f, 1.0f);
    vec3 norm = normalize(onor);

    vec4 ambient = 0.1f * vec4(light, 1.0f);

    float diff = max(dot(onor, olnor), 0.0f);
    vec4 diffuse = vec4(diff * light, 0.0f);

    float specular = 0.5f;
    diff = pow(max(dot(reflect(-olnor, onor), ovnor), 0.0f), 32);
    vec4 fl = vec4(diff * specular * light, 0.0f);

    // vec4 tmp = mix(texture(utex1, otexcor), texture(utex2, vec2(otexcor)), 0.5);
    vec4 tmp = vec4(0.6f, 0.8f, 1.0f, 0.9f);
    tclr = (ambient + diffuse + fl) * tmp;// * vec4(oclr.xyz / 2.0f + 0.5f, 1.0f);
}
