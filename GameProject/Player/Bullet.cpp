#include "Bullet.h"

void Bullet::Initialize()
{
	bullet = new Sprite;
	uint32_t tex = ImageLoading::LoadTexture("resource/tex.png");
	bullet->Initialize(tex);

}


void Bullet::Update()
{
	
	pos_.y -= 10;
}

void Bullet::Draw()
{
	bullet->Darw({ 0.1f,0.2f,1 }, { 0,0,0 }, pos_, { 1.0f,0.0f,1.0f,1.0f });
}
