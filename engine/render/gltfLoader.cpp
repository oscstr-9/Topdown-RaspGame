#include "config.h"
#include "render/gltfLoader.h"
#include "core/VectorMath.h"
#define TINYGLTF_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include "render/tiny_gltf.h"


using namespace tinygltf;

void LoadGLTF(std::string fileName, std::vector<gltfInfo>& info){

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
    
    int numOfMeshes = model.meshes.size();

    for (int i = 0; i < numOfMeshes; i++)
    {
        int numOfPrimitives = model.meshes[i].primitives.size();

        for (int j = 0; j < numOfPrimitives; j++)
        {
            
            // Buffers
            GLuint gpuBuffer;
            GLuint indexBuffer;

            // Bind and prepare buffers
            glGenBuffers(1, &gpuBuffer);    
            glBindBuffer(GL_ARRAY_BUFFER, gpuBuffer);

            glGenBuffers(1, &indexBuffer);    
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

            // Accessors
            Accessor normalAccessor = model.accessors[model.meshes[i].primitives[j].attributes["NORMAL"]];
            Accessor posAccessor    = model.accessors[model.meshes[i].primitives[j].attributes["POSITION"]];
            Accessor texAccessor    = model.accessors[model.meshes[i].primitives[j].attributes["TEXCOORD_0"]];

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
            Accessor indices      = model.accessors[model.meshes[i].primitives[j].indices];
            int indicesByteLength = model.bufferViews[indices.bufferView].byteLength;
            int indicesByteOffset = model.bufferViews[indices.bufferView].byteOffset;
            int indicesByteBuffer = model.bufferViews[indices.bufferView].buffer;
            int indexCount        = indices.count;

            // Texture
            Image texImg = model.images[model.materials[0].pbrMetallicRoughness.baseColorTexture.index];
            int height;
            int width;
            int comp;
            unsigned char* img = stbi_load_from_memory(model.buffers[model.bufferViews[texImg.bufferView].buffer].data.data(), texByteLength, &height, &width, &comp, texImg.component);
            
            // Bind texture to gpu with syntax below, example in textureResource. add texture gluint to GLTFinfo struct for easy access in render function.


            glGenTextures(1, &info.texture);
            glBindTexture(GL_TEXTURE_2D, info.texture);
	        glBufferData(GL_ARRAY_BUFFER, posByteLength+normalByteLength+texByteLength, NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, posByteLength, (void*)(model.buffers[posBuffer].data.data()+posByteOffset+posAccessor.byteOffset));
	        glBufferSubData(GL_ARRAY_BUFFER, posByteLength, texByteLength, (void*)(model.buffers[texBuffer].data.data()+texByteOffset+texAccessor.byteOffset));
	        glBufferSubData(GL_ARRAY_BUFFER, posByteLength+texByteLength, normalByteLength, (void*)(model.buffers[normalBuffer].data.data()+normalByteOffset+normalAccessor.byteOffset));

	        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteLength, (void*)(model.buffers[indicesByteBuffer].data.data()+indicesByteOffset+indices.byteOffset), GL_STATIC_DRAW);


            info.push_back(gltfInfo{
                           gpuBuffer, 
                           indexBuffer,
                           model.accessors[model.meshes[i].primitives[j].indices].componentType,
                           posByteStride,
                           posByteLength,
                           texByteStride,
                           texByteLength,
                           normalByteStride,
                           indexCount});
            
        }
    }
} 

void RenderGLTF(std::vector<gltfInfo>& info){
    

    // Itterates through all meshes and all primitives in each mesh to render the model
    for(int i =0; i < info.size(); i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER, info[i].gpuBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info[i].indexBuffer);

        // Render
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, info[i].posByteStride, NULL);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, info[i].texByteStride, (GLvoid*)info[i].posByteLength);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, info[i].normalByteStride, (GLvoid*)(info[i].posByteLength+info[i].texByteLength));
        
        glDrawElements(GL_TRIANGLES, info[i].indexCount, info[i].componentType, 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}