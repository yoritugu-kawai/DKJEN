#include "Bullet.h"

void Bullet::Initialize()
{
	sprite_ = new Sprite;
	uint32_t tex = ImageLoading::LoadTexture("resource/tex.png");
	sprite_->Initialize(tex);
	speed_ = 10;
	isShot_ = false;

}


void Bullet::Update()
{
	isShot_ = true;
	pos_.y -= speed_;
	if (pos_.y<=-10) {
		pos_ = pos_;
		isShot_ = false;
	}
	ImGui::Begin("bullet");
	ImGui::SliderFloat3("bu", &pos_.y, 0, 5);
	ImGui::End();
}

void Bullet::Draw()
{
	sprite_->Draw({ 0.1f,0.2f,1 }, { 0,0,0 }, pos_, { 1.0f,0.0f,1.0f,1.0f });
}
