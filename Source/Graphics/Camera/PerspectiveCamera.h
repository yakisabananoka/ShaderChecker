#pragma once
#include "Camera.h"

/// @brief 投資投影
class PerspectiveCamera :
	public Camera
{
public:
	PerspectiveCamera();
	~PerspectiveCamera()override = default;

	/// @brief カメラの使用を設定
	void Setup(void) const override;

	/// @brief 視野角の設定
	/// @param fov 視野角(ラジアン)
	void SetFov(float fov);

	PerspectiveCamera(const PerspectiveCamera&) = delete;
	PerspectiveCamera& operator=(const PerspectiveCamera&) = delete;

	PerspectiveCamera(PerspectiveCamera&&) = default;
	PerspectiveCamera& operator=(PerspectiveCamera&&) = default;
private:
	float fov_;

};
