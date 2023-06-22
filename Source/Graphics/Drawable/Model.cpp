#include "Model.h"
#include "Graphics/Shader/VertexShader.h"
#include "Graphics/Shader/PixelShader.h"

ModelPtr Model::Create(const std::filesystem::path& path)
{
	return ModelPtr(new Model(path));
}

ModelPtr Model::Create(const Model& model)
{
	return ModelPtr(new Model(model));
}

Model::~Model()
{
	MV1DeleteModel(handle_);
}

VECTOR Model::GetPosition(void) const
{
	return MV1GetPosition(handle_);
}

VECTOR Model::GetRotation(void) const
{
	return MV1GetRotationXYZ(handle_);
}

void Model::SetPosition(float x, float y, float z)
{
	SetPosition({ x,y,z });
}

void Model::SetPosition(const VECTOR& pos)
{
	MV1SetPosition(handle_, pos);
}

void Model::SetRotation(float x, float y, float z)
{
	SetRotation({ x,y,z });
}

void Model::SetRotation(const VECTOR& rot)
{
	MV1SetRotationXYZ(handle_, rot);
}

void Model::Draw(void) const
{
	MV1DrawModel(handle_);
}

void Model::Draw(const VertexShader& vertex, const PixelShader& pixel) const
{
	MV1SetUseOrigShader(true);

	vertex.Begin();
	pixel.Begin();

	Draw();

	pixel.End();
	vertex.End();

	MV1SetUseOrigShader(false);
}

Model::Model(const Model& model):
	handle_(MV1DuplicateModel(model.handle_))
{
}

Model& Model::operator=(const Model& model)
{
	handle_ = MV1DuplicateModel(model.handle_);
	return *this;
}

Model::Model(const std::filesystem::path& path) :
	handle_(MV1LoadModel(path.string().c_str()))
{
}
