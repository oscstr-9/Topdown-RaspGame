#pragma once
#include "core/VectorMath.h"
#include "core/MatrixMath.h"

class ScreenCamera
{
private:
	VectorMath3 pos;
	MatrixMath rotMat = Identity();
	MatrixMath projectionMat;

public:
	ScreenCamera(float FOV, int width, int height, float near, float far);
	~ScreenCamera();
	void SetRotation(VectorMath3 axisIn, float radIn );
	void SetPosition(VectorMath3 posIn);
	void SetRotMat(MatrixMath rotMatIn);
	MatrixMath GetProjViewMatrix();
	VectorMath3 GetPosition();
};