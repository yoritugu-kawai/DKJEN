#include "GameManager.h"

void GameManager::Initialize()
{
	iseen = new PlaySeen;
	iseen->Initialize();
}

void GameManager::Update()
{
	iseen->Update(this);
}

void GameManager::Draw()
{
	iseen->Draw();
}
