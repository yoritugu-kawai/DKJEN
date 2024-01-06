#include "Particle.h"

void Particle::Initialize()
{
	InstancingResource = CreateBufferResource(sizeof(TransformationMatrix) * kNumIstance);
	vetexResource = CreateBufferResource(sizeof(VertexData) * modelData.vertices.size());
	materialResource = CreateBufferResource(sizeof(Vector4));
	wvpResource = CreateBufferResource(sizeof(TransformationMatrix));
	
	vertxBufferView.BufferLocation = vetexResource->GetGPUVirtualAddress();
	vertxBufferView.SizeInBytes = UINT(sizeof(VertexData) * modelData.vertices.size());
	vertxBufferView.StrideInBytes = sizeof(VertexData);
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
	 instancingSrvHandleGPU = GetGPUDescriptorHandle(srvDescriptorHeap, descriptorSizeSRV, 3);
	device->CreateShaderResourceView(InstancingResource.Get(), &instansingSrvDesc, instancingSrvHandleCPU);
}

void Particle::Draw()
{
	Matrix4x4 ProjectionMatrix = MakePerspectiveFovMatrix(0.45f, float(1280.0f / 720.0f), 0.1f, 100.0f);
	TransformationMatrix* inststacingDet = nullptr;

	Vector4* materialData = nullptr;
	TransformationMatrix* matrixData = nullptr;


	InstancingResource->Map(0, nullptr, reinterpret_cast<void**>(&inststacingDet));
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&matrixData));
	


	Matrix4x4 CameraMatrix = MakeIdentity4x4();

	matrix = Multiply(matrix, Multiply(CameraMatrix, ProjectionMatrix));
	matrixData->WVP = matrix;
	matrixData->World = MakeIdentity4x4();
	*materialData = { 1.0f,1.0f,1.0f,1.0f };
	
	for (uint32_t i = 0; i < kNumIstance; ++i)
	{
		inststacingDet[i].WVP = MakeIdentity4x4();
		inststacingDet[i].World = MakeIdentity4x4();
	}
	Transform transfom[10];
	for (uint32_t i = 0; i < kNumIstance; ++i)
	{
		transfom[i].scale = { 1.0f,1.0f,1.0f };
		transfom[i].rotate = { 0.0f,0.0f,0.0f };
		transfom[i].translate = { i * 0.1f,i * 0.1f,i * 0.1f };
	}

	for (uint32_t i = 0; i < kNumIstance; ++i)
	{
		Matrix4x4 woldMatrix = MakeAffineMatrix(transfom[i].scale, transfom[i].rotate, transfom[i].translate);
		Matrix4x4 woldViewProMatrix = Multiply(woldMatrix, ProjectionMatrix);
		inststacingDet[i].WVP = woldViewProMatrix;
		inststacingDet[i].World = woldMatrix;
	}


	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.material.textureFilePath = "./resoures/uvChecker.png";

	PSOProperty pso_ = Paticle::GetInstance()->GetPSO().polygon;
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();
	
	commandList->SetGraphicsRootSignature(pso_.rootSignature);
	commandList->SetPipelineState(pso_.GraphicsPipelineState);//


	commandList->IASetVertexBuffers(0, 1, &vertxBufferView);

	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	commandList->SetGraphicsRootDescriptorTable(2, instancingSrvHandleGPU);
	commandList->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	commandList->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());
	commandList->SetGraphicsRootConstantBufferView(3, InstancingResource->GetGPUVirtualAddress());

	commandList->DrawInstanced(UINT(modelData.vertices.size()), 10, 0, 0);

}

ID3D12Resource* Particle::CreateBufferResource(size_t sizeInbyte)
{
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();
	ID3D12Resource* RssultResource;
	//頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};

	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD; //UploadHeapを使う

	//頂点リソースの設定
	D3D12_RESOURCE_DESC ResourceDesc{};

	//バッファリソース。テクスチャの場合はまた別の設定をする
	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	ResourceDesc.Width = sizeInbyte; //リソースのサイズ。今回はvector4を3頂点分

	//バッファの場合はこれらは1にする決まり
	ResourceDesc.Height = 1;
	ResourceDesc.DepthOrArraySize = 1;
	ResourceDesc.MipLevels = 1;
	ResourceDesc.SampleDesc.Count = 1;

	//バッファの場合はこれにする決まり
	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	HRESULT hr;
	hr = device->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&ResourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&RssultResource));
	assert(SUCCEEDED(hr));

	return RssultResource;
}