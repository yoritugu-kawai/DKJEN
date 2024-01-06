#pragma once
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/SpritePSO.h"
#include"../Base/TexturePSO.h"
#include"../Base/LightPSO.h"
#include"../Base/ImageLoading.h"
#include<fstream>
#include<sstream>
class CreateDirectionalLight{
public:

	void Initialize();


	void GraphicsCommand();

	ID3D12Resource* CreateBufferResource(size_t sizeInbyte);

	



private:
	ComPtr<ID3D12Resource> directionalLightResource_ = nullptr;
	DirectionalLight* directionalLightData_ = nullptr;




};

