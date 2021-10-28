#pragma once
#include "core/VectorMath.h"
#include "core/MatrixMath.h"
#include "render/Vertex.h"

namespace Debug{
void Render(MatrixMath projView);
void DrawSquare(float size, VectorMath3 pos, VectorMath4 color);
void DrawLine(VectorMath3 start, VectorMath3 end, VectorMath4 color);
}