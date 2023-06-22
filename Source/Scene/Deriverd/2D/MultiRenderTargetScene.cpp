#include "MultiRenderTargetScene.h"
#include "Graphics/Drawable/Screen.h"
#include "Graphics/Drawable/RenderTargets.h"
#include "Graphics/Shader/PixelShader.h"

ScenePtrTemplate<MultiRenderTargetScene> MultiRenderTargetScene::Create(const std::filesystem::path& imagePath, const std::filesystem::path& pixelShaderPath, unsigned num)
{
	return ScenePtrTemplate<MultiRenderTargetScene>(new MultiRenderTargetScene(imagePath, pixelShaderPath, num));
}

MultiRenderTargetScene::~MultiRenderTargetScene() = default;

void MultiRenderTargetScene::Update(void)
{
	//一辺の数を算出
	const float sideLen = ceil(sqrt(static_cast<float>(renderTargets_->GetSize())));

	//スクリーンサイズを取得
	float divSizeX, divSizeY;
	screen_->GetScreenSize(divSizeX, divSizeY);

	//実際に表示するスクリーンのサイズを計算
	divSizeX /= sideLen;
	divSizeY /= sideLen;

	//ここから描画処理

	renderTargets_->Clear();						//レンダーターゲットの初期化

	image_->Draw(0.0f, 0.0f, *pixelShader_);		//ピクセルシェーダーを使用して各レンダーターゲットに描画

	screen_->Setup();		//シーンのスクリーンを設定
	screen_->Clear();		//シーンのスクリーンを初期化
	
	for (int i = 0; const auto& scr : *renderTargets_)
	{
		//各スクリーンの表示位置を計算
		const auto x = static_cast<float>(i % static_cast<int>(sideLen)) * divSizeX;
		const auto y = static_cast<float>(i / static_cast<int>(sideLen)) * divSizeY;

		scr->Draw(x, y, x + divSizeX, y + divSizeY, true);		//スクリーンを描画

		i++;
	}

	//ここまで描画処理
}

MultiRenderTargetScene::MultiRenderTargetScene(const std::filesystem::path& imagePath, const std::filesystem::path& pixelShaderPath, unsigned int num) :
	image_(Image::Create(imagePath)), pixelShader_(PixelShader::Create(pixelShaderPath)), renderTargets_(RenderTargets::Create(num))
{
	pixelShader_->SetRenderTargets(renderTargets_);		//ピクセルシェーダーが出力する先のレンダーターゲットを設定
}
