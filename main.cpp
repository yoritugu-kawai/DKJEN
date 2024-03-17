
#include"DKJEN/Base/WinApp.h"
#include"DKJEN/Base/ImageLoading.h"

#include"DKJEN/Math/Math.h"


#include"DKJEN/Utilipy/rektyk.h"

#include"DKJEN/WorldTransform/WorldTransform.h"
#include"DKJEN/CameraProjection/CameraProjection.h"

#include"DKJEN/Management/TypeManagement.h"
#include "DKJEN/Management/FrameManagement.h"
#include"DKJEN/Management/PSOCopileManagement.h"

#include"GameProject/Player/Player.h"
const wchar_t Title[] = { L"ド根性エンジン" };


//static D3DResourceLeaker leaker;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp::Initialize(Title);
	DxCommon::Initialize();
	ImguiManager::Initialize();
	Input::Initialize();
	
	PSOCopileManagement::Set();

	
	ImageLoading::Initiluze();
	CameraData* cameraData = new CameraData;
	cameraData->Create();




	WorldTransform* worldTransform = new WorldTransform;

	worldTransform->Create();

	
	

	Player* player_ = new Player;

	player_->Initialize();
	//座標
	Coordinate timePos_;
	timePos_.scale = { 1.0f,1.0f,1.0f };
	timePos_.rotate = { 0.0f,0.0f,0.0f };
	timePos_.translate = { 0.0f,0.0f,0.0f };
	timePos_.color = { 1.0f,1.0f,1.0f,1.0f };
	//　メインループ
	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		FrameManagement::BeginFrame();
		
		//最初

		//////
		//　ゲーム処理
		//////
	

		/*if (Input::GetInstance()->PushKeyPressed(DIK_A)) {
			uint32_t tex = ImageLoading::LoadTexture("resource/uvChecker.png");
		}
*/

		player_->Update();

		//////
		//　ゲーム処理
		//////
		
		//////
		//　　描画処理
		//////
		player_->Draw();
		//////
		//　　描画処理
		//////
	
		
		//終わり
		FrameManagement::EndFrame();
	}

	/*
	*************************
	*********   解放  *******
	*************************
	*/
	
	
	
	PSOCopileManagement::Release();

	ImguiManager::Release();
	DxCommon::Release();


	return 0;
}
