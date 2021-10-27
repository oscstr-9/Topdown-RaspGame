#version 300 es
#extension GL_EXT_separate_shader_objects : require
precision highp float;

layout(location=0) in vec3 pos;
layout(location=1) in vec4 color;

layout(location=0) out vec4 Colors;

uniform mat4 projectionViewMatrix;

void main()
{
	gl_Position = projectionViewMatrix*vec4(pos, 1);
	Colors = color;
};
