#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 aModel;
layout (location = 7) in vec3 aInstanceColor;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoord;
    vec3 TexCoord3;
    vec4 FragPosLightSpace;
    vec3 InstanceColor;
} vs_out;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position = projection * view * aModel * vec4(aPos, 1.0);
    vs_out.FragPos = vec3(aModel * vec4(aPos, 1.0));
    vs_out.Normal = aNormal;
    vs_out.TexCoord = aTexCoord;
    vs_out.TexCoord3 = aPos;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
    vs_out.InstanceColor = aInstanceColor;
}
