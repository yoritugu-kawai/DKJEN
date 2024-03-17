#pragma once
#include"../../DKJEN/Type/Sprite.h"
#include"../../DKJEN/Utilipy/Input.h"
#include"Bullet.h"
class Player
{
public:
	void Initialize();
	void Update();
	void Draw();


private:
	Bullet* bullet_;
	Sprite* player;
	Vector3 pos_;
	bool isShot;
};
