#pragma once
#include"Obj3D.h"
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/SpritePSO.h"
#include"../Base/TexturePSO.h"
#include"../Base/LightPSO.h"
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

	ID3D12Resource* lightResource;

	const uint32_t kNumIstance = 10;
	ComPtr<ID3D12Resource>InstancingResource
};


