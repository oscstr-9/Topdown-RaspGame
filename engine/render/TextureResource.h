#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <String>

class TextureResource
{
private:

	GLuint texture;
	std::string file;
public:
	TextureResource(std::string fileIn);
	~TextureResource();
	void bindTexture();
	void LoadFromFile(); 
};