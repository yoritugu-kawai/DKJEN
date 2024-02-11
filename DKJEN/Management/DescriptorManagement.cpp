#include "DescriptorManagement.h"

DescriptorManagement* DescriptorManagement::GetInstance()
{
	static DescriptorManagement instance;

	return &instance;
}

void DescriptorManagement::Initialize()
{
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorManagement::CPUDescriptorHandle( uint32_t descriptorSizeSRV, uint32_t LoadCount, D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc, ComPtr <ID3D12Resource>textureResource)
{
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
	ID3D12DescriptorHeap* srvDescriptorHeap = DxCommon::GetInstance()->GetsrvDescriptorHeap();
	D3D12_CPU_DESCRIPTOR_HANDLE texSrvHandleCPU =
		GetCPUDescriptorHandle(
			srvDescriptorHeap, descriptorSizeSRV, LoadCount);
	texSrvHandleCPU.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	device->CreateShaderResourceView(textureResource.Get(), &srvDesc, texSrvHandleCPU);
	return texSrvHandleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE DescriptorManagement::GPUDescriptorHandle(uint32_t descriptorSizeSRV, uint32_t LoadCount)
{
	
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
	ID3D12DescriptorHeap* srvDescriptorHeap = DxCommon::GetInstance()->GetsrvDescriptorHeap();
	D3D12_GPU_DESCRIPTOR_HANDLE texSrvHandleGPU =
		GetGPUDescriptorHandle(
			srvDescriptorHeap, descriptorSizeSRV, LoadCount);
	texSrvHandleGPU.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	return texSrvHandleGPU;
	
}
