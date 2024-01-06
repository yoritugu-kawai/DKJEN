#pragma once
#include"Obj3D.h"
#include"../Math/Math.h"
#include"../Base/DxCommon.h"

#include"../Base/PaticlePSO.h"
#include"../Base/ImageLoading.h"
#include<fstream>
#include<sstream>
#include"../Base/ImageLoading.h"
#include"../ko/CreateMaterial.h"
#include"../ko/Mesh.h"
#include"../ko/Instancing.h"
class Particle3D {
public:

	//コンストラクタ
	Particle3D();

	//初期化
	//Initializeも兼ねているよ
	//void CreateObject(const std::string& directoryPath,const std::string& fileName);


	static Particle3D* Create(const std::string& directoryPath, const std::string& fileName);


private:
#pragma region モデルの読み込み関係の関数
	//モデルデータの読み込み
	ModelData LoadObjectFile(const std::string& directoryPath, const std::string& fileName);

	//mtlファイルの読み込み
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& fileName);

#pragma endregion

public:
	//描画
	void Draw(Transform transform);


	//デストラクタ
	~Particle3D();




public:
	//アクセッサのまとめ

	//透明度の変更
	void SetColor(Vector4 color) {
		this->color_ = color;
	}

	void SetTransparency(float transparency) {
		this->color_.w = transparency;
	}
	//アクセッサのまとめ
	void SetBlendMode(int32_t blendmode) {
		blendModeNumber_ = blendmode;
	}




private:
	//頂点リソースを作る
	//頂点バッファビューを作成する
	//頂点リソースにデータを書き込む



	//頂点データ
	std::unique_ptr<Mesh> mesh_ = nullptr;

	std::unique_ptr<Transformation> transformation_ = nullptr;


	//マテリアル用のリソースを作る
	std::unique_ptr<CreateMaterial> material_ = nullptr;


	//Lighting用
	std::unique_ptr<CreateDirectionalLight> directionalLight_ = nullptr;

	//インスタンシングの数
	static const int32_t instanceCount_ = 10;
	ComPtr<ID3D12Resource>instancingResource_ = nullptr;
	TransformationMatrix* instancingData_ = nullptr;

	//SRVの作成
	D3D12_SHADER_RESOURCE_VIEW_DESC instancingSrvDesc{};

	//インスタンシング
	std::unique_ptr<Instancing> instancing_ = nullptr;

	uint32_t textureHandle_ = 0;

	//色関係のメンバ変数
	Vector4 color_;


	//デフォルトはα加算
	int32_t blendModeNumber_ = 1;





	//TextureManagerを参考にする
	static std::list<ModelData> modelInformationList_;


};
