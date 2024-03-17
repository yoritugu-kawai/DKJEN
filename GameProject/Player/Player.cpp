#include "Player.h"

void Player::Initialize()
{
	player = new Sprite;
	uint32_t tex = ImageLoading::LoadTexture("resource/tex.png");
	player->Initialize(tex);
	pos_ = { 500.0f,360.0f,0.0f };
	bullet_ = new Bullet;
	bullet_->Initialize();
	isShot = 0;
}

void Player::Update()
{
	if (Input::GetInstance()->PushKey(DIK_A)) {
		pos_.x -= 5;
		
	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		pos_.x += 5;
	}

	if (Input::GetInstance()->PushKey(DIK_W)) {
		pos_.y -= 5;
	}
	if (Input::GetInstance()->PushKey(DIK_S)) {
		pos_.y += 5;
	}
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		isShot = 1;
	}
	if (!isShot) 
	bullet_->SetPos(pos_);
	if (isShot) 
	bullet_->Update();
}

void Player::Draw()
{
	player->Darw({ 0.1f,0.2f,1 }, { 0,0,0 }, pos_, { 1.0f,1.0f,1.0f,1.0f });
	if (isShot) {
		bullet_->Draw();
	}
}
