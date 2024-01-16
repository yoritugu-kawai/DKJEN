#include "Player.h"

void Player::Initialize(TexProeerty  tex, const std::string& filename, ImGguiTransfrom transfrom)
{
	obj3D = new Obj3D;
	obj3D->Initialize(tex,filename);
	transfrom_ = transfrom;
}

void Player::Update()
{
	if (Input::GetInstance()->PushKey(DIK_D)) {
		transfrom_.translate.x += 0.05f;

	}
	if (Input::GetInstance()->PushKey(DIK_A)) {
		transfrom_.translate.x -= 0.05f;
	}

	if (Input::GetInstance()->PushKey(DIK_W)) {
		transfrom_.translate.z += 0.05f;

	}
	if (Input::GetInstance()->PushKey(DIK_S)) {
		transfrom_.translate.z -= 0.05f;

	}
}

void Player::Draw()
{
	obj3D->Draw(transfrom_.scale, transfrom_.rotate, transfrom_.translate, transfrom_.color);
}
