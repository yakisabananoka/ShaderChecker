#include "Camera.h"

Camera::Camera() :
	near_(50.0f), far_(1000.0f), pos_({ 0.0f, 0.0f, -100.0f }), target_({ 0.0f,0.0f,0.0f })
{
}

void Camera::Setup(void) const
{
	SetCameraNearFar(near_, far_);
	SetCameraPositionAndTarget_UpVecY(pos_, target_);
}

void Camera::SetNearFar(float nearDis, float farDis)
{
	near_ = nearDis;
	far_ = farDis;
}

void Camera::SetPosition(const VECTOR& pos)
{
	pos_ = pos;
}

void Camera::SetTarget(const VECTOR& target)
{
	target_ = target;
}
