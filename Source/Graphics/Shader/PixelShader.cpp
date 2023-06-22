#include <ranges>
#include <utility>
#include <DxLib.h>
#include "PixelShader.h"
#include "Graphics/Camera/Camera.h"
#include "Graphics/Drawable/Image.h"
#include "Graphics/Drawable/RenderTargets.h"

PixelShaderPtr PixelShader::Create(const std::filesystem::path& path)
{
	return PixelShaderPtr(new PixelShader(path));
}

void PixelShader::Begin(void) const
{
	SetUsePixelShader(handle_);								//ピクセルシェーダーの使用を設定
	BeginConstantBuffer(DX_SHADERTYPE_PIXEL);				//定数バッファの開始処理
	BeginTexture();											//テクスチャの開始処理
	BeginRenderTarget();									//レンダーターゲットの開始処理
}

void PixelShader::End(void) const
{
	EndRenderTarget();										//レンダーターゲットの終了処理
	EndTexture();											//テクスチャの終了処理
	EndConstantBuffer(DX_SHADERTYPE_PIXEL);					//定数バッファの終了処理
	SetUsePixelShader(-1);									//ピクセルシェーダーの使用を解除
}

void PixelShader::SetRenderTargets(RenderTargetsWeakPtr renderTargets)
{
	SetRenderTargets(std::move(renderTargets), CameraWeakPtr());
}

void PixelShader::SetRenderTargets(RenderTargetsWeakPtr renderTargets, CameraWeakPtr camera)
{
	renderTargets_ = std::move(renderTargets);		//レンダーターゲットを設定
	camera_ = std::move(camera);					//カメラを設定
}

void PixelShader::SetTexture(ImageWeakPtr image, int slot)
{
	textureInfo_[slot] = std::move(image);			//スロット番号をキーとしてテクスチャを設定
}

void PixelShader::SetTexture(nullptr_t, int slot)
{
	//スロット番号のテクスチャを削除
	if (textureInfo_.contains(slot))
	{
		textureInfo_.erase(slot);
	}
}

PixelShader::PixelShader(const std::filesystem::path& path) :
	Shader(LoadPixelShader(path.string().c_str()))
{
}

void PixelShader::BeginRenderTarget(void) const
{
	if (const auto renderTargetPtr = renderTargets_.lock())
	{
		renderTargetPtr->Begin();
	}

	//カメラの設定
	if (const auto camera = camera_.lock())
	{
		camera->Setup();
	}
}

void PixelShader::EndRenderTarget(void) const
{
	if (const auto renderTargetPtr = renderTargets_.lock())
	{
		renderTargetPtr->End();
	}
}

void PixelShader::BeginTexture(void) const
{
	//設定された全テクスチャの取り出し
	for (const auto& [slot, ptr] : textureInfo_)
	{
		//テクスチャが生きている場合はロック
		if (const auto texturePtr = ptr.lock())
		{
			texturePtr->SetupToShader(slot);		//シェーダーに対してテクスチャを設定
		}
	}
}

void PixelShader::EndTexture(void) const
{
	//ハッシュマップからキーのみを取り出し
	for (const auto& slot : textureInfo_ | std::views::keys)
	{
		SetUseTextureToShader(slot, -1);			//設定されたテクスチャを解除する
	}
}
