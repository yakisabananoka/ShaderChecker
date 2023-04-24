#pragma once
#include <unordered_map>
#include "UsingGraphics.h"

class Shader
{
public:
	Shader() = default;
	virtual ~Shader() = default;

	void SetConstantBuffer(ConstantBufferBaseWeakPtr ptr, int slot);

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&&) = default;
	Shader& operator=(Shader&&) = default;

protected:
	void BeginConstantBuffer(int shaderType) const;
	void EndConstantBuffer(int shaderType) const;

	std::unordered_map<int, ConstantBufferBaseWeakPtr> constantBufferInfos_;
};
