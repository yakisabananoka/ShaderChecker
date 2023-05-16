#include <numbers>
#include "PerspectiveCamera.h"

constexpr float DEF_FOV = 60.0f * std::numbers::pi_v<float> / 180.0f;

PerspectiveCamera::PerspectiveCamera() :
	fov_(DEF_FOV)
{
}

void PerspectiveCamera::Setup() const
{
	Camera::Setup();
	SetupCamera_Perspective(fov_);
}

void PerspectiveCamera::SetFov(float fov)
{
	fov_ = fov;
}
