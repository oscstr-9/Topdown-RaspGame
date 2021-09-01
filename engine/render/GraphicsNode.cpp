#include "config.h"
#include "GraphicsNode.h"


GraphicsNode::GraphicsNode(std::shared_ptr <MeshResource> meshIn, std::shared_ptr <TextureResource> textureIn, std::shared_ptr <ShaderResource> shaderIn, MatrixMath transformIn)
{
	mesh = meshIn;
	texture = textureIn;
	shader = shaderIn;
	transform = transformIn;
}

GraphicsNode::~GraphicsNode()
{/*cool*/}

void GraphicsNode::Draw()
{
    texture->bindTexture();
    shader->BindShader();
    shader->setMat4(transform, "posMatrix");
    mesh->Render();
}


std::shared_ptr<MeshResource> GraphicsNode::getMesh() const
{
    return mesh;
}

void GraphicsNode::setMesh(std::shared_ptr<MeshResource> mesh)
{
    this->mesh = mesh;
}

std::shared_ptr<TextureResource> GraphicsNode::getTexture() const
{
    return texture;
}

void GraphicsNode::setTexture(std::shared_ptr<TextureResource> texture)
{
    this->texture = texture;
}

std::shared_ptr<ShaderResource> GraphicsNode::getShader() const
{
    return shader;
}

void GraphicsNode::setShader(std::shared_ptr<ShaderResource> shader)
{
    this->shader = shader;
}

MatrixMath GraphicsNode::getTransform() const
{
    return transform;
}

void GraphicsNode::setTransform(MatrixMath transform)
{
    this->transform = transform;
}

