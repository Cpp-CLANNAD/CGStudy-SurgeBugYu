#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec4 direction;

    float constant, linear, quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D utex1;
uniform sampler2D utex2;
uniform Light light;
uniform Material material;

in vec3 oclr;
in vec2 otexcor;
in vec3 onor;
in vec3 oPos;
in mat4 oView;

out vec4 tclr;

void main()
{
    //tclr = vec4(0.6f, 0.8f, 1.0f, 0.9f);
    // tclr = vec4(oclr, 0.9f);
    // tclr = texture(utex2, otexcor) * vec4(oclr.xyz / 2.0f + 0.5f, 1.0f);
    vec3 norm = normalize(onor);
    vec3 olnor, ovnor = normalize(-oPos);
    float dis = 0.0f, attenuation = 1.0f;
    if (light.direction.w != 1.0f)
        olnor = normalize(-vec3(oView * light.direction));
    else {
        olnor = normalize(vec3(oView * light.direction) - oPos);
        dis = length(vec3(oView * light.direction) - oPos);
        attenuation = 1.0 / (light.constant + light.linear * dis + light.quadratic * dis * dis);
    }

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, otexcor));

    float diff = max(dot(onor, olnor), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, otexcor));

    float spec = pow(max(dot(ovnor, reflect(-olnor, onor)), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, otexcor));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // vec4 tmp = mix(texture(utex1, otexcor), texture(utex2, vec2(otexcor)), 0.5);
    vec4 tmp = vec4(1.0f, 0.5f, 0.31f, 1.0f);
    tclr = vec4(ambient + diffuse + specular, 1.0f);// * vec4(oclr.xyz / 2.0f + 0.5f, 1.0f);
}
