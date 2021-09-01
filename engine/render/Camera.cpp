#include "config.h"
#include "Camera.h"

Camera::Camera(float FOV, int width, int height, float near, float far)
{
	pos = VectorMath3(0,0,0);
	projectionMat = MatrixMath::ProjectionMatrix(FOV, (float)width / (float)height, near, far);
}

void Camera::SetRotation(VectorMath3 axisIn, float radIn) {
	rotMat = RotateMatrix(radIn, axisIn);
}

void Camera::SetPosition(VectorMath3 posIn) {
	pos = posIn;
}

void Camera::SetRotMat(MatrixMath rotMatIn) {
	rotMat = rotMatIn;
}

MatrixMath Camera::GetProjViewMatrix() {
	return  projectionMat * rotMat * MatrixMath::TranslationMatrix(pos);
}

VectorMath3 Camera::GetPosition() {
	return pos;
}

Camera::~Camera()
{
}