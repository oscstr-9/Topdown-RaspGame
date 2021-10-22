#pragma once
#include <string>
#include <GL/glew.h>

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