
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

	
	
	Sprite* SpriteTex = new Sprite;
	SpriteTex->Initialize(tex3);
	Player* player_ = new Player;
	player_->Initialize();

	ImGguiTransfrom imGui3D;

	imGui3D.scale = { 0.5f, 0.5f, 0.5f };
    imGui3D.rotate = { 0.0f, 0.0f, 0.0f };
	imGui3D.translate = { 0.0f, -1.0f, 3.0f };
	imGui3D.color = { 0.0f,0.0f,1.0f,1.0f };
	int nem=1;
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
			if (Input::GetInstance()->PushKeyPressed(DIK_1)) {
				nem = 2;
			}
			break;
		case 2:
			//更新
			player_->Updet();

			//////描画
			//

			player_->Draw();
			if (Input::GetInstance()->PushKeyPressed(DIK_1)) {
				nem = 3;
			}
			break;
		case 3:
			if (Input::GetInstance()->PushKeyPressed(DIK_1)) {
				nem = 1;
			}
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
	
	
	SpriteTex->Release();
	delete SpriteTex;
	player_->Release();
	delete player_;
	
	
	PSOCopileManagement::Release();

	ImguiManager::Release();
	DxCommon::Release();


	return 0;
}
