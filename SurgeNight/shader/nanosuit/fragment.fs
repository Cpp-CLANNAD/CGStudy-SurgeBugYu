#version 330 core

struct TextureMaterial {
    sampler2D ambient, diffuse, specular;
    float shininess;
};

struct CustomMaterial {
    vec3 ambient, diffuse, specular;
    float shininess;
};

struct LightSpot {
    vec3 position, direction;
    float cutOff, outerCutOff;

    vec3 ambient, diffuse, specular;
    float constant, linear, quadratic;
};

struct LightNormal {
    vec4 position;
    float cutOff, outerCutOff;

    vec3 ambient, diffuse, specular;
    float constant, linear, quadratic;
};

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform LightSpot light;
uniform TextureMaterial material;

in vec3 oclr;
in vec2 otexcor;
in vec3 onor;
in vec3 oPos;
in mat4 oView;

out vec4 tclr;

vec3 calcNormalLight(LightNormal tlight, CustomMaterial tmat, vec3 normalDir, vec3 vw2ptDir, vec3 lt2ptDir, vec3 lightDir)
{
    vec3 tnnor = normalize(normalDir), tvnor = normalize(-vw2ptDir), tlpnor = normalize(-lt2ptDir), tlnor = normalize(lightDir);
    float dis = length(lt2ptDir);

    vec3 ambient = tlight.ambient * tmat.ambient;

    float diff = max(dot(tnnor, tlnor), 0.0f);
    vec3 diffuse = tlight.diffuse * diff * tmat.diffuse;

    float spec = pow(max(dot(tvnor, reflect(-tlnor, tnnor)), 0.0f), tmat.shininess);
    vec3 specular = tlight.specular * spec * tmat.specular;

    float attenuation = 1.0f;
    attenuation = 1.0 / (tlight.constant + tlight.linear * dis + tlight.quadratic * (dis * dis));

    return (ambient + diffuse + specular) * attenuation;
}

vec3 calcSpotLight(LightSpot tlight, CustomMaterial tmat, vec3 normalDir, vec3 vw2ptDir, vec3 lt2ptDir, vec3 lightDir)
{
    vec3 tnnor = normalize(normalDir), tvnor = normalize(-vw2ptDir), tlpnor = normalize(-lt2ptDir), tlnor = normalize(lightDir);
    float dis = length(lt2ptDir);

    vec3 ambient = tlight.ambient * tmat.ambient;

    float diff = max(dot(tnnor, tlnor), 0.0f);
    vec3 diffuse = tlight.diffuse * diff * tmat.diffuse;

    float spec = pow(max(dot(tvnor, reflect(-tlnor, tnnor)), 0.0f), tmat.shininess);
    vec3 specular = tlight.specular * spec * tmat.specular;

    float attenuation = 1.0f;
    attenuation = 1.0 / (tlight.constant + tlight.linear * dis + tlight.quadratic * (dis * dis));

    float theta = dot(tlpnor, -tlnor);
    float epsilon = tlight.cutOff - tlight.outerCutOff;
    float intensity = clamp((theta - tlight.outerCutOff) / epsilon, 0.0f, 1.0f);

    return (ambient + diffuse + specular) * attenuation * intensity;
}

void main()
{
    //tclr = vec4(0.6f, 0.8f, 1.0f, 0.9f);
    // tclr = vec4(oclr, 0.9f);
    // tclr = texture(utex2, otexcor) * vec4(oclr.xyz / 2.0f + 0.5f, 1.0f);
    vec3 ltDir = (oView * vec4(light.direction, 0.0f)).xyz, vwDir = -oPos, lpDir = oPos - vec3((oView * vec4(light.position, 1.0f)).xyz);

    // vec4 tmp = mix(texture(utex1, otexcor), texture(utex2, vec2(otexcor)), 0.5);
    // vec4 tmp = vec4(1.0f, 0.5f, 0.31f, 1.0f);
    CustomMaterial mat;
    mat.ambient = vec3(texture(texture_diffuse0, otexcor));
    mat.diffuse = vec3(texture(texture_diffuse0, otexcor));
    mat.specular = vec3(texture(texture_specular0, otexcor));
    mat.shininess = material.shininess;
    // tclr = texture(texture_diffuse0, otexcor);
    tclr = vec4(calcSpotLight(light, mat, onor, vwDir, lpDir, ltDir), 1.0f);// * vec4(oclr.xyz / 2.0f + 0.5f, 1.0f);
}
