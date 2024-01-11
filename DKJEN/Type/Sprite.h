#pragma once
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/SpritePSO.h"
#include"../Base/ImageLoading.h"
class  Sprite
{
public:
	 
	 void Initialize(TexProeerty  tex);
	 void Vertex();
	 void Darw(Vector3 scale, Vector3 rotate, Vector3 translate, Vector4 Color);
	// void Release();

	 ID3D12Resource* CreateBufferResource(size_t sizeInbyte);
private:

	//
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};
	D3D12_INDEX_BUFFER_VIEW indexBufferViewSprite{};
	
	VertexData* VertexDataSprite = nullptr;
	ComPtr<ID3D12Resource> vertexResourceSprite;
	ComPtr<ID3D12Resource>transformationMatrixResourceSprote;
	ComPtr<ID3D12Resource> materialResource;
	ComPtr<ID3D12Resource> indexResourceSprite;

	Matrix4x4* transformationMatrixDataSprite = nullptr;
	Transform transformSprite{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };


	TexProeerty  tex_;
	Vector4 transX_ = { 320.f,0.0f,0.0f,1.0f };
	Vector4 transY_ = { 0.0f,180.0f,0.0f,1.0f };
	Vector4 transXY_ = { 320.0f,180.0f,0.0f,1.0f };
	Transform uvTranformSprite{
	 {1.0f,1.0f,1.0f},
	 {0.0f,0.0f,0.0f},
	 {0.0f,0.0f,0.0f}
	};
	Matrix4x4 matrix;
};


