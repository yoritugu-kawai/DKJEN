#pragma once
#include"../../DKJEN/Management/TypeManagement.h"
#include"../Collder/Collder.h"
class Bullet :public Collider
{
public:
	void Intiailize(Coordinate pos, const Vector3& velocuty);
	void Updet();
	void Draw(CameraOperation pro);
	static const int32_t kLifeTime = 60 * 5;
	bool IsDead() const { return isDead_; }
	void OnCollision() override;
	Vector3 GetWorldPosition() override;
private:
	Obj3D* obj3d_;
	Coordinate pos_;
	int shot_ = 0;
	//速度
	Vector3 velocuty_;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
	TexProeerty tex;
};


