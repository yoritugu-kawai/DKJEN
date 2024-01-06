#pragma once
#include"Obj3D.h"
#include"../Math/Math.h"
#include"../Base/DxCommon.h"

#include"../Base/PaticlePSO.h"
#include"../Base/ImageLoading.h"
#include<fstream>
#include<sstream>
#include"../Base/ImageLoading.h"
class Particle
{
public:
	void Initialize();
	void SRV();
	void Draw();
	ID3D12Resource* CreateBufferResource(size_t sizeInbyte);
private:
	ModelData modelData;
	VertexData vertexData;
	ID3D12Resource* vetexResource;
	ID3D12Resource* lightResource;
	ID3D12Resource* Vertex;
	D3D12_VERTEX_BUFFER_VIEW vertxBufferView{};
	ID3D12Resource* materialResource;
	ID3D12Resource* wvpResource;
	TexProeerty  tex_;
	D3D12_GPU_DESCRIPTOR_HANDLE instancingSrvHandleGPU;
	Matrix4x4 matrix;
	const uint32_t kNumIstance = 10;
	ComPtr<ID3D12Resource>InstancingResource;
};


