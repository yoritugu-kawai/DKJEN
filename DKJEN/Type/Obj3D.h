#pragma once
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/SpritePSO.h"
#include"../Base/TexturePSO.h"
#include"../Base/LightPSO.h"
#include"../Base/ImageLoading.h"
#include<fstream>
#include<sstream>
struct MaterialData {
	std::string textureFilePath;
};

struct ModelData
{
	std::vector<VertexData>vertices;
	MaterialData material;
};


class Obj3D {
public:
	void Initialize(TexProeerty  tex);
	/// <summary>
	/// m= MakeAffineMatrix(scale,rotate,translate);
	/// の式を計算してmを引数に代入
	/// </summary>
	/// <param name="m"></param>
	/// 
	/// <param name="Color"></param>
	void Draw(Vector3 scale, Vector3 rotate, Vector3 translate, Vector4 Color);
	void Release();
	ID3D12Resource* CreateBufferResource(size_t sizeInbyte);

	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);
private:
	ID3D12Resource* vetexResource;
	ID3D12Resource* materialResource;
	ID3D12Resource* wvpResource;
	ID3D12Resource* lightResource;

	D3D12_VERTEX_BUFFER_VIEW vertxBufferView{};
	ModelData modelData;
	Matrix4x4 matrix;
	TexProeerty  tex_;
	ImageLoading* imageLoading = new ImageLoading;

	Vector3 pos;
};
