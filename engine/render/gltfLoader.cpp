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

    // Accessor normalAccessor = model.accessors[model.meshes[0].primitives[0].attributes["NORMAL"]];
    // Accessor posAccessor = model.accessors[model.meshes[0].primitives[0].attributes["POSITION"]];
    // Accessor texAccessor = model.accessors[model.meshes[0].primitives[0].attributes["TEXCOORD_0"]];

    // // normals
    // int normalByteLength = model.bufferViews[normalAccessor.bufferView].byteLength;
    // int normalByteOffset = model.bufferViews[normalAccessor.bufferView].byteOffset;
    // int normalByteStride = model.bufferViews[normalAccessor.bufferView].byteStride;
    // int normalBuffer     = model.bufferViews[normalAccessor.bufferView].buffer;


    // // positions
    // int posByteLength = model.bufferViews[posAccessor.bufferView].byteLength;
    // int posByteOffset = model.bufferViews[posAccessor.bufferView].byteOffset;
    // int posByteStride = model.bufferViews[posAccessor.bufferView].byteStride;
    // int posBuffer     = model.bufferViews[posAccessor.bufferView].buffer;


    // // texture coords
    // int texByteLength = model.bufferViews[texAccessor.bufferView].byteLength;
    // int texByteOffset = model.bufferViews[texAccessor.bufferView].byteOffset;
    // int texByteStride = model.bufferViews[texAccessor.bufferView].byteStride;
    // int texBuffer     = model.bufferViews[texAccessor.bufferView].buffer;


    // glGenBuffers(1, &posBuffer);
    // glGenBuffers(1, &normalBuffer);
    // glGenBuffers(1, &texBuffer);

    //std::cout << model.buffers[posBuffer].data.data()<< std::endl;

    // glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(int), (void*)model.buffers[posBuffer].data.data(), GL_STATIC_DRAW);

	// glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(int), (void*)model.buffers[normalBuffer].data.data(), GL_STATIC_DRAW);

    // glBindBuffer(GL_ARRAY_BUFFER, texBuffer);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(int), (void*)model.buffers[texBuffer].data.data(), GL_STATIC_DRAW);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // glEnableVertexAttribArray(0);
    // glEnableVertexAttribArray(1);
    // glEnableVertexAttribArray(2);

    // glVertexAttribPointer(0, normalByteLength, GL_FLOAT, GL_FALSE, normalByteStride, NULL);
    // glVertexAttribPointer(1, posByteLength, GL_FLOAT, GL_FALSE, posByteStride, (GLvoid*)posByteOffset);
    // glVertexAttribPointer(2, texByteLength, GL_FLOAT, GL_FALSE, texByteStride, (GLvoid*)texByteOffset);
    //glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(GLfloat) * 9));    
}