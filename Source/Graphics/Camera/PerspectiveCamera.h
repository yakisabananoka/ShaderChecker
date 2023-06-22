#pragma once
#include "Camera.h"
#include "Graphics/UsingGraphics.h"

/// @brief 透視投影
class PerspectiveCamera :
	public Camera
{
public:
	/// @brief 生成関数
	/// @return カメラ
	static PerspectiveCameraPtr Create(void);

	~PerspectiveCamera()override = default;

	/// @brief カメラの使用を設定
	void Setup(void) const override;

	/// @brief 視野角の設定
	/// @param fov 視野角(ラジアン)
	void SetFov(float fov);

	PerspectiveCamera(const PerspectiveCamera&) = default;
	PerspectiveCamera& operator=(const PerspectiveCamera&) = default;

	PerspectiveCamera(PerspectiveCamera&&) = default;
	PerspectiveCamera& operator=(PerspectiveCamera&&) = default;

protected:
	PerspectiveCamera();

private:
	float fov_;

};
