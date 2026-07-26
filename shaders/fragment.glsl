#version 330 core

#define MAX_LIGHTS  16


in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoord;
    vec3 TexCoord3;
    vec4 FragPosLightSpace;
    vec3 InstanceColor;
} fs_in;

out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    int type;       // 0 - directional, 1 - point

    vec3 vector;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // Used to calculate attenuation for point lights
    float constant;
    float linear;
    float quadratic;
};

uniform vec3 viewPos;

uniform Material material;
uniform Light directionalLight;
uniform Light pointLights[MAX_LIGHTS];
uniform int numberPointLights;

uniform bool useTexture2D;
uniform bool useTextureCube;
uniform bool useInstanceColor;

uniform sampler2D objectTexture;
uniform samplerCube objectTextureCube;
uniform sampler2D depthTexture;

uniform bool enableShadows;


float CalculateShadow(vec3 normal, vec3 lightDir)
{
    // Perspective divide
    vec3 projectedCoords = fs_in.FragPosLightSpace.xyz / fs_in.FragPosLightSpace.w;
    // Transform to [0, 1] range
    projectedCoords = projectedCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective
    // float closestDepth = texture(depthTexture, projectedCoords.xy).r;
    // Get current depth value of fragment from light's perspective
    float currentDepth = projectedCoords.z;

    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005); 

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(depthTexture, 0);
    for (int x = -1; x <= 1; x++)
    {
        for (int y =-1; y <= 1; y++)
        {
            float pcfDepth = texture(depthTexture, projectedCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }

    // Check whether fragment is in shadow
    return shadow / 9.0;
}

vec3 CalculateLighting(Light light, vec3 lightDir, float attenuation)
{
    vec3 color = vec3(1.0);

    if (useTexture2D)
    {
        color = vec3(texture(objectTexture, fs_in.TexCoord));
    }
    else if (useTextureCube)
    {
        color = vec3(texture(objectTextureCube, fs_in.TexCoord3));
    }

    vec3 ambientColor = useInstanceColor ? fs_in.InstanceColor : material.ambient;
    vec3 diffuseColor = useInstanceColor ? fs_in.InstanceColor : material.diffuse;

    // ambient
    vec3 ambient = light.ambient * ambientColor * attenuation;

    // diffuse
    vec3 norm = normalize(fs_in.Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse =  light.diffuse * diff * diffuseColor * attenuation;

    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 halwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(viewDir, halwayDir), 0.0), material.shininess);
    if (diff == 0)
    {
        spec = 0;
    }
    vec3 specular = light.specular * material.specular * spec * attenuation;

    float shadow = 0.0;
    if (enableShadows)
    {
        shadow = CalculateShadow(norm, lightDir);
    }
    return (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
}

vec3 CalculateDirectionalLight(Light light)
{
    return CalculateLighting(light, normalize(-light.vector), 1.0);
}

vec3 CalculatePointLight(Light light)
{
    vec3 lightDir = normalize(light.vector - fs_in.FragPos);
    float distance = length(light.vector - fs_in.FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    return CalculateLighting(light, lightDir, attenuation);
}

void main()
{
    vec3 color = CalculateDirectionalLight(directionalLight);

    for (int i = 0; i < numberPointLights; i++)
    {
        color += CalculatePointLight(pointLights[i]);
    }

    FragColor = vec4(color, 1.0);
}
    