#version 300 es
#extension GL_EXT_separate_shader_objects : require
precision highp float;

layout(location=0) in vec4 Colors;
layout(location=1) in vec2 texturesOut;
layout(location=2) in vec3 fragPos;
layout(location=3) in vec3 normalOut;

uniform sampler2D textureArray;
uniform vec3 lightColor[16];
uniform vec3 lightPos[16];
uniform float intensity[16];
uniform vec3 viewPos;
uniform float specIntensity;
uniform float amountOfLights;

out vec4 Color;

void main()
{	
	vec4 lightSources;
	for(int i = 0; i < int(amountOfLights); i++){
		vec3 viewDir = normalize(fragPos - viewPos);
		vec3 lightDir = normalize(lightPos[i] - fragPos);
		vec3 halfwayDir = normalize(lightDir + viewDir);
		vec3 ambient = intensity[i] * lightColor[i];

		vec3 to_light = lightPos[i] - fragPos;
		float d = length(to_light);
		float attenuation = clamp( intensity[i] / d, 0.0, 1.0);

		vec3 norm = normalize(normalOut);

		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColor[i];

		float spec = pow(max(dot(norm, halfwayDir), 0.0), 64.0);
		vec3 specular = lightColor[i] * spec;  

		lightSources += attenuation * vec4(ambient + diffuse + specular, 1.0);
	}
	Color =  texture(textureArray, texturesOut) * Colors * lightSources;
};
