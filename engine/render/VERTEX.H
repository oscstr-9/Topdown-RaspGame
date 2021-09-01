#ifndef VERTEX_H
#define VERTEX_H

#include "core/VectorMath.h"

struct Vertex
{
	VectorMath3 pos;
	VectorMath4 color;
	VectorMath2 textures;
	VectorMath3 normal;

	//-----------------------//
	Vertex(VectorMath3 posIn, VectorMath4 colorIn, VectorMath2 texturesIn, VectorMath3 normalIn);
};

inline Vertex::Vertex(VectorMath3 posIn, VectorMath4 colorIn, VectorMath2 texturesIn, VectorMath3 normalIn) {
	pos = posIn;
	color = colorIn;
	textures = texturesIn;
	normal = normalIn;
}
#endif // !VERTICES_H