#include "Particle.h"

//void Particle::Initialize()
//{
//
//	model.vertices.push_back({ v.position = {1.0f,1.0f,0.0f,1.0f}, v.texcoord = {0.0f,0.0f}, v.normal = {0.0f,0.0f,1.0f} });
//	model.vertices.push_back({ v.position = {-1.0f,1.0f,0.0f,1.0f}, v.texcoord = {0.0f,0.0f}, v.normal = {0.0f,0.0f,1.0f} });
//	model.vertices.push_back({ v.position = {1.0f,-1.0f,0.0f,1.0f}, v.texcoord = {0.0f,0.0f}, v.normal = {0.0f,0.0f,1.0f} });
//	model.vertices.push_back({ v.position = {1.0f,-1.0f,0.0f,1.0f}, v.texcoord = {0.0f,0.0f}, v.normal = {0.0f,0.0f,1.0f} });
//	model.vertices.push_back({ v.position = {-1.0f,1.0f,0.0f,1.0f}, v.texcoord = {0.0f,0.0f}, v.normal = {0.0f,0.0f,1.0f} });
//	model.vertices.push_back({ v.position = {-1.0f,-1.0f,0.0f,1.0f}, v.texcoord = {0.0f,0.0f}, v.normal = {0.0f,0.0f,1.0f} });
//	model.material.textureFilePath = "./resource/uvChecker.png";
//}
void Particle::Initialize(TexProeerty  tex)
{



	tex_ = tex;// spriteLoad_->Load("resource/e.png");

	vertexResourceSprite = CreateBufferResource(sizeof(VertexData) * 6);
	transformationMatrixResourceSprote = CreateBufferResource(sizeof(Matrix4x4));
	materialResource = CreateBufferResource(sizeof(UVMaterial));
	indexResourceSprite = CreateBufferResource(sizeof(uint32_t) * 6);
	matrix = MakeIdentity4x4();
}

void  Particle::Vertex()
{

	vertexBufferViewSprite.BufferLocation = vertexResourceSprite->GetGPUVirtualAddress();
	vertexBufferViewSprite.SizeInBytes = sizeof(VertexData) * 6;
	vertexBufferViewSprite.StrideInBytes = sizeof(VertexData);
	//
	indexBufferViewSprite.BufferLocation = instancingResource->GetGPUVirtualAddress();
	indexBufferViewSprite.SizeInBytes = sizeof(uint32_t) * 6;
	indexBufferViewSprite.Format = DXGI_FORMAT_R32_UINT;

	//頂点データ
	vertexResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&VertexDataSprite));
	uint32_t* indexDataSpriite = nullptr;
	indexResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&indexDataSpriite));


	//1枚目
	//左下
	VertexDataSprite[0].position = { transY_ };
	VertexDataSprite[0].texcoord = { 0.0f,1.0f };
	//左上
	VertexDataSprite[1].position = { 0.0f,0.0f,0.0f,1.0f };
	VertexDataSprite[1].texcoord = { 0.0f,0.0f };
	//右下
	VertexDataSprite[2].position = { transXY_ };
	VertexDataSprite[2].texcoord = { 1.0f,1.0f };

	//右上
	VertexDataSprite[3].position = { transX_ };
	VertexDataSprite[3].texcoord = { 1.0f,0.0f };


	indexDataSpriite[0] = 0;  indexDataSpriite[1] = 1; indexDataSpriite[2] = 2;
	indexDataSpriite[3] = 1; indexDataSpriite[4] = 3; indexDataSpriite[5] = 2;


	/////

	const uint32_t kNumInstance = 10;
	instancingResource= CreateBufferResource(sizeof(TransformationMatrix) * kNumInstance);
	TransformationMatrix* instancingData = nullptr;
	instancingResource->Map(0, nullptr, reinterpret_cast<void**>(&instancingData));

	for (uint32_t index = 0; index < kNumInstance; ++index) {

		instancingData[index].WVP = MakeIdentity4x4();
		instancingData[index].World= MakeIdentity4x4();

	}
	Transform transfom[10];
	for (uint32_t i = 0; i < kNumInstance; ++i)
	{
		transfom[i].scale = { 1.0f,1.0f,1.0f };
		transfom[i].rotate = { 0.0f,0.0f,0.0f };
		transfom[i].translate = { i * 0.1f,i * 0.1f,i * 0.1f };
	}

	for (uint32_t i = 0; i < kNumInstance; ++i)
	{
		Matrix4x4 woldMatrix = MakeAffineMatrix(transfom[i].scale, transfom[i].rotate, transfom[i].translate);
		Matrix4x4 woldViewProMatrix = Multiply(woldMatrix, ProjectionMatrix);
		instancingData[i].WVP = woldViewProMatrix;
		instancingData[i].World = woldMatrix;
	}

}
void  Particle::Darw(Vector3 scale, Vector3 rotate, Vector3 translate, Vector4 Color)
{
	matrix = MakeAffineMatrix(scale, rotate, translate);

	UVMaterial* materialDeta = nullptr;
	materialResource->Map(0, nullptr,
		reinterpret_cast<void**>(&materialDeta));
	materialDeta->color = Color;
	Vertex();

	ImGui::Begin("sprite");
	ImGui::Text("uv");
	ImGui::SliderFloat3("t", &uvTranformSprite.translate.x, -4.0f, 4.0f);
	ImGui::SliderFloat3("s", &uvTranformSprite.scale.x, -4.0f, 4.0f);
	ImGui::SliderFloat3("r", &uvTranformSprite.rotate.x, -4.0f, 4.0f);
	ImGui::End();

	Matrix4x4 m2 = MakeAffineMatrix(uvTranformSprite.scale, uvTranformSprite.rotate, uvTranformSprite.translate);
	materialDeta->uvTransform = m2;


	transformationMatrixResourceSprote->Map(0, nullptr, reinterpret_cast<void**>
		(&transformationMatrixDataSprite));
	*transformationMatrixDataSprite = MakeIdentity4x4();

	Matrix4x4 SpriteMatrix = MakeAffineMatrix(transformSprite.scale, transformSprite.rotate, transformSprite.translate);
	Matrix4x4 viewMatrix = MakeIdentity4x4();
	Matrix4x4 projectionMatrix = MakeOrthographicMatrix(0.0f, 0.0f, float(WinApp::GetInstance()->Width()), float(WinApp::GetInstance()->Height()), 0.0f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = Multiply(matrix, Multiply(viewMatrix, projectionMatrix));
	*transformationMatrixDataSprite = worldViewProjectionMatrix;


	//
	PSOProperty pso_ = ParticlePSO::GetInstance()->GetPSO().Texture;
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();


	commandList->SetGraphicsRootSignature(pso_.rootSignature);
	commandList->SetPipelineState(pso_.GraphicsPipelineState);
	commandList->IASetVertexBuffers(0, 1, &vertexBufferViewSprite);
	commandList->IASetIndexBuffer(&indexBufferViewSprite);
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	commandList->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	commandList->SetGraphicsRootDescriptorTable(1, instancingSrvHandleGPU);
	commandList->SetGraphicsRootDescriptorTable(2, tex_.SrvHandleGPU);
	commandList->DrawIndexedInstanced(6, 10, 0, 0, 0);

}

void  Particle::Release()
{
	tex_.Resource->Release();

	vertexResourceSprite->Release();
	indexResourceSprite->Release();
	transformationMatrixResourceSprote->Release();
	materialResource->Release();
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
	device->CreateShaderResourceView(instancingResource.Get(), &instansingSrvDesc, instancingSrvHandleCPU);
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