#pragma once
#include"../../DKJEN/Type/Sprite.h"
#include"../../DKJEN/Utilipy/Input.h"
#include"Bullet.h"
class Player
{
public:
	void Initialize();
	void Input();
	void Update();
	void Draw();


private:
	Bullet* bullet_;
	Sprite* sprite_;
	Vector3 pos_;
	bool isShot_;
};
