#pragma once
#include <d3d12.h>
#include <string>
#include <array>
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/SpritePSO.h"
#include"../Base/TexturePSO.h"
#include"../Base/LightPSO.h"
#include"../Base/ImageLoading.h"
#include<fstream>
#include<sstream>

//テクスチャに関するクラス
class TextureManager {
private:
	//コンストラクタ
	TextureManager();

	//コンストラクタ
	~TextureManager();

public:
	static TextureManager* GetInstance();


	//コピーコンストラクタ禁止
	TextureManager(const TextureManager& textureManager) = delete;

	//代入演算子を無効にする
	TextureManager& operator=(const TextureManager& textureManager) = delete;

	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);
	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);


	ComPtr<ID3D12DescriptorHeap> GetSrvDescriptorHeap() {
		return  m_srvDescriptorHeap_;
	}
public:
	
	//初期化
	static void Initilalize();

	//統合させた関数
	//インデックスを返すからマイナスはありえない。
	//uintにしたほうが良いよね
	static uint32_t LoadTexture(const std::string& filePath);

	static void GraphicsCommand(uint32_t texHandle);

	//解放
	void Release();



	/// テクスチャの情報を取得
	const D3D12_RESOURCE_DESC GetResourceDesc(uint32_t textureHandle);

private:



#pragma region テクスチャの読み込み
	//Textureデータを読む
	//1.TextureデータそのものをCPUで読み込む
	static DirectX::ScratchImage LoadTextureData(const std::string& filePath);

	//2.DirectX12のTextureResourceを作る
	static ComPtr<ID3D12Resource> CreateTextureResource(const DirectX::TexMetadata& metadata);

	//3.TextureResourceに1で読んだデータを転送する
	//void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages,ID3D12Device* device,ID3D12GraphicsCommandList* commandList);
	static void UploadTextureData(ComPtr<ID3D12Resource> texture, const DirectX::ScratchImage& mipImages);


#pragma endregion
	

public:
		static const int TEXTURE_MAX_AMOUNT_ = 128;

		ComPtr<ID3D12DescriptorHeap> m_srvDescriptorHeap_ = nullptr;

	struct TextureInformation {

		//リソース
		ComPtr<ID3D12Resource> resource_= nullptr;

		//画像読み込み
		D3D12_CPU_DESCRIPTOR_HANDLE srvHandleCPU_ = {};
		D3D12_GPU_DESCRIPTOR_HANDLE srvHandleGPU_ = {};

		//読み込んだテクスチャの名前
		std::string name_={};

		//テクスチャハンドル
		uint32_t handle_ = 0;
	};

private:


	//構造体版
	//array...stdの配列版。その名前の通り配列だよね
	std::array<TextureInformation, TEXTURE_MAX_AMOUNT_> textureInformation_{};



};