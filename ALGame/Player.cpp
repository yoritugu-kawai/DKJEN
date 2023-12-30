#include "Player.h"

void Player::Initialize()
{




	PSOCopileManagement::Set();
	ImageLoading* imageLoading = new ImageLoading;
	imageLoading->Initiluze();
	TexProeerty tex2 = imageLoading->LoadTexture("resource/Player.png");
	

	SpriteTex = new Sprite;
	SpriteTex->Initialize(tex2);
	

	obj3D[0] = new Obj3D;
	obj3D[0]->Initialize(tex2, "Player.obj");

	obj3D[1] = new Obj3D;
	obj3D[1]->Initialize(tex2, "Player.obj");

	obj3D[2] = new Obj3D;
	obj3D[2]->Initialize(tex2, "Player.obj");

	obj3D[3] = new Obj3D;
	obj3D[3]->Initialize(tex2, "Player.obj");
	
	
	
	for (int i = 0; i < 4; i++) {
		imGui3D[i].scale = { 0.5f, 0.5f, 0.5f };
		imGui3D[i].rotate = { 0.0f, 0.0f, 0.0f };


	}
	imGui3D[0].translate = { 0.0f, -1.0f, 3.0f };
	imGui3D[0].color = { 0.0f,0.0f,1.0f,1.0f };
	imGui3D[0].scale = { 0.5f, 0.5f, 0.5f };

	imGui3D[1].translate = { 0.0f, -1.0f, 8.0f };
	imGui3D[1].color = { 1.0f,0.0f,0.0f,1.0f };
	imGui3D[1].scale = { 0.5f, 0.5f, 0.5f };

	imGui3D[2].translate = { 0.0f, -1.0f, 3.0f };
	imGui3D[2].color = { 0.0f,0.2f,2.5f,1.0f };
	imGui3D[2].scale = { 0.2f, 0.2f, 0.2f };

	imGui3D[3].translate = { 0.0f, -1.0f, 8.0f };
	imGui3D[3].color = { 0.0f,0.0f,0.0f,1.0f };
	imGui3D[3].scale = { 0.2f, 0.2f, 0.2f };

}

void Player::Updet()
{
	if (Input::GetInstance()->PushKey(DIK_A)) {
		imGui3D[0].translate.x -= 0.05f;
	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		imGui3D[0].translate.x += 0.05f;
	}


	imGui3D[2].translate.z += 0.1f;
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		shot = 0;
	}
	if (shot == 1) {

		imGui3D[2].translate = imGui3D[0].translate;
	}
	if (imGui3D[2].translate.z > 15) {
		shot = 1;
	}


	imGui3D[1].translate.x += enemySpeed;
	imGui3D[3].translate = imGui3D[1].translate;
	if (imGui3D[1].translate.x > -3) {
		enemySpeed = enemySpeed * -1;
	}
	if (imGui3D[1].translate.x < 3) {
		enemySpeed = enemySpeed * -1;
	}
}

void Player::Draw()
{
	ImGui::Begin("3D");
	ImGui::ColorEdit4("color", (float*)&imGui3D[0].color);
	ImGui::SliderFloat3("scale", &imGui3D[0].scale.x, -0.0f, 5.0f);
	ImGui::SliderFloat3("rotate", &imGui3D[0].rotate.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("translate", &imGui3D[0].translate.x, -5.0f, 5.0f);
	ImGui::End();

	for (int i = 0; i < 4; i++)
	{
		obj3D[i]->Draw(imGui3D[i].scale, imGui3D[i].rotate, imGui3D[i].translate, imGui3D[i].color);
	}
}

void Player::Release()
{
	for (int i = 0; i < 4; i++)
	{
		obj3D[i]->Release();
		delete obj3D[i];
	}
	PSOCopileManagement::Release();
	SpriteTex->Release();
	delete SpriteTex;
}
