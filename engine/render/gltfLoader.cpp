#include "config.h"
#include "render/gltfLoader.h"
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core/VectorMath.h"
#define TINYGLTF_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include "render/tiny_gltf.h"


using namespace tinygltf;

void loadGLTF(std::string fileName){

    Model model;
    TinyGLTF loader;

    std::string err;
    std::string warn;
    bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, "textures/GLTFs/" + fileName + ".gltf");

    Accessor normalAccessor = model.accessors[model.meshes[0].primitives[0].attributes["NORMAL"]];
    Accessor posAccessor = model.accessors[model.meshes[0].primitives[0].attributes["POSITION"]];
    Accessor texAccessor = model.accessors[model.meshes[0].primitives[0].attributes["TEXCOORD_0"]];

    // normals
    int normalByteLength = model.bufferViews[normalAccessor.bufferView].byteLength;
    int normalByteOffset = model.bufferViews[normalAccessor.bufferView].byteOffset;
    int normalByteStride = model.bufferViews[normalAccessor.bufferView].byteStride;
    int normalBuffer     = model.bufferViews[normalAccessor.bufferView].buffer;


    // positions
    int posByteLength = model.bufferViews[posAccessor.bufferView].byteLength;
    int posByteOffset = model.bufferViews[posAccessor.bufferView].byteOffset;
    int posByteStride = model.bufferViews[posAccessor.bufferView].byteStride;
    int posBuffer     = model.bufferViews[posAccessor.bufferView].buffer;


    // texture coords
    int texByteLength = model.bufferViews[texAccessor.bufferView].byteLength;
    int texByteOffset = model.bufferViews[texAccessor.bufferView].byteOffset;
    int texByteStride = model.bufferViews[texAccessor.bufferView].byteStride;
    int texBuffer     = model.bufferViews[texAccessor.bufferView].buffer;

    int indicesByteBuffer = model.bufferViews[model.accessors[model.meshes[0].primitives[0].indices].bufferView].buffer;
    int indicesByteOffset = model.bufferViews[model.accessors[model.meshes[0].primitives[0].indices].bufferView].byteOffset;
    int indexCount        = model.accessors[model.meshes[0].primitives[0].indices].count;

    // Buffers
    GLuint gpuBuffer;
    GLuint indexBuffer;

    // Bind and prepare
    glGenBuffers(1, &gpuBuffer);    
    glBindBuffer(GL_ARRAY_BUFFER, gpuBuffer);

    glGenBuffers(1, &indexBuffer);    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBufferData(GL_ARRAY_BUFFER, posByteLength+normalByteLength+texByteLength, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, posByteLength, (void*)model.buffers[posBuffer].data.data()+posByteOffset);
	glBufferSubData(GL_ARRAY_BUFFER, posByteLength, texByteLength, (void*)model.buffers[texBuffer].data.data()+texByteOffset);
	glBufferSubData(GL_ARRAY_BUFFER, texByteLength, normalByteLength, (void*)model.buffers[normalBuffer].data.data()+normalByteOffset);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, model.buffers[indicesByteBuffer].data.data()+indicesByteOffset, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Render
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, posByteStride, NULL);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, texByteStride, (GLvoid*)texByteOffset);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, normalByteStride, (GLvoid*)texByteOffset);

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}