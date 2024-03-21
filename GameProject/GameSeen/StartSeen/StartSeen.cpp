#include "StartSeen.h"

void StartSeen::Initialize()
{
}

void StartSeen::Update(GameManager* gameManager)
{
	if (Input::GetInstance()->PushKeyPressed(DIK_SPACE)) {
		gameManager->ChangeState(new PlaySeen);
	}
}

void StartSeen::Draw()
{
}
