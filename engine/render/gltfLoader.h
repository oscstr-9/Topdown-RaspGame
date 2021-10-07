#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct gltfInfo{
    GLuint gpuBuffer;
    GLuint indexBuffer;
    int componentType;
    int posByteStride;
    int posByteLength;
    int texByteStride;
    int texByteLength;
    int normalByteStride;
    int indexCount;
};

void LoadGLTF(std::string fileName, std::vector<gltfInfo>& info);
void RenderGLTF(std::vector<gltfInfo>& info);
