#include "StartSeen.h"

void StartSeen::Initialize()
{
	sprite_ = new Sprite;
	uint32_t tex = TexManager::LoadTexture("resource/tex.png");
	sprite_->Initialize(tex);
}

void StartSeen::Update(GameManager* gameManager)
{
	if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
 		gameManager->ChangeState(new PlaySeen);
	}
}

void StartSeen::Draw()
{
	sprite_->Draw({ 100.0f,100.0f,1 }, { 0,0,0 }, pos_, {0.0f,1.0f,1.0f,1.0f});
}
