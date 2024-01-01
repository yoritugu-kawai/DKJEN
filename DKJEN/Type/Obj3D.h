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
	/// <summary>
	/// 
	/// </summary>
	/// <param name="tex"></param>
	void Initialize(TexProeerty  tex);
	/// <summary>
	/// 参考数値↓
	/// </summary>
	/// <param name="Vector3 scale={ 0.5f, 0.5f, 0.5f }"></param>
	/// <param name="Vector3 rotate = { 0.0f, 0.0f, 0.0f }"></param>
	/// <param name="Vector3 translate = { 0.0f, 0.0f, 0.0f }"></param>
	/// <param name="Vector4 color = { 1.0f,1.0f,1.0f,1.0f }"></param>
	void Draw(Vector3 scale, Vector3 rotate, Vector3 translate, Vector4 Color);
	void Instancing(int inst);
	void Release();
	
	void SRV();
	ID3D12Resource* CreateBufferResource(size_t sizeInbyte);

	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);

	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

	
private:
	ID3D12Resource* vetexResource;
	ID3D12Resource* materialResource;
	ID3D12Resource* wvpResource;
	ID3D12Resource* lightResource;

	ComPtr<ID3D12Resource>InstancingResource;
	D3D12_VERTEX_BUFFER_VIEW vertxBufferView{};
	ModelData modelData;
	Matrix4x4 matrix;
	TexProeerty  tex_;
	ImageLoading* imageLoading = new ImageLoading;
	int inst_ = 0;
	const uint32_t kNumIstance = 10;

	Vector3 pos;
};
