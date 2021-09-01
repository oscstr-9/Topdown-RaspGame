#include "core/VectorMath.h"
#include "core/MatrixMath.h"
#include "render/ShaderResource.h"
#include <memory>

class Lighting
{
	VectorMath3 pos;
	VectorMath3 color;
	float intensity;

public:
	Lighting(VectorMath3 posIn, VectorMath3 colorIn, float intensityIn);
	~Lighting();
	void setIntensity(float intensityIn);
	void Lighting::setPos(VectorMath3 posIn);
	void Lighting::setIntensity(VectorMath3 colorIn);
	void bindLight(std::shared_ptr<ShaderResource> shader, VectorMath3 cameraPos);
};
