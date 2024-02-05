#pragma once
#include"../../DKJEN/Management/TypeManagement.h"
#include"../Collder/Collder.h"
#include"../Player/Player.h"
class EnemyBullet :public Collider
{
public:
	void Intiailize(Coordinate pos);
	void Updet( Coordinate pos, Player* player);
	void Draw(CameraOperation pro);
	static const int32_t kLifeTime = 60 * 5;
	bool IsDead() const { return isDead_; }
	Coordinate GetPos() { return pos_; }
	void OnCollision() override;
	Vector3 GetWorldPosition() override;
private:
	Obj3D* obj3d_;
	Coordinate pos_;
	int shot_ = 0;
	//速度

	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
	TexProeerty tex;
	Vector3 velocity_;
};


