#pragma once
#include"../../DKJEN/Management/TypeManagement.h"

class Bullet
{
public:
	void Intiailize(Coordinate pos, const Vector3& velocuty);
	void Updet();
	void Draw(CameraProjection pro);
	static const int32_t kLifeTime = 60 * 5;
	bool IsDead() const { return isDead_; }
private:
	Obj3D* obj3d_;
	Coordinate pos_;
	int shot_ = 0;
	//速度
	Vector3 velocuty_;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
};


