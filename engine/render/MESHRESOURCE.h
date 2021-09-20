#pragma once
#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include <memory>

class Vertex;

class MeshResource
{
	GLuint vertexBuffer;
	GLuint indexBuffer;
	
public:
	int numOfIndices;
	MeshResource(Vertex vertices[], unsigned int indices[], int numOfVertices, int numOfIndicesIn);
	MeshResource(MeshResource& mesh);
	MeshResource();
	static std::shared_ptr<MeshResource> Cube(float size);
	static std::shared_ptr<MeshResource> LoadObj(std::string);
	void Render();
	void Destroy();

	~MeshResource();
};
