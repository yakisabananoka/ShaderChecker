#include "SceneManager.h"
#include "Scene.h"
#include "Graphics/Drawable/Screen.h"
#include "Scene/Deriverd/2D/ImageScene.h"
#include "Scene/Deriverd/2D/ConstantBufferScene.h"
#include "Scene/Deriverd/2D/MultiRenderTargetScene.h"
#include "Scene/Deriverd/3D/ModelFor1FrameScene.h"

SceneManager::SceneManager() :
	index_(0)
{
	sceneGenerators_.emplace_back(std::bind(ImageScene::Create, "Assets/Image/texture0.png", "Assets/ShaderBinary/Pixel/ImagePixelShader.pso"));
	sceneGenerators_.emplace_back(std::bind(ImageScene::Create, "Assets/Image/texture0.png", "Assets/ShaderBinary/Pixel/Kuwahara2DShader.pso"));
	sceneGenerators_.emplace_back(ConstantBufferScene::Create);
	sceneGenerators_.emplace_back(std::bind(MultiRenderTargetScene::Create, "Assets/Image/texture0.png", "Assets/ShaderBinary/Pixel/MultiRT2DPixelShader.pso", 4));
	sceneGenerators_.emplace_back(std::bind(ModelFor1FrameScene::Create, "Assets/Model/cube.mv1", "Assets/ShaderBinary/Vertex/ModelVertexShader.vso", "Assets/ShaderBinary/Pixel/ModelPixelShader.pso"));

	scene_ = sceneGenerators_[index_]();
}

SceneManager::~SceneManager() = default;

void SceneManager::Update(void)
{
	ChangeScene();		//シーン変更の処理

	if (!scene_)
	{
		return;
	}

	stopWatch_.Reset();
	stopWatch_.Start();	//計測開始

	scene_->Update();	//シーンの更新

	stopWatch_.Stop();	//計測終了

	Draw();				//シーンの描画
}

void SceneManager::Draw(void) const
{
	//バックスクリーンの取得と設定
	const auto& backScreen = Screen::GetBackScreen();
	backScreen.Setup();
	backScreen.Clear();

	scene_->GetScreen().Draw(0.0f, 0.0f, true);		//シーンのスクリーンに対して描画

	//描画情報表示
	DrawFormatString(0, 0, 0xffffff, "DrawCall:%d\nProcessTime:%.6f", GetDrawCallCount(), stopWatch_.GetNowCount());
}

void SceneManager::ChangeScene(void)
{
	///マウスカーソルの変動量に応じたシーン変更
	const auto rotVal = -GetMouseWheelRotVol();
	if (!rotVal)
	{
		return;
	}

	const int size = static_cast<int>(sceneGenerators_.size());
	if (!size)
	{
		return;
	}

	index_ = (index_ + rotVal % size + size) % size;

	scene_ = sceneGenerators_[index_]();
}
