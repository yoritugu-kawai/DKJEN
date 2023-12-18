
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
	TexProeerty tex2 = imageLoading->LoadTexture("resource/uvChecker.png");
	TexProeerty tex3 = imageLoading->LoadTexture("resource/iras.png");
	
	Texture* tex = new Texture;
	tex->Initialize(tex2);

	Sprite* SpriteTex = new Sprite;
	SpriteTex->Initialize(tex3);
	Obj3D* obj3D = new Obj3D;
	obj3D->Initialize(tex2);


	Sphere* sphere_ = new Sphere;
	sphere_->Initialize(tex2);
	///ImGui
	ImGguiTransfrom imGuiTextur;
	for (int i = 0; i < 2; i++) {
		imGuiTextur.scale = { 1,1,1 };
		imGuiTextur.rotate = { 0,0,0 };
		imGuiTextur.translate = { 0,0,0 };
		imGuiTextur.color = { 1.0f,1.0f,1.0f,1.0f };

	}

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

	ImGguiTransfrom imGuiSphere[1];
	for (int i = 0; i < 1; i++) {
		imGuiSphere[i].scale = { 1.0f, 1.0f, 1.0f };
		imGuiSphere[i].rotate = { 0.0f, 4.7f, 0.0f };
		imGuiSphere[i].translate = { 0.0f, 0.0f, 0.0f };
		imGuiSphere[i].color = { 1.0f,1.0f,1.0f,1.0f };

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

		ImGui::Begin("Texture");
		ImGui::ColorEdit3("color", (float*)&imGuiTextur.color);
		ImGui::SliderFloat3("scale", &imGuiTextur.scale.x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &imGuiTextur.rotate.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("translate", &imGuiTextur.translate.x, -5.0f, 5.0f);
		ImGui::End();


		tex->Draw(imGuiTextur.scale, imGuiTextur.rotate, imGuiTextur.translate, imGuiTextur.color);




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
//#endif
		ImGui

		ImGui::Begin("3D");
		ImGui::ColorEdit4("color", (float*)&imGui3D[0].color);
		ImGui::SliderFloat3("scale", &imGui3D[0].scale.x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &imGui3D[0].rotate.x, -10.0f, 10.0f);
		ImGui::SliderFloat3("translate", &imGui3D[0].translate.x, -5.0f, 5.0f);
		ImGui::End();

		
		obj3D->Draw(imGui3D[0].scale, imGui3D[0].rotate, imGui3D[0].translate, imGui3D[0].color);
		//

		ImGui::Begin("sphere");
		ImGui::ColorEdit3("color", (float*)&imGuiSphere[0].color);
		ImGui::SliderFloat3("scale", &imGuiSphere[0].scale.x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &imGuiSphere[0].rotate.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("translate", &imGuiSphere[0].translate.x, -5.0f, 5.0f);
		ImGui::End();


		imGuiSphere[0].rotate.y += 0.02f;
		sphere_->Draw(imGuiSphere[0].scale, imGuiSphere[0].rotate, imGuiSphere[0].translate);
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
	
	tex->Release();
	SpriteTex->Release();
	delete SpriteTex;
	obj3D->Release();
	delete obj3D;
	sphere_->Release();
	PSOCopileManagement::Release();

	ImguiManager::Release();
	DxCommon::Release();


	return 0;
}
