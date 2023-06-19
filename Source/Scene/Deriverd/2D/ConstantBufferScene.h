#pragma once
#include "Scene/Scene.h"
#include "Scene/UsingScene.h"
#include "Graphics/UsingGraphics.h"
#include "Graphics/Shader/PixelShader.h"
#include "Common/StopWatch.h"

class ConstantBufferScene final :
	public Scene
{
public:
	/// @brief 定数バッファとして転送するための構造体(DirectX11は16byteアライメントのためpaddingで調整)
	struct Test
	{
		float time;				//経過時間
		float padding[3];		//パディング
	};

	/// @brief ImageSceneの生成
	/// @return 生成されたImageScene
	static ScenePtrTemplate<ConstantBufferScene> Create(void);

	/// @brief デストラクタ
	~ConstantBufferScene() override;

	/// @brief 更新
	void Update(void) override;

	ConstantBufferScene(const ConstantBufferScene&) = delete;
	ConstantBufferScene& operator=(const ConstantBufferScene&) = delete;

	ConstantBufferScene(ConstantBufferScene&&) = delete;
	ConstantBufferScene& operator=(ConstantBufferScene&&) = delete;
private:
	ConstantBufferScene();

	ImagePtr image_;									//画像
	PixelShader pixelShader_;							//画像用のピクセルシェーダー
	ConstantBufferPtr<Test> constantBuffer_;			//定数バッファ

	StopWatch stopWatch_;								//時間計測

};
