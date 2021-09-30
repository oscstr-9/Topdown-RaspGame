#include "config.h"
#include "render/gltfLoader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "core/VectorMath.h"
#define TINYGLTF_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include "render/tiny_gltf.h"


using namespace tinygltf;

void LoadGLTF(std::string fileName, std::vector<int>& info){

    Model model;
    TinyGLTF loader;

    std::string err;
    std::string warn;
    bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, "textures/GLTFs/" + fileName + ".gltf");
    if (!ret)
    {
        std::cout << "GLTF File could not be loaded." << std::endl;
        return;
    }
    
    int numOfPrimitives = model.meshes[0].primitives.size();
    info.push_back(numOfPrimitives);

            std::cout << numOfPrimitives << std::endl;

    for (int i = 0; i < numOfPrimitives; i++)
    {
                std::cout << i << std::endl;

    Accessor normalAccessor = model.accessors[model.meshes[0].primitives[i].attributes["NORMAL"]];
    Accessor posAccessor    = model.accessors[model.meshes[0].primitives[i].attributes["POSITION"]];
    Accessor texAccessor    = model.accessors[model.meshes[0].primitives[i].attributes["TEXCOORD_0"]];

    // Normals
    int normalByteLength = model.bufferViews[normalAccessor.bufferView].byteLength;
    int normalByteOffset = model.bufferViews[normalAccessor.bufferView].byteOffset;
    int normalByteStride = model.bufferViews[normalAccessor.bufferView].byteStride;
    int normalBuffer     = model.bufferViews[normalAccessor.bufferView].buffer;


    // Positions
    int posByteLength = model.bufferViews[posAccessor.bufferView].byteLength;
    int posByteOffset = model.bufferViews[posAccessor.bufferView].byteOffset;
    int posByteStride = model.bufferViews[posAccessor.bufferView].byteStride;
    int posBuffer     = model.bufferViews[posAccessor.bufferView].buffer;


    // Texture coords
    int texByteLength = model.bufferViews[texAccessor.bufferView].byteLength;
    int texByteOffset = model.bufferViews[texAccessor.bufferView].byteOffset;
    int texByteStride = model.bufferViews[texAccessor.bufferView].byteStride;
    int texBuffer     = model.bufferViews[texAccessor.bufferView].buffer;

    // Indices
    int indicesByteLength = model.bufferViews[model.accessors[model.meshes[0].primitives[i].indices].bufferView].byteLength;
    int indicesByteOffset = model.bufferViews[model.accessors[model.meshes[0].primitives[i].indices].bufferView].byteOffset;
    int indicesByteBuffer = model.bufferViews[model.accessors[model.meshes[0].primitives[i].indices].bufferView].buffer;
    Accessor indices      = model.accessors[model.meshes[0].primitives[i].indices];
    int indexCount        = indices.count;

    // Buffers
    GLuint gpuBuffer;
    GLuint indexBuffer;

    // Bind and prepare
    glGenBuffers(1, &gpuBuffer);    
    glBindBuffer(GL_ARRAY_BUFFER, gpuBuffer);

    glGenBuffers(1, &indexBuffer);    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBufferData(GL_ARRAY_BUFFER, posByteLength+normalByteLength+texByteLength, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, posByteLength, (void*)(model.buffers[posBuffer].data.data()+posByteOffset));
	glBufferSubData(GL_ARRAY_BUFFER, posByteLength, texByteLength, (void*)(model.buffers[texBuffer].data.data()+texByteOffset));
	glBufferSubData(GL_ARRAY_BUFFER, texByteLength, normalByteLength, (void*)(model.buffers[normalBuffer].data.data()+normalByteOffset));

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteLength, (void*)(model.buffers[indicesByteBuffer].data.data()+indicesByteOffset), GL_STATIC_DRAW);


    info.push_back(posByteStride);
    info.push_back(posByteLength);
    info.push_back(texByteStride);
    info.push_back(texByteLength);
    info.push_back(normalByteStride);
    info.push_back(indexCount);
    info.push_back(gpuBuffer);
    info.push_back(indexBuffer);   
    }
}

void RenderGLTF(std::vector<int>& info){
    glBindBuffer(GL_ARRAY_BUFFER, info[6]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info[7]);

     // Render
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    
    for (int i = 0; i < info[0]; i++)
    {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, info[i*8+1], NULL);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, info[i*8+2], (GLvoid*)info[i*8+1]);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, info[i*8+4], (GLvoid*)(info[i*8+3]+info[i*8+1]));
    
    glDrawElements(GL_TRIANGLES, info[i*8+5], GL_UNSIGNED_INT, 0);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}