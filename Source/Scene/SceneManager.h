#pragma once
#include <vector>
#include <functional>
#include "UsingScene.h"
#include "Common/StopWatch.h"

class SceneManager
{
public:
	using SceneGenerator = std::function<ScenePtr(void)>;
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
	/// @brief 描画処理
	void Draw(void) const;

	/// @brief シーンの変更
	void ChangeScene(void);

	ScenePtr scene_;						//シーン
	SceneGenerators sceneGenerators_;		//シーン生成用配列
	int index_;								//シーン生成用インデックス
	StopWatch stopWatch_;					//時間計測用
};
