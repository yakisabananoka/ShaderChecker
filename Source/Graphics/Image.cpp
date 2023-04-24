#include <array>
#include <DxLib.h>
#include "Image.h"
#include "PixelShader.h"

static std::array<VERTEX2DSHADER, 4> vertices = {};		//シェーダー描画用

Image::Image(const std::filesystem::path& path)
{
	handle_ = LoadGraph(path.string().c_str());
}

Image::~Image()
{
	DeleteGraph(handle_);
}

void Image::Draw(float x, float y, bool transFlg) const
{
	DrawGraph(static_cast<int>(x), static_cast<int>(y), handle_, transFlg);
}

void Image::Draw(float x, float y, const PixelShader& pixelShader) const
{
	float sizeX, sizeY = {};
	GetGraphSizeF(handle_, &sizeX, &sizeY);

	for (int index = 0; auto & vertex : vertices)
	{
		vertex.u = static_cast<float>(index % 2);
		vertex.v = static_cast<float>(index >= 2);

		vertex.pos.x = x + sizeX * vertex.u;
		vertex.pos.y = y + sizeY * vertex.v;
		vertex.pos.z = 0.0f;

		vertex.dif = GetColorU8(255, 255, 255, 255);
		vertex.spc = GetColorU8(255, 255, 255, 255);
		vertex.rhw = 1.0f;

		vertex.su = vertex.u;
		vertex.sv = vertex.v;

		index++;
	}

	SetUseTextureToShader(0, handle_);

	pixelShader.Begin();

	DrawPrimitive2DToShader(vertices.data(), static_cast<int>(vertices.size()), DX_PRIMTYPE_TRIANGLESTRIP);

	pixelShader.End();

	SetUseTextureToShader(0, -1);
}
