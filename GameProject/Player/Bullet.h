#pragma once
#include"../../DKJEN/Type/Sprite.h"
class Bullet
{
public:
	void Initialize();
	void Update();
	void Draw();
	Vector3 GetPos() { return pos_; }
	void SetPos(Vector3 pos) { pos_ = pos; }
private:
	Sprite* bullet;
	Vector3 pos_;
};
