#include "ImageScene.h"
#include "Graphics/Drawable/Image.h"
#include "Graphics/Drawable/Screen.h"
#include "Graphics/Shader/ConstantBuffer.h"
#include "Graphics/Shader/PixelShader.h"

ScenePtrTemplate<ImageScene> ImageScene::Create(const std::filesystem::path& imagePath, const std::filesystem::path& pixelShaderPath)
{
	return ScenePtrTemplate<ImageScene>(new ImageScene(imagePath, pixelShaderPath));
}

ImageScene::~ImageScene() = default;

void ImageScene::Update(void)
{
	//ここから描画処理

	screen_->Setup();		//スクリーンの設定
	screen_->Clear();		//スクリーンを初期化

	image_->Draw(0.0f, 0.0f, *pixelShader_);			//ピクセルシェーダーを使用して画像を描画

	//ここまで描画処理
}

ImageScene::ImageScene(const std::filesystem::path& imagePath, const std::filesystem::path& pixelShaderPath) :
	image_(Image::Create(imagePath)),
	pixelShader_(PixelShader::Create(pixelShaderPath))
{
}
