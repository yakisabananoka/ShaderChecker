#pragma once
#include <vector>
#include "../Model.h"
#include "Graphics/UsingGraphics.h"

class PBRMaterial final:
	public Model::Material
{
public:
	struct Element
	{

	};

	static MaterialPtrTemplate<PBRMaterial> Create(int materialNum);

	~PBRMaterial() override;
	void Begin(int index) const override;
	void End(int index) const override;



	PBRMaterial(const PBRMaterial&) = delete;
	PBRMaterial& operator=(const PBRMaterial&) = delete;

	PBRMaterial(PBRMaterial&&) = delete;
	PBRMaterial& operator=(PBRMaterial&&) = delete;

private:
	PBRMaterial(int materialNum);
	std::vector<Element> elements_;
};