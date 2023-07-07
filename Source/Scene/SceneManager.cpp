#include "SceneManager.h"
#include "Scene.h"
#include "Graphics/Drawable/Screen.h"
#include "Scene/Derived/2D/ImageScene.h"
#include "Scene/Derived/2D/ConstantBufferScene.h"
#include "Scene/Derived/2D/MultiRenderTargetScene.h"
#include "Scene/Derived/3D/ModelFor1FrameScene.h"
#include "Scene/Derived/3D/ModelForAllFrameScene.h"

SceneManager::SceneManager() :
	index_(0)
{
	sceneGenerators_.emplace_back(std::bind(ImageScene::Create, "通常の画像の描画を行うシーン", "Assets/Image/texture0.png", "Assets/ShaderBinary/Pixel/ImagePixelShader.pso"));
	sceneGenerators_.emplace_back(std::bind(ImageScene::Create, "Kuwaharaフィルターを適用したシーン", "Assets/Image/texture0.png", "Assets/ShaderBinary/Pixel/Kuwahara2DShader.pso"));
	sceneGenerators_.emplace_back(ConstantBufferScene::Create);
	sceneGenerators_.emplace_back(std::bind(MultiRenderTargetScene::Create, "マルチレンダーターゲットを使用したシーン", "Assets/Image/texture0.png", "Assets/ShaderBinary/Pixel/MultiRT2DPixelShader.pso", 4));
	sceneGenerators_.emplace_back(std::bind(ModelFor1FrameScene::Create, "ボーンがないモデルの描画を行うシーン", "Assets/Model/cube.mv1", "Assets/ShaderBinary/Vertex/Model1FrameVertexShader.vso", "Assets/ShaderBinary/Pixel/ModelPixelShader.pso"));
	sceneGenerators_.emplace_back(std::bind(ModelFor1FrameScene::Create, "パールシェーダーを適用したシーン", "Assets/Model/monkey.mv1", "Assets/ShaderBinary/Vertex/Model1FrameVertexShader.vso", "Assets/ShaderBinary/Pixel/PearlShader.pso"));
	sceneGenerators_.emplace_back(std::bind(ModelFor1FrameScene::Create, "法線マップを適用したボーンがないモデルの描画を行うシーン", "Assets/Model/rock.mv1", "Assets/ShaderBinary/Vertex/ModelNormal1FrameVertexShader.vso", "Assets/ShaderBinary/Pixel/ModelNormalPixelShader.pso"));
	sceneGenerators_.emplace_back(std::bind(ModelForAllFrameScene::Create,
		"ボーンを持つモデルの描画を行うシーン",
		"Assets/Model/human.mv1",
		"Assets/ShaderBinary/Vertex/Model1FrameVertexShader.vso",
		"Assets/ShaderBinary/Vertex/Model4FrameVertexShader.vso",
		"Assets/ShaderBinary/Vertex/Model8FrameVertexShader.vso",
		"Assets/ShaderBinary/Pixel/ModelPixelShader.pso"));

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
	DrawFormatString(0, 0, 0xffffff, "%s\nDrawCall:%d\nProcessTime:%.6f", scene_->GetName().c_str(), GetDrawCallCount(), stopWatch_.GetNowCount());
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
