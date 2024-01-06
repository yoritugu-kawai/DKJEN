#include "TextureManager.h"



static uint32_t descriptorSizeSRV_ = 0u;
static uint32_t descriptorSizeRTV_ = 0u;
static uint32_t descriptorSizeDSV_ = 0u;
static uint32_t textureIndex;


static DirectX::ScratchImage mipImages_[TextureManager::TEXTURE_MAX_AMOUNT_];
static D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc[TextureManager::TEXTURE_MAX_AMOUNT_];

//コンストラクタ
TextureManager::TextureManager() {

}

TextureManager* TextureManager::GetInstance() {
	
	static TextureManager instance;
	return &instance;
}





const D3D12_RESOURCE_DESC TextureManager::GetResourceDesc(uint32_t textureHandle) {
	//テクスチャの情報を取得
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc = textureInformation_[textureHandle].resource_->GetDesc();

	return resourceDesc;
}


//初期化
void TextureManager::Initilalize() {
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();//
	
	CoInitializeEx(0, COINIT_MULTITHREADED);
	descriptorSizeSRV_ =  device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	descriptorSizeRTV_ =  device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	descriptorSizeDSV_ =  device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	textureIndex = 0;
}


D3D12_CPU_DESCRIPTOR_HANDLE TextureManager::GetCPUDescriptorHandle(ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index) {
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += (descriptorSize * index);
	return handleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::GetGPUDescriptorHandle(ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index) {
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += (descriptorSize * index);
	return handleGPU;
}





//統合させた関数
uint32_t TextureManager::LoadTexture(const std::string& filePath) {
	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();//
	
	for (int i = 0; i < TEXTURE_MAX_AMOUNT_; i++) {
		//同じテクスチャがあった場合そのテクスチャハンドルを返す
		if (TextureManager::GetInstance()->textureInformation_[i].name_ == filePath) {
			return TextureManager::GetInstance()->textureInformation_[i].handle_;
		}
	}



	
	++textureIndex;


	
	if (textureIndex > 127) {
		textureIndex = 0;
	}

	TextureManager::GetInstance()->textureInformation_[textureIndex].name_ = filePath;
	//テクスチャハンドル
	TextureManager::GetInstance()->textureInformation_[textureIndex].handle_ = textureIndex;

	mipImages_[textureIndex] = LoadTextureData(filePath);

	const DirectX::TexMetadata& metadata = mipImages_[textureIndex].GetMetadata();

	TextureManager::GetInstance()->textureInformation_[textureIndex].resource_ = CreateTextureResource(metadata);
	UploadTextureData(TextureManager::GetInstance()->textureInformation_[textureIndex].resource_.Get(), mipImages_[textureIndex]);


	srvDesc[textureIndex].Format = metadata.format;
	srvDesc[textureIndex].Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	//2Dテクスチャ
	srvDesc[textureIndex].ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc[textureIndex].Texture2D.MipLevels = UINT(metadata.mipLevels);
	
	ID3D12DescriptorHeap* srvDescriptorHeap = DxCommon::GetInstance()->GetsrvDescriptorHeap();

	TextureManager::GetInstance()->textureInformation_[textureIndex].srvHandleCPU_ = GetCPUDescriptorHandle(srvDescriptorHeap, descriptorSizeSRV_, textureIndex);
	TextureManager::GetInstance()->textureInformation_[textureIndex].srvHandleGPU_ = GetGPUDescriptorHandle(srvDescriptorHeap, descriptorSizeSRV_, textureIndex);

	//SRVの生成
	//DirectXSetup::GetInstance()->GetDevice()->CreateShaderResourceView(TextureManager::GetInstance()->textureResource_[textureIndex].Get(), &srvDesc[textureIndex], TextureManager::GetInstance()->textureSrvHandleCPU_[textureIndex]);
	
	device->CreateShaderResourceView(
		TextureManager::GetInstance()->textureInformation_[textureIndex].resource_.Get(), 
		&srvDesc[textureIndex], TextureManager::GetInstance()->textureInformation_[textureIndex].srvHandleCPU_);
	



	return textureIndex;
}
	


#pragma region テクスチャの読み込み


#pragma region 上のLoadTextureにまとめた
//Textureを読み込むためのLoad関数
//1.TextureデータそのものをCPUで読み込む
DirectX::ScratchImage TextureManager::LoadTextureData(const std::string& filePath) {
	
	//テクスチャファイルを読んでプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = ConvertString(filePath);
	//ここで問題
	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));
	
	//ミップマップの作成
	//ミップマップ...元画像より小さなテクスチャ群
	DirectX::ScratchImage mipImages{};
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(hr));

	//ミップマップ月のデータを返す
	return mipImages;
}

//2.DirectX12のTextureResourceを作る
ComPtr<ID3D12Resource> TextureManager::CreateTextureResource(const DirectX::TexMetadata& metadata) {
	ComPtr<ID3D12Resource> resource = nullptr;
	
	//1.metadataを基にResourceの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	//Textureの幅
	resourceDesc.Width = UINT(metadata.width);
	//Textureの高さ
	resourceDesc.Height = UINT(metadata.height);
	//mipmapの数
	resourceDesc.MipLevels = UINT16(metadata.mipLevels);
	//奥行き or 配列Textureの配列数
	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);
	//TextureのFormat
	resourceDesc.Format = metadata.format;
	//サンプリングカウント
	resourceDesc.SampleDesc.Count = 1;
	//Textureの次元数。普段使っているのは2次元
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);

	//2.利用するHeapの設定
	//利用するHeapの設定。非常に特殊な運用。02_04exで一般的なケース版がある
	D3D12_HEAP_PROPERTIES heapProperties{};
	//細かい設定を行う
	heapProperties.Type = D3D12_HEAP_TYPE_CUSTOM;
	//WriteBackポリシーでCPUアクセス可能
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	//プロセッサの近くに配置
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;

	ID3D12Device* device = DxCommon::GetInstance()->GetDevice();//

	

	//3.Resourceを生成する
	
	HRESULT hr = device->CreateCommittedResource(
		&heapProperties,					//Heapの設定
		D3D12_HEAP_FLAG_NONE,				//Heapの特殊な設定
		&resourceDesc,						//Resourceの設定
		D3D12_RESOURCE_STATE_GENERIC_READ,	//初回のResourceState。データの転送を受け入れられるようにする
		nullptr,							//Clear最適値。使わないのでnullptr
		IID_PPV_ARGS(&resource));			//作成するResourceポインタへのポインタ
	assert(SUCCEEDED(hr));

	return resource;


}

//3.TextureResourceに1で読んだデータを転送する
//書き換え
void TextureManager::UploadTextureData(
	ComPtr<ID3D12Resource> texture, 
	const DirectX::ScratchImage& mipImages) {

	//Meta情報を取得
	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();
	//全MipMapについて
	for (size_t mipLevel = 0; mipLevel < metadata.mipLevels; ++mipLevel) {
		//MipMapLevelを指定して各Imageを取得
		const DirectX::Image* img = mipImages.GetImage(mipLevel, 0, 0);
		//Textureに転送
		HRESULT hr = texture->WriteToSubresource(
			UINT(mipLevel),
			nullptr,				//全領域へコピー
			img->pixels,			//元データアドレス
			UINT(img->rowPitch),	//1ラインサイズ
			UINT(img->slicePitch)	//1枚サイズ
		);

		assert(SUCCEEDED(hr));
	}



}



#pragma endregion



#pragma endregion


void TextureManager::GraphicsCommand(uint32_t texHandle) {
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();

	commandList->SetGraphicsRootDescriptorTable(
		2, TextureManager::GetInstance()->textureInformation_[texHandle].srvHandleGPU_);

}

void TextureManager::Release() {
	
	
	//ゲーム終了時にはCOMの終了処理を行っておく
	CoUninitialize();
}


//コンストラクタ
TextureManager::~TextureManager() {

}