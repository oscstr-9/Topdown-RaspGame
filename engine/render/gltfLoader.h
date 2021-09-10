#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include "tiny_gltf.h"
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace tinygltf;

void loadGLTF(Model model, std::string modelName){
    TinyGLTF loader;

    std::string err;
    std::string warn;
    bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, modelName);

    glGenBuffers(1, model.meshes[1].primitives[1]);
//    model.accessors
//    model.buffers
//    model.bufferViews
}