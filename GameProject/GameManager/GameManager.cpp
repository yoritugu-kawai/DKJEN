#include "GameManager.h"

void GameManager::Initialize()
{
	iseen_ = new StartSeen;
	iseen_->Initialize();
}

void GameManager::Update()
{
	iseen_->Update(this);
}

void GameManager::Draw()
{
	iseen_->Draw();
}
