#pragma once
#include"../StateSeen/IScene.h"
#include"../PlaySeen/PlaySeen.h"

class StartSeen : public IScene {
public:
	void Initialize()override;
	void Update(GameManager* gameManager)override;
	void Draw()override;
private:

};