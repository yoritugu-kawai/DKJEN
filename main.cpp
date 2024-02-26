
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

	
	ImageLoading::Initiluze();






	/*TexProeerty texNeedle2 = imageLoading3->LoadTexture("resource/p/needle2.png");
	TexProeerty texTime = imageLoading->LoadTexture("resource/p/time.png");*/

	CameraOperation pro;
	pro.Initialize();
	Obj3D* time = new Obj3D;
	time->Initialize("resource", "ball.obj");
	uint32_t texball = ImageLoading::LoadTexture("resource/uvChecker.png");
	Sprite* sprite_ = new Sprite;
	sprite_->Initialize(texball);



	//Particle* particle = new Particle;

	//particle->Initialize(texball);
	Coordinate imGuiParticle;
	imGuiParticle.scale = { 1.0f,1.0f,1.0f };
	imGuiParticle.rotate = { 0.0f,0.0f,0.0f };
	imGuiParticle.translate = { 0.0f,0.0f,0.0f };
	imGuiParticle.color = { 1.0f, 1.0f, 1.0, 1.0f };

	//座標
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
	

		if (Input::GetInstance()->PushKeyPressed(DIK_A)) {
			uint32_t tex = ImageLoading::LoadTexture("resource/uvChecker.png");
			int a=0;
		}
#ifdef USE_IMGUI

		ImGui::Begin("buildTest");
		ImGui::End();


#endif // USE_IMGUI



		//////
		//　ゲーム処理
		//////
		ImGui::Begin("Camera");

		ImGui::DragFloat3("translate", &pro.translate.x);
		ImGui::DragFloat3("rotate", &pro.rotate.x);

		ImGui::End();
	
		//////
		//　　描画処理
		//////

		time->Draw(timePos_.scale, timePos_.rotate, timePos_.translate, timePos_.color, pro);
		sprite_->Darw(timePos_.scale, timePos_.rotate, timePos_.translate, timePos_.color);
		/*particle->Darw(timePos_.scale, timePos_.rotate, timePos_.translate, timePos_.color); */
	
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
