#include "Particle.h"

void Particle::Initialize()
{

}

void Particle::SRV()
{
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
	ID3D12DescriptorHeap* srvDescriptorHeap = DxCommon::GetInstance()->GetsrvDescriptorHeap();
	uint32_t descriptorSizeSRV = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	D3D12_SHADER_RESOURCE_VIEW_DESC instansingSrvDesc{};
	instansingSrvDesc.Format = DXGI_FORMAT_UNKNOWN;
	instansingSrvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	instansingSrvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	instansingSrvDesc.Buffer.FirstElement = 0;
	instansingSrvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	instansingSrvDesc.Buffer.NumElements = 10;
	instansingSrvDesc.Buffer.StructureByteStride = sizeof(TransformationMatrix);
	D3D12_CPU_DESCRIPTOR_HANDLE instancingSrvHandleCPU = GetCPUDescriptorHandle(srvDescriptorHeap, descriptorSizeSRV, 3);
	D3D12_GPU_DESCRIPTOR_HANDLE instancingSrvHandleGPU = GetGPUDescriptorHandle(srvDescriptorHeap, descriptorSizeSRV, 3);
	device->CreateShaderResourceView(InstancingResource.Get(), &instansingSrvDesc, instancingSrvHandleCPU);
}

void Particle::Draw()
{
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.material.textureFilePath = "./resoures/uvChecker.png";


}
