#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;

    float cutOff, outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant, linear, quadratic;
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
    vec3 olnor = normalize(-(oView * vec4(light.direction, 0.0f)).xyz), ovnor = normalize(-oPos), oltnor = vec3((oView * vec4(light.position, 1.0f)).xyz) - oPos;

    float dis = 0.0f;
    dis = length(oltnor);
    oltnor = normalize(oltnor);

    float theta = dot(oltnor, olnor);
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

    float attenuation = 1.0f;
    attenuation = 1.0 / (light.constant + light.linear * dis + light.quadratic * (dis * dis));

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, otexcor));

    float diff = max(dot(onor, olnor), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, otexcor));

    float spec = pow(max(dot(ovnor, reflect(-olnor, onor)), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, otexcor));

    ambient *= attenuation;
    diffuse *= attenuation;
    diffuse *= intensity;
    specular *= attenuation;
    specular *= intensity;

    // vec4 tmp = mix(texture(utex1, otexcor), texture(utex2, vec2(otexcor)), 0.5);
    vec4 tmp = vec4(1.0f, 0.5f, 0.31f, 1.0f);
    tclr = vec4(ambient + diffuse + specular, 1.0f);// * vec4(oclr.xyz / 2.0f + 0.5f, 1.0f);
}
