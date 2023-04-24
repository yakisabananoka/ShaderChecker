#pragma once
#include <filesystem>
#include "UsingGraphics.h"

class Image
{
public:
	Image(const std::filesystem::path& path);
	~Image();

	void Draw(float x, float y, bool transFlg) const;
	void Draw(float x, float y, const PixelShader& pixelShader) const;

	Image(const Image&) = delete;
	Image& operator=(const Image&) = delete;

	Image(Image&&) = default;
	Image& operator=(Image&&) = default;

private:
	int handle_;
};

