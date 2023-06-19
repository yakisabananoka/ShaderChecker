#pragma once
#include "UsingScene.h"
#include "Graphics/UsingGraphics.h"

/// @brief シーン
class Scene
{
public:
	/// @brief デストラクタ
	virtual ~Scene();

	/// @brief 更新
	virtual void Update(void) = 0;

	/// @brief スクリーンの取得
	/// @return スクリーン
	const Screen& GetScreen(void) const;

	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	Scene(Scene&&) = delete;
	Scene& operator=(Scene&&) = delete;

protected:
	Scene();

	ScreenPtr screen_;		//スクリーン

};
