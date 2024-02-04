
#include"DKJEN/Base/WinApp.h"
#include"DKJEN/Base/ImageLoading.h"

#include"DKJEN/Math/Math.h"


#include"DKJEN/Utilipy/rektyk.h"

#include"DKJEN/CameraProjection/CameraProjection.h"

#include"DKJEN/Management/TypeManagement.h"
#include "DKJEN/Management/FrameManagement.h"
#include"DKJEN/Management/PSOCopileManagement.h"
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

	ImageLoading* imageLoading3 = new ImageLoading;
	imageLoading3->Initiluze();


	TexProeerty texball = imageLoading2->LoadTexture("resource/ball.png");

	/*TexProeerty texNeedle2 = imageLoading3->LoadTexture("resource/p/needle2.png");
	TexProeerty texTime = imageLoading->LoadTexture("resource/p/time.png");*/

	CameraProjection pro;
	pro.Initialize();
	Obj3D* time = new Obj3D;
	time->Initialize("resource", "ball.obj");

	//Obj3D* needle = new Obj3D;
	//needle->Initialize("resource/p", "needle.obj");
	//Obj3D* needle2 = new Obj3D;
	//needle2->Initialize("resource/p", "needle2.obj");


	Coordinate timePos_;
	timePos_.scale = { 1.0f,1.0f,1.0f };
	timePos_.rotate = { 0.0f,0.0f,0.0f };
	timePos_.translate = { 0.0f,0.0f,0.0f };
	timePos_.color = { 1.0f,1.0f,1.0f,1.0f };

	Vector3 needleRotate_ = { 0.0f,0.0f,0.0f };
	Vector3 needleRotate2_ = { 0.0f,0.0f,0.0f };
	//　メインループ
	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		FrameManagement::BeginFrame();
		pro.Update();
		//最初

		//////
		//　ゲーム処理
		//////
		needleRotate_.z -= 0.01f;
		needleRotate2_.z -= 0.001f;
		//////
		//　ゲーム処理
		//////
		
	
	
		//////
		//　　描画処理
		//////

		time->Draw(timePos_.scale, timePos_.rotate, timePos_.translate, timePos_.color, pro, texball);
		/*needle->Draw(timePos_.scale, needleRotate_, timePos_.translate, timePos_.color, pro, texNeedle);
		needle2->Draw(timePos_.scale, needleRotate2_, timePos_.translate, timePos_.color, pro, texNeedle2);*/
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
