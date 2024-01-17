
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
	TexProeerty tex2 = imageLoading->LoadTexture("resource/uvChecker.png");
	TexProeerty tex3 = imageLoading->LoadTexture("resource/iras.png");
	CameraProjection pro;
	pro.Initialize();

	Obj3D* obj3D2 = new Obj3D;
	obj3D2->Initialize(tex3, "axis.obj");

	Sprite* SpriteTex = new Sprite;
	SpriteTex->Initialize(tex2);
	Obj3D* obj3D = new Obj3D;
	obj3D->Initialize(tex2,"axis.obj");

	
	

	ImGguiTransfrom imGuiSprite;
	imGuiSprite.scale = { 1.0f,1.0f,1.0f };
	imGuiSprite.rotate = { 0.0f,0.0f,0.0f };
	imGuiSprite.translate = { 0.0f,0.0f,0.0f };
	imGuiSprite.color = { 1.0f, 1.0f, 1.0, 1.0f };

	ImGguiTransfrom imGui3D[1];
	for (int i = 0; i < 1; i++) {
		imGui3D[i].scale = { 0.5f, 0.5f, 0.5f };
		imGui3D[i].rotate = { 0.0f, 0.0f, 0.0f };
		imGui3D[i].translate = { 0.0f, 0.0f, 0.0f };
		imGui3D[i].color = { 1.0f,1.0f,1.0f,1.0f };

	}

	ImGguiTransfrom imGui3;
	for (int i = 0; i < 1; i++) {
		imGui3.scale = { 0.5f, 0.5f, 0.5f };
		imGui3.rotate = { 0.0f, 0.0f, 0.0f };
		imGui3.translate = { 0.0f, 0.0f, 0.0f };
		imGui3.color = { 1.0f,1.0f,1.0f,1.0f };

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

		ImGui::Begin("Sprite");
		ImGui::ColorEdit4("color", (float*)&imGuiSprite.color);
		ImGui::SliderFloat3("scale", &imGuiSprite.scale.x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &imGuiSprite.rotate.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("translate", &imGuiSprite.translate.x, -500.0f, 500.0f);
		ImGui::End();
		
		SpriteTex->Darw(imGuiSprite.scale, imGuiSprite.rotate, imGuiSprite.translate, imGuiSprite.color);
		
//#ifdef _DEBUG
//		ImGui::Begin("a");
//
//		ImGui::End();
//
//#endiftry
	

		
		ImGui::Begin("pro");
	
		ImGui::SliderFloat3("scale", &pro.translate.x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &pro.rotate.x, -10.0f, 10.0f);
		
		ImGui::End();


		ImGui::Begin("3D");
		ImGui::ColorEdit4("color", (float*)&imGui3D[0].color);
		ImGui::SliderFloat3("scale", &imGui3D[0].scale.x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &imGui3D[0].rotate.x, -10.0f, 10.0f);
		ImGui::SliderFloat3("translate", &imGui3D[0].translate.x, -5.0f, 5.0f);
		ImGui::End();

		
		obj3D->Draw(imGui3D[0].scale, imGui3D[0].rotate, imGui3D[0].translate, imGui3D[0].color,pro);
		obj3D2->Draw(imGui3.scale, imGui3.rotate, imGui3.translate, imGui3.color, pro);
		//

	
		
		FrameManagement::EndFrame();
	}

	/*
	*************************
	*********   解放  *******
	*************************
	*/
	
	
	/*delete SpriteTex;
	
	delete obj3D;
	*/
	PSOCopileManagement::Release();

	ImguiManager::Release();
	DxCommon::Release();


	return 0;
}
