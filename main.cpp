
#include"DKJEN/Base/WinApp.h"
#include"DKJEN/Base/ImageLoading.h"

#include"DKJEN/Math/Math.h"


#include"DKJEN/Type/Polygon.h"
#include"DKJEN/Type/Sprite.h"
#include"DKJEN/Type/Texture.h"
#include"DKJEN/Type/Sphere.h"
#include"DKJEN/Type/Obj3D.h"
#include"DKJEN/Utilipy/rektyk.h"

#include "DKJEN/Management/FrameManagement.h"
#include"DKJEN/Management/PSOCopileManagement.h"
#include"ALGame/Player.h"
#include"seen.h"
const wchar_t Title[] = { L"ド根性エンジン" };


struct Transfrom4
{
	Vector4 lefe;
	Vector4  top;
	Vector4 right;
	Vector4 color;

};

static D3DResourceLeaker leaker;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp::Initialize(Title);
	DxCommon::Initialize();

	ImguiManager::Initialize();
	Input::Initialize();

	PSOCopileManagement::Set();
	ImageLoading* imageLoading = new ImageLoading;
	imageLoading->Initiluze();
	TexProeerty tex3 = imageLoading->LoadTexture("resource/iras.png");

	TexProeerty tex4 = imageLoading->LoadTexture("resource/stat.png");
	TexProeerty tex5 = imageLoading->LoadTexture("resource/stat1.png");
	TexProeerty tex6 = imageLoading->LoadTexture("resource/crla.png");
	TexProeerty tex7 = imageLoading->LoadTexture("resource/crla2.png");
	
	Sprite* SpriteTex=new Sprite;
	Sprite* SpriteTex2= new Sprite;
	Sprite* SpriteTex3 = new Sprite;
	Sprite* SpriteTex4 = new Sprite;
	SpriteTex->Initialize(tex4);
	SpriteTex2->Initialize(tex5);
	SpriteTex3->Initialize(tex6);
	SpriteTex4->Initialize(tex7);
	Player* player_ = new Player;
	player_->Initialize();
	seen* Sen= new seen();
	Sen->Initialize(tex4, tex5);
	ImGguiTransfrom imGui3D;

	imGui3D.scale = { 0.5f, 0.5f, 0.5f };
    imGui3D.rotate = { 0.0f, 0.0f, 0.0f };
	imGui3D.translate = { 0.0f, -1.0f, 3.0f };
	imGui3D.color = { 0.0f,0.0f,1.0f,1.0f };
	int nem=1;
	ImGguiTransfrom imGuiSprite;
	imGuiSprite.scale = { 2.5f,2.0f,1.0f };
	imGuiSprite.rotate = { 0.0f,0.0f,0.0f };
	imGuiSprite.translate = { 0.0f,0.0f,0.0f };
	imGuiSprite.color = { 1.0f, 1.0f, 1.0, 1.0f }; 
	ImGguiTransfrom imGuiSprite2;
	imGuiSprite2.scale = { 2.5f,2.0f,1.0f };
	imGuiSprite2.rotate = { 0.0f,0.0f,0.0f };
	imGuiSprite2.translate = { 0.0f,0.0f,0.0f };
	imGuiSprite2.color = { 1.0f, 1.0f, 1.0, 1.0f };
	ImGguiTransfrom imGuiSprite3;
	imGuiSprite3.scale = { 2.5f,2.0f,1.0f };
	imGuiSprite3.rotate = { 0.0f,0.0f,0.0f };
	imGuiSprite3.translate = { 0.0f,0.0f,0.0f };
	imGuiSprite3.color = { 1.0f, 1.0f, 1.0, 1.0f };
	ImGguiTransfrom imGuiSprite4;
	imGuiSprite4.scale = { 2.5f,2.0f,1.0f };
	imGuiSprite4.rotate = { 0.0f,0.0f,0.0f };
	imGuiSprite4.translate = { 0.0f,0.0f,0.0f };
	imGuiSprite4.color = { 1.0f, 1.0f, 1.0, 1.0f };
	int tim = 0;
	int sta = 0;
	int t = 10000;
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

		
	
		switch (nem)
		{
		case 1:
			if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
				sta = 1;
				imGuiSprite3.translate.x = 0;
				imGuiSprite4.translate.x = 0;
			}
			if (sta==1)
			{
				imGuiSprite.translate.x -= 15;
				imGuiSprite2.translate.x += 15;
				tim += 1;
			}
			if (tim==60)
			{
				sta = 0;
				
				tim = 0;
				nem = 2;
			}
			SpriteTex->Darw(imGuiSprite.scale, imGuiSprite.rotate, imGuiSprite.translate, imGuiSprite.color);
			SpriteTex2->Darw(imGuiSprite2.scale, imGuiSprite2.rotate, imGuiSprite2.translate, imGuiSprite2.color);
			Sen->Draw();
			player_->Draw();
			break;
		case 2:
			//更新
			
		
			//////描画
			//
			player_->Updet(t);
			player_->Draw();
			if(player_->Getdes()==1)
			 {
				nem = 3;
			}
			break;
		case 3:
			if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
				sta = 1;
				imGuiSprite.translate.x = 0;
				imGuiSprite2.translate.x = 0;
				player_->stedes(0);
			}
			if (sta == 1)
			{
				imGuiSprite3.translate.x -= 15;
				imGuiSprite4.translate.x += 15;
				tim += 1;
			}
			if (tim == 60)
			{
				sta = 0;
				
				tim = 0;
				nem = 1;
				
			}
			SpriteTex->Darw(imGuiSprite.scale, imGuiSprite.rotate, imGuiSprite.translate, imGuiSprite.color);
			SpriteTex2->Darw(imGuiSprite2.scale, imGuiSprite2.rotate, imGuiSprite2.translate, imGuiSprite2.color);
			
			SpriteTex3->Darw(imGuiSprite3.scale, imGuiSprite3.rotate, imGuiSprite3.translate, imGuiSprite.color);
			SpriteTex4->Darw(imGuiSprite4.scale, imGuiSprite4.rotate, imGuiSprite4.translate, imGuiSprite.color);
			break;
		case 4:
			if (Input::GetInstance()->PushKeyPressed(DIK_1)) {
				nem = 1;
			}
			break;
		}
		
		
	
		//////
		//　ゲーム処理
		//////

		
		FrameManagement::EndFrame();
	}

	/*
	*************************
	*********   解放  *******
	*************************
	*/
	
	
	/*SpriteTex->Release();
	delete SpriteTex;*/
	player_->Release();
	delete player_;
	
	
	PSOCopileManagement::Release();

	ImguiManager::Release();
	DxCommon::Release();


	return 0;
}
