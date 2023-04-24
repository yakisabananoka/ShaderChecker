#pragma once
#include <filesystem>
#include "Shader.h"

class PixelShader :
	public Shader
{
public:
	PixelShader(std::filesystem::path path);
	~PixelShader() override;

	void Begin(void) const;
	void End(void) const;

	PixelShader(const PixelShader&) = delete;
	PixelShader& operator=(const PixelShader&) = delete;

	PixelShader(PixelShader&&) = default;
	PixelShader& operator=(PixelShader&&) = default;

private:
	int handle_;

};
