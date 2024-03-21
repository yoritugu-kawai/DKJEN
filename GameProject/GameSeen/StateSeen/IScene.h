#pragma once
#include"../../../DKJEN/Utilipy/Input.h"
#include"../../GameManager/GameManager.h"
class GameManager;
class IScene {
public:
	virtual void Initialize() = 0;
	virtual void Update(GameManager* gameManager) = 0;
	virtual void Draw() = 0;

private:
	
};