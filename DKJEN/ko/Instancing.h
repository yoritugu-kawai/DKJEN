#pragma once
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/SpritePSO.h"
#include"../Base/TexturePSO.h"
#include"../Base/LightPSO.h"
#include"../Base/ImageLoading.h"
#include<fstream>
#include<sstream>

class Instancing{
public:
	//コンストラクタ
	Instancing();

	//初期化
	void Initialize();

	//グラフィックコマンドの設定
	void SetGraphicsCommand();

	//ドローコール
	void GraphicsCommand();

	//デストラクタ
	~Instancing();
	ID3D12Resource* CreateBufferResource(size_t sizeInbyte);

public:
	int GetInstanceCount() {
		return instanceCount_;
	}

private:
	
	D3D12_CPU_DESCRIPTOR_HANDLE instancingSrvHandleCPU_ = {};
	D3D12_GPU_DESCRIPTOR_HANDLE instancingSrvHandleGPU_ = {};

	ComPtr<ID3D12Resource>instancingResource_ = nullptr;

	static const int32_t instanceCount_ = 10;
	Transform transforms[instanceCount_];
	TransformationMatrix* instancingData_ = nullptr;
};

