#pragma once
#include <string>
#include "GL/glew.h"
#include "core/MatrixMath.h"
#include "core/VectorMath.h"
#include "render/Camera.h"

class ShaderResource
{
	GLuint program;
	MatrixMath renderPos;

public:
	ShaderResource();
	~ShaderResource();
	void LocationAndColor(MatrixMath locMat, VectorMath4 colorVec, Camera camera);
	GLuint LoadShader(const char* vertex_path, const char* fragment_path);
	void BindShader();
	void setVec3(VectorMath3 vec3, std::string uniform);
	void setVec4(VectorMath4 vec4, std::string uniform);
	void setMat4(MatrixMath mat4, std::string uniform);
	void setFloat(float floatIn, std::string uniform);
};
