
#include"DKJEN/Base/WinApp.h"
#include"DKJEN/Base/ImageLoading.h"

#include"DKJEN/Math/Math.h"


#include"DKJEN/Utilipy/rektyk.h"

#include"DKJEN/CameraProjection/CameraProjection.h"

#include"DKJEN/Management/TypeManagement.h"
#include "DKJEN/Management/FrameManagement.h"
#include"DKJEN/Management/PSOCopileManagement.h"

#include"GameProject/Skydome/Skydome.h"
#include"GameProject/Enemy/Enemy.h"
#include"GameProject/Player/Bullet.h"
#include"GameProject/Player/Player.h"
#include"GameProject/Collder/CollisionManager.h"
const wchar_t Title[] = { L"ド根性エンジン" };


//static D3DResourceLeaker leaker;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp::Initialize(Title);
	DxCommon::Initialize();
	ImguiManager::Initialize();
	Input::Initialize();
	
	PSOCopileManagement::Set();
	ImageLoading* imageLoading = new ImageLoading;
	imageLoading->Initiluze();
	TexProeerty texIro = imageLoading->LoadTexture("resource/iras.png");
	TexProeerty texUV = imageLoading->LoadTexture("resource/uvChecker.png");
	TexProeerty texPlayer = imageLoading->LoadTexture("GameResource/Player.png");
	TexProeerty texEnemy = imageLoading->LoadTexture("GameResource/enemy.png");
	TexProeerty texCelestialSphere = imageLoading->LoadTexture("GameResource/uvChecker.png");
	TexProeerty texSprite = imageLoading->LoadTexture("GameResource/anchor.png");
	CameraProjection pro;
	pro.Initialize();


	Sprite* SpriteTex = new Sprite;
	SpriteTex->Initialize(texIro);

	Sprite* SpriteTex2 = new Sprite;
	SpriteTex2->Initialize(texUV);

	/*Obj3D* obj3D = new Obj3D;
	obj3D->Initialize(texUV,"resource","axis.obj");*/


	//ゲームキャラクター
	Coordinate playerTransfrom;
	playerTransfrom.scale = { 0.5f, 0.5f, 0.5f };
	playerTransfrom.rotate = { 0.0f, 0.0f, 0.0f };
	playerTransfrom.translate = { 0.0f, 0.0f, 0.0f };
	playerTransfrom.color = { 1.0f,1.0f,1.0f,1.0f };

	Coordinate enemyTransfrom;
	enemyTransfrom.scale = { 0.5f, 0.5f, 0.5f };
	enemyTransfrom.rotate = { 0.0f, 0.0f, 0.0f };
	enemyTransfrom.translate = { 0.0f, 0.0f, 10.0f };
	enemyTransfrom.color = { 1.0f,1.0f,1.0f,1.0f };

	Player* player_ = new Player;
	player_->Intiailize( "GameResource", "Player.obj",playerTransfrom, texSprite);

	Enemy* enemy_ = new Enemy();
	enemy_->Intiailize( "GameResource", "Player.obj", enemyTransfrom);
	

	Skydome* skydome_ = new Skydome;
	skydome_->Intiailize( "GameResource", "CelestialSphere.obj");
	//Bullet* bullet_ = new Bullet;
	//bullet_->Intiailize();
	CollisionManager* collisionManager_ = new CollisionManager;

	Coordinate imGuiSprite;
	imGuiSprite.scale = { 1.0f,1.0f,1.0f };
	imGuiSprite.rotate = { 0.0f,0.0f,0.0f };
	imGuiSprite.translate = { 0.0f,0.0f,0.0f };
	imGuiSprite.color = { 1.0f, 1.0f, 1.0, 1.0f };
	//
	Coordinate imGuiSprite2;
	imGuiSprite2.scale = { 1.0f,1.0f,1.0f };
	imGuiSprite2.rotate = { 0.0f,0.0f,0.0f };
	imGuiSprite2.translate = { 50.0f,50.0f,50.0f };
	imGuiSprite2.color = { 1.0f, 1.0f, 1.0, 1.0f };

	Coordinate imGui3D[1];
	for (int i = 0; i < 1; i++) {
		imGui3D[i].scale = { 0.5f, 0.5f, 0.5f };
		imGui3D[i].rotate = { 0.0f, 0.0f, 0.0f };
		imGui3D[i].translate = { 0.0f, 0.0f, 0.0f };
		imGui3D[i].color = { 1.0f,1.0f,1.0f,1.0f };

	}
	
	//　メインループ
	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		FrameManagement::BeginFrame();
		//////
		//　ゲーム処理
		//////

		
		pro.Update();


		/*ImGui::Begin("Sprite");
		ImGui::ColorEdit4("color", (float*)&imGuiSprite.color);
		ImGui::SliderFloat3("scale", &imGuiSprite.scale.x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &imGuiSprite.rotate.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("translate", &imGuiSprite.translate.x, -500.0f, 500.0f);
		ImGui::End();
		
		SpriteTex->Darw(imGuiSprite.scale, imGuiSprite.rotate, imGuiSprite.translate, imGuiSprite.color);

		ImGui::Begin("Sprite2");
		ImGui::ColorEdit4("color", (float*)&imGuiSprite2.color);
		ImGui::SliderFloat3("scale", &imGuiSprite2.scale.x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &imGuiSprite2.rotate.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("translate", &imGuiSprite2.translate.x, -500.0f, 500.0f);
		ImGui::End();
		SpriteTex2->Darw(imGuiSprite2.scale, imGuiSprite2.rotate, imGuiSprite2.translate, imGuiSprite2.color);*/
		
//#ifdef _DEBUG
//		ImGui::Begin("a");
//
//		ImGui::End();
//
//#endiftry
	

		//
		ImGui::Begin("pro");
	
		ImGui::DragFloat3("translate", &pro.translate.x);
		ImGui::DragFloat3("rotate", &pro.rotate.x);
		
		ImGui::End();


		/*ImGui::Begin("3D");
		ImGui::ColorEdit4("color", (float*)&imGui3D[0].color);
		ImGui::SliderFloat3("scale", &imGui3D[0].scale.x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &imGui3D[0].rotate.x, -10.0f, 10.0f);
		ImGui::SliderFloat3("translate", &imGui3D[0].translate.x, -5.0f, 5.0f);
		ImGui::End();

		
		obj3D->Draw(imGui3D[0].scale, imGui3D[0].rotate, imGui3D[0].translate, imGui3D[0].color,pro);*/
		//

		
		player_->Update(pro);
		player_->Draw(texPlayer, pro);
		enemy_->Update(player_);
		enemy_->Draw(texEnemy, pro);
		skydome_->Draw(texCelestialSphere, pro);


		collisionManager_->CollideClear();
	   // enemy_->GetBullets();
		const std::list<Bullet*>& playerBullets = player_->GetBullets();
		collisionManager_->ColliderPush(player_);
		collisionManager_->ColliderPush(enemy_);
		for (Bullet* bullet : playerBullets) {
			collisionManager_->ColliderPush(bullet);
		}
		/*for (EnemyBullet* bullet : enemyBullets) {
			collisionManager_->ColliderPush(bullet);
		}*/
		collisionManager_->CheckAllCollisions();
	
		
		FrameManagement::EndFrame();
	}

	/*
	*************************
	*********   解放  *******
	*************************
	*/
	player_->~Player();
	
	/*delete SpriteTex;
	
	delete obj3D;
	*/
	PSOCopileManagement::Release();

	ImguiManager::Release();
	DxCommon::Release();


	return 0;
}
