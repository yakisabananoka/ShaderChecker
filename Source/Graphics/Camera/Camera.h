#pragma once
#include <DxLib.h>

/// @brief カメラ
class Camera
{
public:
	Camera();
	virtual ~Camera() = default;

	/// @brief カメラの使用を設定
	virtual void Setup(void) const;

	/// @brief 手前クリップ距離と奥クリップ距離の設定
	/// @param nearDis 手前クリップ距離(0より大きく)
	/// @param farDis 奥クリップ距離
	void SetNearFar(float nearDis, float farDis);

	/// @brief 位置の設定
	/// @param pos 位置
	void SetPosition(const VECTOR& pos);

	/// @brief ターゲットの設定
	/// @param target ターゲットの位置
	void SetTarget(const VECTOR& target);

	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	Camera(Camera&&) = default;
	Camera& operator=(Camera&&) = default;

private:
	float near_;		//手前クリップ距離
	float far_;			//奥クリップ距離

	VECTOR pos_;		//位置
	VECTOR target_;		//ターゲットの位置

};
