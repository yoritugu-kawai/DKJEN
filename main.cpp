
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
	Texture* tex = new Texture;
	tex->Initialize(tex2);

	Sprite* SpriteTex = new Sprite;
	SpriteTex->Initialize(tex2);

	///ImGui
	ImGguiTransfrom imGuiTextur;
	for (int i = 0; i < 2; i++) {
		imGuiTextur.matrix = MakeIdentity4x4();
		imGuiTextur.scale = { 1,1,1 };
		imGuiTextur.rotate = { 0,0,0 };
		imGuiTextur.translate = { 0,0,0 };
		imGuiTextur.color = { 1.0f,1.0f,1.0f,1.0f };

	}

	ImGguiTransfrom imGuiSprite;
	imGuiSprite.matrix = MakeIdentity4x4();
	imGuiSprite.scale = { 1.0f,1.0f,1.0f };
	imGuiSprite.rotate = { 0.0f,0.0f,0.0f };
	imGuiSprite.translate = { 0.0f,0.0f,0.0f };
	imGuiSprite.color = { 1.0f, 1.0f, 1.0, 1.0f };
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

		imGuiTextur.matrix = MakeAffineMatrix(imGuiTextur.scale, imGuiTextur.rotate, imGuiTextur.translate);
		tex->Draw(imGuiTextur.matrix, imGuiTextur.color);




		ImGui::Begin("Sprite");
		ImGui::ColorEdit3("color", (float*)&imGuiSprite.color);
		ImGui::SliderFloat3("scale", &imGuiSprite.scale.x, -0.0f, 5.0f);
		ImGui::SliderFloat3("rotate", &imGuiSprite.rotate.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("translate", &imGuiSprite.translate.x, -500.0f, 500.0f);
		ImGui::End();
		imGuiSprite.matrix = MakeAffineMatrix(imGuiSprite.scale, imGuiSprite.rotate, imGuiSprite.translate);

		SpriteTex->Darw(imGuiSprite.matrix, imGuiSprite.color);
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
	
	PSOCopileManagement::Release();

	ImguiManager::Release();
	DxCommon::Release();


	return 0;
}
