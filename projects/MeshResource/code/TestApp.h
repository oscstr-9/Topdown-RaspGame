#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2020 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include "render/MESHRESOURCE.h"
#include "render/ShaderResource.h"
#include "render/window.h"
#include "render/GraphicsNode.h"
#include <memory>

namespace Example
{
class ExampleApp : public Core::App
{
public:
	/// constructor
	ExampleApp();
	/// destructor
	~ExampleApp();
	/// open app
	bool Open();
	void ControllerInputs();
	/// run app
	void Run();
private:
	//screen size
	int width, height;

	double x;
	double y;

	float size = 1;
	float speed = 0.003;
	float deadZone = 0.2;

	float up = false;
	float down = false;
	float left = false;
	float right = false;
	float forward = false;
	float backward = false;

	MatrixMath rotMat = Identity();
	MatrixMath posMat = Identity();
	MatrixMath characterPosMat = Identity();
	VectorMath3 posVec = VectorMath3(0, 0, -5);
	std::shared_ptr<ShaderResource> shaders;
	Display::Window* window;
	GraphicsNode* sphere;
	GraphicsNode* objObject;
	GraphicsNode* cube;
};
} // namespace Example