#include "Player.h"
#include"../../DKJEN/Utilipy/Input.h"

void Player::Intiailize(TexProeerty  tex, const std::string& directoryPath, const std::string& filename, ImGguiTransfrom pos)
{
	//GameResource
	obj3d_ = new Obj3D;
	obj3d_->Initialize(tex, directoryPath, filename);
	pos_ = pos;
}

void Player::Updet()
{
	if (Input::GetInstance()->PushKey(DIK_A)) {
		pos_.translate.x -= 0.05;
	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		pos_.translate.x += 0.05;
	}
}

void Player::Draw(CameraProjection pro)
{
	obj3d_->Draw(pos_.scale, pos_.rotate, pos_.translate, pos_.color, pro);
}
