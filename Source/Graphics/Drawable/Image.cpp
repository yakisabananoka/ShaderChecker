#include <array>
#include <DxLib.h>
#include "Image.h"
#include "Graphics/Shader/PixelShader.h"

static std::array<VERTEX2DSHADER, 4> vertices = {};			//シェーダー描画用

Image::Image(std::filesystem::path path) :
	Image(LoadGraph(path.string().c_str()))
{
}

Image::~Image()
{
	DeleteGraph(handle_);									//画像の削除
}

void Image::Draw(float x, float y, bool transFlg) const
{
	DrawGraph(static_cast<int>(x), static_cast<int>(y), handle_, transFlg);			//描画
}

void Image::Draw(float x, float y, const PixelShader& pixelShader) const
{
	float sizeX, sizeY = {};
	GetGraphSizeF(handle_, &sizeX, &sizeY);				//画像サイズを取得

	//各頂点に対して設定
	for (int index = 0; auto & vertex : vertices)
	{
		vertex.u = static_cast<float>(index % 2);		//奇数の場合は0、偶数の場合は1を設定
		vertex.v = static_cast<float>(index >= 2);		//2未満の場合は0、それ以外は1を設定

		vertex.pos.x = x + sizeX * vertex.u;			//Uを使用してXを算出
		vertex.pos.y = y + sizeY * vertex.v;			//Vを算出してYを算出
		vertex.pos.z = 0.0f;							//とりあえず0

		vertex.dif = GetColorU8(255, 255, 255, 255);		//拡散反射は白を設定
		vertex.spc = GetColorU8(255, 255, 255, 255);		//鏡面反射は白を設定

		vertex.rhw = 1.0f;			//除算数(とりあえず1)

		vertex.su = vertex.u;		//サブテクスチャU値
		vertex.sv = vertex.v;		//サブテクスチャV値

		index++;					//インデックスを加算
	}

	SetUseTextureToShader(0, handle_);					//0番スロットにテクスチャを設定

	pixelShader.Begin();								//シェーダーの開始処理

	DrawPrimitive2DToShader(vertices.data(), static_cast<int>(vertices.size()), DX_PRIMTYPE_TRIANGLESTRIP);		//TRAIANGLESTRIPでポリゴンを作り描画

	pixelShader.End();									//シェーダーの終了処理

	SetUseTextureToShader(0, -1);	//テクスチャの設定を解除
}

void Image::Draw(VECTOR pos, float cx, float cy, float size, float angle, bool transFlg)
{
	DrawBillboard3D(pos, cx, cy, size, angle, handle_, transFlg);
}

void Image::Draw(VECTOR pos, float cx, float cy, float size, float angle, bool transFlg, const PixelShader& pixel)
{
	pixel.Begin();

	DrawBillboard3DToShader(pos, cx, cy, size, angle, handle_, transFlg);

	pixel.End();
}

Image::Image(Image&& image) noexcept:
	handle_(image.handle_)
{
	image.handle_ = -1;
}

Image& Image::operator=(Image&& image) noexcept
{
	handle_ = image.handle_;
	image.handle_ = -1;
	return *this;
}

Image::Image(int handle) :
	handle_(handle)
{
}
