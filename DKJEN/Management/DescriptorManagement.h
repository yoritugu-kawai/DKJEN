#pragma once
#include"../Base/WinApp.h"
#include"../Base/DxCommon.h"
#include"../Base/Function.h"
#include"../externals/DirectXTex/d3dx12.h"
#include"../externals/DirectXTex/DirectXTex.h"
#include"../Base/ImageLoading.h"
class DescriptorManagement
{
public:
	static DescriptorManagement* GetInstance();
	static void Initialize();
	static D3D12_CPU_DESCRIPTOR_HANDLE CPUDescriptorHandle( uint32_t descriptorSizeSRV, uint32_t LoadCount, D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc, ComPtr <ID3D12Resource>textureResource);
	static D3D12_GPU_DESCRIPTOR_HANDLE GPUDescriptorHandle( uint32_t descriptorSizeSRV, uint32_t LoadCount);
private:

};
