#include "config.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "TextureResource.h"


TextureResource::TextureResource(std::string fileIn)
{
	file =  "textures/" + fileIn;
}

void TextureResource::bindTexture(){
	glBindTexture(GL_TEXTURE_2D, texture);
	}

void TextureResource::LoadFromFile() {

	int width, height, channels;

	//Check if picture can be found
	unsigned char* img = stbi_load(file.c_str(), &width, &height, &channels, 0);
	if (img == NULL) {
		printf("Image loaded incorrectly %s", file);
		exit(1);
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (channels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	else if (channels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(img);
}

TextureResource::~TextureResource()
{glDeleteTextures(1,&texture);}
