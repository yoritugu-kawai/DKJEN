#pragma once
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/ParyiclePSO.h"
#include"../Base/ImageLoading.h"
#include"../Type/Obj3D.h"
#include<fstream>
#include<sstream>
class Particle
{
public:
	void Initialize(TexProeerty  tex);
	void Vertex();
	void Darw(Vector3 scale, Vector3 rotate, Vector3 translate, Vector4 Color);
	void Release();

	ID3D12Resource* CreateBufferResource(size_t sizeInbyte);
private:

	//
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};
	D3D12_INDEX_BUFFER_VIEW indexBufferViewSprite{};

	VertexData* VertexDataSprite = nullptr;
	ID3D12Resource* vertexResourceSprite;
	ID3D12Resource* transformationMatrixResourceSprote;
	ID3D12Resource* materialResource;
	ID3D12Resource* indexResourceSprite;

	Matrix4x4* transformationMatrixDataSprite = nullptr;
	Transform transformSprite{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };


	TexProeerty  tex_;
	Vector4 transX_ = { 560.f,0.0f,0.0f,1.0f };
	Vector4 transY_ = { 0.0f,360.0f,0.0f,1.0f };
	Vector4 transXY_ = { 560.0f,360.0f,0.0f,1.0f };
	Transform uvTranformSprite{
	 {1.0f,1.0f,1.0f},
	 {0.0f,0.0f,0.0f},
	 {0.0f,0.0f,0.0f}
	};
	Matrix4x4 matrix;
	ModelData model;
	VertexData v;
};
