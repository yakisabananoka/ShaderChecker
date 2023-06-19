#include "SceneManager.h"
#include "Scene.h"
#include "Graphics/Drawable/Screen.h"
#include "Scene/Deriverd/2D/ImageScene.h"
#include "Scene/Deriverd/2D/ConstantBufferScene.h"
#include "Scene/Deriverd/3D/ModelFor1FrameScene.h"

SceneManager::SceneManager() :
	index_(0)
{
	sceneGenerators_.emplace_back(std::bind(ImageScene::Create, "Assets/Image/texture0.png", "Assets/ShaderBinary/Pixel/ImagePixelShader.pso"));
	sceneGenerators_.emplace_back(std::bind(ImageScene::Create, "Assets/Image/texture0.png", "Assets/ShaderBinary/Pixel/Kuwahara2DShader.pso"));
	sceneGenerators_.emplace_back(ConstantBufferScene::Create);
	sceneGenerators_.emplace_back(std::bind(ModelFor1FrameScene::Create, "Assets/Model/cube.mv1", "Assets/ShaderBinary/Vertex/ModelVertexShader.vso", "Assets/ShaderBinary/Pixel/ModelPixelShader.pso"));

	scene_ = sceneGenerators_[index_]();
}

SceneManager::~SceneManager() = default;

void SceneManager::Update(void)
{
	ChangeScene();

	if (!scene_)
	{
		return;
	}

	scene_->Update();
	Draw();
}

void SceneManager::Draw(void) const
{
	const auto& backScreen = Screen::GetBackScreen();
	backScreen.Setup();
	backScreen.Clear();

	scene_->GetScreen().Draw(0.0f, 0.0f, true);
}

void SceneManager::ChangeScene(void)
{
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
