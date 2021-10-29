#include "config.h"
#include "Camera.h"

ScreenCamera::ScreenCamera(float FOV, int width, int height, float near, float far)
{
	pos = VectorMath3(0,0,0);
	projectionMat = MatrixMath::ProjectionMatrix(FOV, (float)width / (float)height, near, far);
}

void ScreenCamera::SetRotation(VectorMath3 axisIn, float radIn) {
	rotMat = RotateMatrix(radIn, axisIn);
}

void ScreenCamera::SetPosition(VectorMath3 posIn) {
	pos = posIn;
}

void ScreenCamera::SetRotMat(MatrixMath rotMatIn) {
	rotMat = rotMatIn;
}

MatrixMath ScreenCamera::GetProjViewMatrix() {
	return  projectionMat * rotMat * MatrixMath::TranslationMatrix(-pos);
}

VectorMath3 ScreenCamera::GetPosition() {
	return pos;
}

ScreenCamera::~ScreenCamera()
{
}