
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
	ImageLoading* imageLoading2 = new ImageLoading;
	imageLoading2->Initiluze();
	TexProeerty sta1 = imageLoading->LoadTexture("GameResource/sta2.png");
	TexProeerty sta2= imageLoading->LoadTexture("GameResource/sta1.png");
	TexProeerty texPlayer = imageLoading->LoadTexture("GameResource/Player.png");
	TexProeerty texEnemy = imageLoading->LoadTexture("GameResource/enemy.png");
	TexProeerty texCelestialSphere = imageLoading->LoadTexture("GameResource/uvChecker.png");
	TexProeerty texSprite = imageLoading->LoadTexture("GameResource/anchor.png");
	TexProeerty texEnd = imageLoading2->LoadTexture("GameResource/end.png");
	TexProeerty pphs = imageLoading2->LoadTexture("GameResource/push.png");

	CameraProjection pro;
	pro.Initialize();


	Sprite* SpriteTex = new Sprite;
	SpriteTex->Initialize(sta1);

	Sprite* SpriteTex2 = new Sprite;
	SpriteTex2->Initialize(sta2);
	Sprite* End = new Sprite;
	End->Initialize(sta1);

	Sprite* push = new Sprite;
	push->Initialize(pphs);

	/*Obj3D* obj3D = new Obj3D;
	obj3D->Initialize("GameResource","ro.obj");*/


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
	player_->Intiailize(texSprite,"GameResource", "Player.obj", "GameResource", "ro.obj",playerTransfrom);

	Enemy* enemy_ = new Enemy();
	enemy_->Intiailize( "GameResource", "Player.obj", enemyTransfrom);
	

	Skydome* skydome_ = new Skydome;
	skydome_->Intiailize( "GameResource", "CelestialSphere.obj");
	//Bullet* bullet_ = new Bullet;
	//bullet_->Intiailize();
	CollisionManager* collisionManager_ = new CollisionManager;
	//フラグ
	int nem = 1;
	int sta = 0;
	int tim = 0;
	XINPUT_STATE joyState;
	Coordinate imGuiSprite;
	imGuiSprite.scale = { 4.5f,4.0f,1.0f };
	imGuiSprite.rotate = { 0.0f,0.0f,0.0f };
	imGuiSprite.translate = { 0.0f,0.0f,0.0f };
	imGuiSprite.color = { 1.0f, 1.0f, 1.0, 1.0f };
	//
	Coordinate imGuiSprite2;
	imGuiSprite2.scale = { 4.5f,4.0f,1.0f };
	imGuiSprite2.rotate = { 0.0f,0.0f,0.0f };
	imGuiSprite2.translate = { 0.0f,0.0f,0.0f };
	imGuiSprite2.color = { 1.0f, 1.0f, 1.0, 1.0f };

	Coordinate imGuiSprite3;
	imGuiSprite3.scale = { 4.5f,4.0f,1.0f };
	imGuiSprite3.rotate = { 0.0f,0.0f,0.0f };
	imGuiSprite3.translate = { 0.0f,0.0f,0.0f };
	imGuiSprite3.color = { 1.0f, 1.0f, 1.0, 1.0f };


	Coordinate imGuiSprite4;
	imGuiSprite4.scale = { 4.5f,4.0f,1.0f };
	imGuiSprite4.rotate = { 0.0f,0.0f,0.0f };
	imGuiSprite4.translate = { 0.0f,0.0f,0.0f };
	imGuiSprite4.color = { 1.0f, 1.0f, 1.0, 1.0f };
	Coordinate imGui3D[1];
	for (int i = 0; i < 1; i++) {
		imGui3D[i].scale = { 0.5f, 0.5f, 0.5f };
		imGui3D[i].rotate = { 0.0f, 0.0f, 0.0f };
		imGui3D[i].translate = { 0.0f, 0.0f, 0.0f };
		imGui3D[i].color = { 1.0f,1.0f,1.0f,1.0f };

	}
	int i=0;
	Vector3 rot = { 0.0f,0.0f,0.0f };
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
	

		//
		

		switch (nem)
		{
		case 1:
			Input::GetInstance()->NoneJoyState(joyState);
			
			if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)|| joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
				sta = 1;
				
			}
			if (sta == 1)
			{
				imGuiSprite.translate.x -= 15;
				imGuiSprite2.translate.x += 15;
				tim += 1;
			}
			if (tim == 60)
			{
				sta = 0;

				tim = 0;
				nem = 2;
			}
			if (i == 0) {

			imGuiSprite4.scale.x -= 0.01f;
			}
			if (imGuiSprite4.scale.x >= 1.0f) {
				imGuiSprite4.scale.x -= 0.01f;
			}

			if (imGuiSprite4.scale.x <= 1.0f) {
				i = 1;
				imGuiSprite4.scale.x += 0.01f;
			}



			SpriteTex->Darw(imGuiSprite.scale, imGuiSprite.rotate, imGuiSprite.translate, imGuiSprite.color);
			SpriteTex2->Darw(imGuiSprite2.scale, imGuiSprite2.rotate, imGuiSprite2.translate, imGuiSprite2.color);
			player_->Draw(texPlayer, pro);
			enemy_->Draw(texEnemy, pro);
			push->Darw(imGuiSprite4.scale, imGuiSprite4.rotate, imGuiSprite4.translate, imGuiSprite4.color);
			skydome_->Draw(texCelestialSphere, pro);

			break;
		case 2:
			Input::GetInstance()->NoneJoyState(joyState);

			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
				
				sta = 1;
			}
			

			player_->Update(pro);
			player_->Draw(texPlayer, pro);
			enemy_->Update(player_);
			enemy_->Draw(texEnemy, pro);
			skydome_->Draw(texCelestialSphere, pro);
			ImGui::Begin("pro");

			ImGui::DragFloat3("translate", &pro.translate.x);
			ImGui::DragFloat3("rotate", &pro.rotate.x);

			ImGui::End();
			if (sta == 1)
			{
				pro.translate.z += 0.05f;
				tim += 1;
			}
			if (tim == 600)
			{
				pro.translate.z = -20;
				sta = 0;
				nem = 3;
			}
			break;
		case 3:
			/*nem = 1;*/
			End->Darw(imGuiSprite3.scale, imGuiSprite3.rotate, imGuiSprite3.translate, imGuiSprite3.color);
			break;
		}
		
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
