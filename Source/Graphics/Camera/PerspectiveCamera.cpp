#include <numbers>
#include "PerspectiveCamera.h"

constexpr float DEF_FOV = 60.0f * std::numbers::pi_v<float> / 180.0f;

PerspectiveCameraPtr PerspectiveCamera::Create(void)
{
	return PerspectiveCameraPtr(new PerspectiveCamera());
}

void PerspectiveCamera::Setup(void) const
{
	Camera::Setup();
	SetupCamera_Perspective(fov_);
}

void PerspectiveCamera::SetFov(float fov)
{
	fov_ = fov;
}

PerspectiveCamera::PerspectiveCamera() :
	fov_(DEF_FOV)
{
}
