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

VECTOR Model::GetScale(void) const
{
	return MV1GetScale(handle_);
}

void Model::SetScale(float x, float y, float z)
{
	SetScale({ x,y,z });
}

void Model::SetScale(const VECTOR& scale)
{
	MV1SetScale(handle_, scale);
}

void Model::Draw(void) const
{
	MV1DrawModel(handle_);
}

void Model::Draw(const VertexShader& vertex, const PixelShader& pixel) const
{
	MV1SetUseOrigShader(true);		//シェーダーを使ってMV1モデルを描画する前にtrueにする

	vertex.Begin();					//頂点シェーダーの開始処理
	pixel.Begin();					//ピクセルシェーダーの開始処理

	Draw();							//描画

	pixel.End();					//ピクセルシェーダーの終了処理
	vertex.End();					//頂点シェーダーの終了処理

	MV1SetUseOrigShader(false);		//シェーダーを使ってMV1モデルを描画した後はfalseにする
}

void Model::Draw(const VertexShader& vertex1Frame, const VertexShader& vertex4Frame, const VertexShader& vertex8Frame, const PixelShader& pixel) const
{
	//ループ用に配列を作成
	const VertexShader* vertexShaders[DX_MV1_VERTEX_TYPE_NUM];

	vertexShaders[DX_MV1_VERTEX_TYPE_1FRAME] = &vertex1Frame;			//1フレームの影響のみを受ける場合
	vertexShaders[DX_MV1_VERTEX_TYPE_4FRAME] = &vertex4Frame;			//1～4フレームの影響を受ける頂点が一つでもある場合
	vertexShaders[DX_MV1_VERTEX_TYPE_8FRAME] = &vertex8Frame;			//5～8フレームの影響を受ける頂点が一つでもある場合
	vertexShaders[DX_MV1_VERTEX_TYPE_FREE_FRAME] = nullptr;				//上記に当てはまらない頂点を持つ場合

	vertexShaders[DX_MV1_VERTEX_TYPE_NMAP_1FRAME] = &vertex1Frame;		//法線マップありで、1フレームの影響のみを受ける場合
	vertexShaders[DX_MV1_VERTEX_TYPE_NMAP_4FRAME] = &vertex4Frame;		//法線マップありで、1～4フレームの影響を受ける頂点が一つでもある場合
	vertexShaders[DX_MV1_VERTEX_TYPE_NMAP_8FRAME] = &vertex8Frame;		//法線マップありで、5～8フレームの影響を受ける頂点が一つでもある場合
	vertexShaders[DX_MV1_VERTEX_TYPE_NMAP_FREE_FRAME] = nullptr;		//法線マップありで、上記に当てはまらない頂点を持つ場合

	MV1SetUseOrigShader(true);		//シェーダーを使ってMV1モデルを描画する前にtrueにする

	//モデル中のトライアングルリストの数だけ回す
	const auto triangleListNum = MV1GetTriangleListNum(handle_);
	for (int i = 0; i < triangleListNum; i++)
	{
		//トライアングルリストの頂点タイプに一致したシェーダーがある場合はそれを取り出して処理
		if (const auto* vertexShader = vertexShaders[MV1GetTriangleListVertexType(handle_, i)])
		{
			vertexShader->Begin();					//選択された頂点シェーダーの開始処理
			pixel.Begin();							//ピクセルシェーダーの開始処理

			MV1DrawTriangleList(handle_, i);		//トライアングルリスト単位での描画

			pixel.End();							//ピクセルシェーダーの終了処理
			vertexShader->End();					//選択された頂点シェーダーの終了処理
		}
	}

	MV1SetUseOrigShader(false);		//シェーダーを使ってMV1モデルを描画した後はfalseにする
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
