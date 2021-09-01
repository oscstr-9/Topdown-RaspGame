#include "config.h"
#include "Lighting.h"
#include "ShaderResource.h"

Lighting::Lighting(VectorMath3 posIn, VectorMath3 colorIn, float intensityIn)
{
	pos = posIn;
	color = colorIn;
	intensity = intensityIn;
}

Lighting::~Lighting()
{
}

void Lighting::setIntensity(float intensityIn) {
	intensity = intensityIn;
}

void Lighting::setPos(VectorMath3 posIn) {
	pos = posIn;
}

void Lighting::setIntensity(VectorMath3 colorIn) {
	color = colorIn;
}

// Sets all values required for lighting to work in the shader
void Lighting::bindLight(std::shared_ptr<ShaderResource> shader, VectorMath3 cameraPos) {

	shader->setVec3(color, "lightColor");
	shader->setVec3(pos, "lightPos");
	shader->setFloat(intensity, "intensity");

	shader->setVec3(cameraPos, "viewPos");
	shader->setFloat(1, "specIntensity");
}
