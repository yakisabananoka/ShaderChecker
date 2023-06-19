#pragma once
#include <vector>
#include <functional>
#include "UsingScene.h"

class SceneManager
{
public:
	using SceneGenerator = std::function<ScenePtr()>;
	using SceneGenerators = std::vector<SceneGenerator>;

	SceneManager();
	~SceneManager();

	/// @brief 更新
	void Update(void);

	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;

private:
	void Draw(void) const;

	void ChangeScene(void);

	ScenePtr scene_;						//シーン
	SceneGenerators sceneGenerators_;		//シーン生成用配列
	int index_;								//シーン生成用インデックス
};
