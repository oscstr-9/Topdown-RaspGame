#include "RenderDebug.h"
#include "render/ShaderResource.h"
#include <GL/glew.h>

#define MAX_SIZE 8192*4

namespace Debug{
    struct Vertex{
        VectorMath3 pos;
	    VectorMath4 color;
    };
    struct debugRenderBuffer{
        unsigned int vbo = 0;
        unsigned int numOfVert = 0;
        Vertex vertex[MAX_SIZE];
        ShaderResource shader;
    };

debugRenderBuffer buffer;
inline void PushVertex(Vertex vertex){
    if (buffer.numOfVert >= MAX_SIZE)
        return;

    else{
        buffer.vertex[buffer.numOfVert] = vertex;
        buffer.numOfVert ++;
    }
}
void Render(MatrixMath projView){
    if(buffer.vbo <= 0){
        glGenBuffers(1, &buffer.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo);

        glBufferData(GL_ARRAY_BUFFER, MAX_SIZE*sizeof(Vertex), 0, GL_DYNAMIC_DRAW);

        buffer.shader.LoadShader("engine/render/DebugVertexShader.glsl","engine/render/DebugFragShader.glsl");
    }
    else{
        glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo);
    }

    glBufferSubData(GL_ARRAY_BUFFER, 0, buffer.numOfVert*sizeof(Vertex), buffer.vertex);
    buffer.shader.setMat4(projView, "projectionViewMatrix");
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)sizeof(VectorMath3));

    glDrawArrays(GL_TRIANGLES, 0, buffer.numOfVert);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    buffer.numOfVert = 0;
}
void DrawSquare(float size, VectorMath3 pos, VectorMath4 color){
    PushVertex(Vertex{pos + VectorMath3(-0.5*size, -0.5 * size, 0), color});
    PushVertex(Vertex{pos + VectorMath3(0.5*size, -0.5 * size, 0), color});
    PushVertex(Vertex{pos + VectorMath3(0.5*size, 0.5 * size, 0), color});

    PushVertex(Vertex{pos + VectorMath3(-0.5*size, -0.5 * size, 0), color});
    PushVertex(Vertex{pos + VectorMath3(-0.5*size, 0.5 * size, 0), color});
    PushVertex(Vertex{pos + VectorMath3(0.5*size, 0.5 * size, 0), color});
}

void DrawLine(VectorMath3 start, VectorMath3 end){

}
}