#pragma once
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/SpritePSO.h"
#include"../Base/TexturePSO.h"
#include"../Base/LightPSO.h"
#include"../Base/ImageLoading.h"
#include<fstream>
#include<sstream>
class CreateMaterial{
public:

	void Initialize();

	void SetInformation(Vector4 setColor);

	void GraphicsCommand();
	ID3D12Resource* CreateBufferResource(size_t sizeInbyte);

	
	struct Material {
	Vector4 color;
	//boolの代わりにint32_t
	int32_t enableLighting;
	float padding[3];
	Matrix4x4 uvTransform;
};

private:
	//頂点リソースを作る
	ComPtr<ID3D12Resource> materialResource_ = nullptr;
		

	


};

