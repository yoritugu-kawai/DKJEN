#include "Particle.h"
static uint32_t modelIndex;
std::list<ModelData> Particle3D::modelInformationList_{};
static uint32_t descriptorSizeSRV_ = 0u;

Particle3D::Particle3D() {

}



//モデルデータの読み込み
ModelData Particle3D::LoadObjectFile(const std::string& directoryPath, const std::string& fileName) {
	//1.中で必要となる変数の宣言
	ModelData modelData;
	//位置
	std::vector<Vector4> positions;
	//法線
	std::vector<Vector3> normals;
	//テクスチャ座標
	std::vector<Vector2> texcoords;
	//ファイルから読んだ1行を格納するもの
	std::string line;


	//2.ファイルを開く
	std::ifstream file(directoryPath + "/" + fileName);
	assert(file.is_open());

	

	while (std::getline(file, line)) {
		std::string identifier;
		std::istringstream s(line);
		//先頭の識別子を読む
		s >> identifier;

		//identifierに応じた処理
		if (identifier == "v") {
			Vector4 position;
			//ex).  v 「1.0000」 「1.0000」 「-0.0000」
			s >> position.x >> position.y >> position.z;
			position.z *= -1.0f;
			position.w = 1.0f;
			positions.push_back(position);
		}
		else if (identifier == "vt") {
			Vector2 texcoord;
			s >> texcoord.x >> texcoord.y;
			texcoord.y = 1.0f - texcoord.y;
			texcoords.push_back(texcoord);
		}
		else if (identifier == "vn") {
			Vector3 normal;
			s >> normal.x >> normal.y >> normal.z;
			normal.z *= -1.0f;
			normals.push_back(normal);
		}
		else if (identifier == "f") {
			//面は三角形限定。その他は未対応
			VertexData triangle[3];
			for (int32_t faceVertex = 0; faceVertex < 3; ++faceVertex) {
				std::string vertexDefinition;
				s >> vertexDefinition;
				//頂点の要素へのINdexは「位置/uv/法線」で格納されているので、分解してindexを取得する
				std::istringstream v(vertexDefinition);
				uint32_t elementIndices[3];


				for (int32_t element = 0; element < 3; ++element) {
					std::string index;
					// 「/」区切りでインデックスを読んでいく
					std::getline(v, index, '/');
					elementIndices[element] = std::stoi(index);


				}
				
				Vector4 position = positions[elementIndices[0] - 1];
				Vector2 texcoord = texcoords[elementIndices[1] - 1];
				Vector3 normal = normals[elementIndices[2] - 1];
			

				triangle[faceVertex] = { position,texcoord,normal };



			}
			
			modelData.vertices.push_back(triangle[2]);
			modelData.vertices.push_back(triangle[1]);
			modelData.vertices.push_back(triangle[0]);

		}
		else if (identifier == "mtllib") {
			//materialTemplateLibraryファイルの名前を取得する
			std::string materialFileName;
			s >> materialFileName;
			
			modelData.material = LoadMaterialTemplateFile(directoryPath, materialFileName);
		}


	}





	//4.ModelDataを返す
	return modelData;
}

//mtlファイルを読む関数
MaterialData Particle3D::LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& fileName) {

#pragma region 
	//構築するMaterialData
	MaterialData materialData;
	//ファイルから読んだ1行を格納するもの
	std::string line;

#pragma endregion



#pragma region
	std::ifstream file(directoryPath + "/" + fileName);
	//開かなかったら止める
	assert(file.is_open());

#pragma endregion




#pragma region  
	while (std::getline(file, line)) {
		std::string identifier;
		std::istringstream s(line);
		s >> identifier;

		
		if (identifier == "map_Kd") {
			std::string textureFileName;
			s >> textureFileName;
			//連結してファイルパスにする
			materialData.textureFilePath = directoryPath + "/" + textureFileName;

		}



	}

#pragma endregion

	//4.MaterialDataを返す

	return materialData;



}



Particle3D* Particle3D::Create(const std::string& directoryPath, const std::string& fileName) {
	//新たなModel型のインスタンスのメモリを確保
	Particle3D* particle3D = new Particle3D();

	//すでにある場合はリストから取り出す
	for (ModelData modelData : modelInformationList_) {
		if (modelData.name == fileName) {



			////マテリアル用のリソースを作る。今回はcolor1つ分のサイズを用意する
			particle3D->material_ = std::make_unique<CreateMaterial>();
			particle3D->material_->Initialize();



			//テクスチャの読み込み
			particle3D->textureHandle_ = TextureManager::GetInstance()->LoadTexture(modelData.material.textureFilePath);


			//頂点リソースを作る
			particle3D->mesh_ = std::make_unique<Mesh>();
			particle3D->mesh_->Initialize(modelData.vertices);

			//Instancing
			//Transformationいらなかったっす
			particle3D->instancing_ = std::make_unique<Instancing>();
			particle3D->instancing_->Initialize();


			//Lighting
			particle3D->directionalLight_ = std::make_unique<CreateDirectionalLight>();
			particle3D->directionalLight_->Initialize();




			//初期は白色
			//モデル個別に色を変更できるようにこれは外に出しておく
			particle3D->color_ = { 1.0f,1.0f,1.0f,1.0f };

			return particle3D;


		}
	}

	//モデルの読み込み
	ModelData modelDataNew = particle3D->LoadObjectFile(directoryPath, fileName);
	modelDataNew.name = fileName;
	modelInformationList_.push_back(modelDataNew);



	////マテリアル用のリソースを作る。今回はcolor1つ分のサイズを用意する
	particle3D->material_ = std::make_unique<CreateMaterial>();
	particle3D->material_->Initialize();


	//テクスチャの読み込み
	particle3D->textureHandle_ = TextureManager::GetInstance()->LoadTexture(modelDataNew.material.textureFilePath);


	//頂点リソースを作る
	particle3D->mesh_ = std::make_unique<Mesh>();
	particle3D->mesh_->Initialize(modelDataNew.vertices);



	//Instancing
	//Transformationいらなかったっす
	particle3D->instancing_ = std::make_unique<Instancing>();
	particle3D->instancing_->Initialize();

	//Lighting
	particle3D->directionalLight_ = std::make_unique<CreateDirectionalLight>();
	particle3D->directionalLight_->Initialize();





	//初期は白色
	//モデル個別に色を変更できるようにこれは外に出しておく
	particle3D->color_ = { 1.0f,1.0f,1.0f,1.0f };

	return particle3D;

}



//描画
void Particle3D::Draw(Transform transform) {
	ID3D12GraphicsCommandList* commandList = DxCommon::GetInstance()->GetCommandList();
	
	material_->SetInformation(color_);

	//書き込むためのデータを書き込む
	//頂点データをリソースにコピ


	instancing_->SetGraphicsCommand();

	PSOProperty pso_ = Paticle::GetInstance()->GetPSO().Texture;
	//コマンドを積む
	commandList->SetPipelineState(pso_.GraphicsPipelineState);
	commandList->SetGraphicsRootSignature(pso_.rootSignature);


	mesh_->GraphicsCommand();

	//CBVを設定する
	material_->GraphicsCommand();

	//Transformationいらなかったっす
	instancing_->GraphicsCommand();


	//SRVのDescriptorTableの先頭を設定。2はrootParameter[2]である

	if (textureHandle_ != 0) {
		TextureManager::GraphicsCommand(textureHandle_);

	}


	//Light
	directionalLight_->GraphicsCommand();

	//DrawCall
	mesh_->DrawCall(instanceCount_);


}

