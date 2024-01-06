#pragma once

#include <vector>
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/SpritePSO.h"
#include"../Base/TexturePSO.h"
#include"../Base/LightPSO.h"
#include"../Base/ImageLoading.h"
#include<fstream>
#include<sstream>

class Mesh{
public:

	void Initialize(const std::vector<VertexData>& vertices);

	void GraphicsCommand();

	void DrawCall(int32_t instanceCount);

	ID3D12Resource* CreateBufferResource(size_t sizeInbyte);

private:
	//頂点リソースを作る
	ComPtr<ID3D12Resource> vertexResource_ = nullptr;
		

	//頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;

	std::vector<VertexData> vertices_{};

	int32_t instanceCount_ = 1;
};

