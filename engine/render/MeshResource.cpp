#include "config.h"
#include "MESHRESOURCE.h"
#include "TextureResource.h"
#include <vector>
#include <string.h>

MeshResource::MeshResource(Vertex vertices[], unsigned int indices[], int numOfVertices, int numOfIndicesIn) {
	numOfIndices = numOfIndicesIn;

	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numOfVertices, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numOfIndices, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

MeshResource::MeshResource(MeshResource& mesh) {
	this->vertexBuffer = mesh.vertexBuffer;
	this->indexBuffer = mesh.indexBuffer;
	this->numOfIndices = mesh.numOfIndices;
}

void MeshResource::Render() {
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(GLfloat) * 3));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(GLfloat) * 7));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(GLfloat) * 9));

		glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

std::shared_ptr<MeshResource> MeshResource::Cube(float size) {

	// Vertex configuration: Vertex(Pos(x,y,z), color(x,y,z,w), texture(x,y), normals(x,y,z));

						  //Front (red)
	Vertex vertices[] = { Vertex(VectorMath3(-size / 2,-size / 2,size / 2),VectorMath4(1,0,0,1),VectorMath2(1.f/3.f,0), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(size/2,-size/2,size/2), VectorMath4(1,0,0,1),VectorMath2(2.f/3.f,0), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(size/2,size/2,size/2), VectorMath4(1,0,0,1),VectorMath2(2.f/3.f,1), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(-size/2,size/2,size/2), VectorMath4(1,0,0,1),VectorMath2(1.f/3.f,1), VectorMath3(0,0,0)),

						  //Back (green)
						  Vertex(VectorMath3(-size/2,-size/2,-size/2),VectorMath4(0,1,0,1),VectorMath2(0,0), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(size/2,-size/2,-size/2), VectorMath4(0,1,0,1),VectorMath2(1.f/3.f,0), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(size/2,size/2,-size/2), VectorMath4(0,1,0,1),VectorMath2(1.f / 3.f,1), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(-size/2,size/2,-size/2), VectorMath4(0,1,0,1),VectorMath2(0,1), VectorMath3(0,0,0)),
		
						  //Left (blue)
						  Vertex(VectorMath3(-size/2,-size/2,-size/2),VectorMath4(0,0,1,1),VectorMath2(0,0), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(-size/2,-size/2,size/2), VectorMath4(0,0,1,1),VectorMath2(1.f / 3.f,0), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(-size/2,size/2,size/2), VectorMath4(0,0,1,1),VectorMath2(1.f / 3.f,1), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(-size/2,size/2,-size/2), VectorMath4(0,0,1,1),VectorMath2(0,1), VectorMath3(0,0,0)),

						  //Right (Purple)
						  Vertex(VectorMath3(size/2,-size/2,-size/2),VectorMath4(1,0,1,1),VectorMath2(0,0), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(size/2,-size/2,size/2), VectorMath4(1,0,1,1),VectorMath2(1.f / 3.f,0), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(size/2,size/2,size/2), VectorMath4(1,0,1,1),VectorMath2(1.f / 3.f,1), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(size/2,size/2,-size/2), VectorMath4(1,0,1,1),VectorMath2(0,1), VectorMath3(0,0,0)),

						  //Top (Yellow)
						  Vertex(VectorMath3(-size/2,size/2,size/2),VectorMath4(1,1,0,1),VectorMath2(2.f / 3.f,0), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(size/2,size/2,size/2), VectorMath4(1,1,0,1),VectorMath2(1,0), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(size/2,size/2,-size/2), VectorMath4(1,1,0,1),VectorMath2(1,1), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(-size/2,size/2,-size/2), VectorMath4(1,1,0,1),VectorMath2(2.f/3.f,1), VectorMath3(0,0,0)),

						  //Bottom (Cyan)
						  Vertex(VectorMath3(size/2,-size/2,size/2),VectorMath4(0,1,1,1),VectorMath2(2.f/3.f,0), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(-size/2,-size/2,size/2), VectorMath4(0,1,1,1),VectorMath2(1,0), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(-size/2,-size/2,-size/2), VectorMath4(0,1,1,1),VectorMath2(1,1), VectorMath3(0,0,0)),
						  Vertex(VectorMath3(size/2,-size/2,-size/2), VectorMath4(0,1,1,1),VectorMath2(2.f/3.f,1), VectorMath3(0,0,0))
};

	unsigned int indices[] = { 3,0,1,1,2,3,			//Front
							   7,4,5,5,6,7,			//Back
							   11,8,9,9,10,11,		//Left
							   15,12,13,13,14,15,	//Right
							   19,16,17,17,18,19,	//Top
							   23,20,21,21,22,23	//Bottom
	};

	return std::make_shared<MeshResource>(vertices, indices, sizeof(vertices)/sizeof(Vertex), sizeof(indices) / sizeof(unsigned int));
}

std::shared_ptr<MeshResource> MeshResource::LoadObj(std::string fileName)
{
	FILE* myfile = fopen(("textures/OBJs/" + fileName + ".obj").c_str(), "r");
	std::vector<VectorMath3> vC; // Vertex Coords
	std::vector<VectorMath2> vT; // Vertex Textures
	std::vector<VectorMath3> vN; // Vertex normals
	std::vector<Vertex> vertices; // Combined verices
	int numOfVertices = 0;

	// Vertex Indices
	std::vector<unsigned int> indices;

	char buf[256];
	bool indexCheck = true;
	bool scanning = true;

	// If file is found
	if (myfile != NULL)
	{
		while (scanning) {
			// If it should scan or not
			if (indexCheck) { 
				// If end of file is reached
				if ((fscanf(myfile, "%256s", buf) <= 0)) {
					break;
				}
			}

			// Vertex Coords
			if (buf[0] == 'v' && buf[1] == '\0') {
				float x, y, z;
				if (fscanf(myfile, "%f %f %f", &x, &y, &z) == 3) {
					vC.push_back(VectorMath3(x, y, z));
				}
				else { std::cout << "Vertex coords broken" << std::endl; }
			}

		// Vertex Textures
			else if (buf[0] == 'v' && buf[1] == 't' && buf[2] == '\0') {
				float x, y;
				if (fscanf(myfile, "%f %f", &x, &y) == 2) {
					vT.push_back(VectorMath2(x, 1 - y));
				}
				else { std::cout << "Vertex texture coords broken" << std::endl; }
			}

		// Vertex Normals
			else if (buf[0] == 'v' && buf[1] == 'n' && buf[2] == '\0') {
				float x, y, z;
				if (fscanf(myfile, "%f %f %f", &x, &y, &z) == 3) {
					vN.push_back(VectorMath3(x, y, z));
				}
				else { std::cout << "Vertex normal coords broken" << std::endl; }
			}

		// Vertices
			else if (buf[0] == 'f' && buf[1] == '\0') {
				indexCheck = true;
				char x[64], y[64], z[64], w[64];
				int reads = 0;

				reads = fscanf(myfile, "%s %s %s %s", &x, &y, &z, &w);

				// Find and add vertices depending on indices
				int indexList[4][3];
				sscanf(x, "%d/ %d/ %d/", &indexList[0][0], &indexList[0][1], &indexList[0][2]);
				sscanf(y, "%d/ %d/ %d/", &indexList[1][0], &indexList[1][1], &indexList[1][2]);
				sscanf(z, "%d/ %d/ %d/", &indexList[2][0], &indexList[2][1], &indexList[2][2]);

				//		           Vertex(VectorMath3(pos),	      VectorMath4(color),  VectorMath2(Textures),  VectorMath3(normal))
				vertices.push_back(Vertex(vC[(indexList[0][0]) - 1], VectorMath4(1, 1, 1, 1), vT[(indexList[0][1]) - 1], vN[(indexList[0][2]) - 1]));
				vertices.push_back(Vertex(vC[(indexList[1][0]) - 1], VectorMath4(1, 1, 1, 1), vT[(indexList[1][1]) - 1], vN[(indexList[1][2]) - 1]));
				vertices.push_back(Vertex(vC[(indexList[2][0]) - 1], VectorMath4(1, 1, 1, 1), vT[(indexList[2][1]) - 1], vN[(indexList[2][2]) - 1]));

				indices.push_back(numOfVertices);
				indices.push_back(numOfVertices + 1);
				indices.push_back(numOfVertices + 2);

				numOfVertices += 3;
				
				if (reads == 3) {
					break;
				}
				// Triangulate quad
				else if (w[0] != 'f' && w[0] != '#') {

					sscanf(w, "%d/ %d/ %d/", &indexList[3][0], &indexList[3][1], &indexList[3][2]);

					vertices.push_back(Vertex(vC[(indexList[3][0]) - 1], VectorMath4(1, 1, 1, 1), vT[(indexList[3][1]) - 1], vN[(indexList[3][2]) - 1]));

					indices.push_back(numOfVertices - 3);
					indices.push_back(numOfVertices - 1);
					indices.push_back(numOfVertices);

					numOfVertices += 1;
				}
				// if accidentally read too long
				else if(w[0] == 'f'){
					buf[0] = 'f', buf[1] == '\0';
					indexCheck = false;
				}
			}
		}
		fclose(myfile);

		return std::make_shared<MeshResource>(&vertices[0], &indices[0], vertices.size(), indices.size());
	}
	else { std::cout << "Unable to open file"; }
	return NULL;
}

void MeshResource::Destroy() {
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

MeshResource::~MeshResource() {
	Destroy();
}