#pragma once
#include <string>
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

	/// @brief シーン名の取得
	/// @return シーン名
	const std::string& GetName(void) const;

	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	Scene(Scene&&) = delete;
	Scene& operator=(Scene&&) = delete;

protected:
	Scene(const std::string& name);

	ScreenPtr screen_;			//スクリーン
	std::string name_;			//シーン名

};
