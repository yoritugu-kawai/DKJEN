#pragma once
#include"../../DKJEN/Management/TypeManagement.h"
#include"IEnemyState.h"
#include"EnemyLeaveh.h"
#include "EnemyApproach.h"
#include"EnemyBullet.h"
#include"../Collder/Collder.h"
#include"../Player/Player.h"
class Enemy :public Collider
{
public:
	void Intiailize( const std::string& directoryPath, const std::string& filename, Coordinate pos);
	void Update(Player* player);
	void Draw(TexProeerty  tex, CameraProjection pro);
	Vector3 GetWorldPosition() override;
	Coordinate GetPos() { return  pos_; };
	Vector3 GetVelocty() { return Velocty_; }
	void SetPos(Vector3 pos) { pos_.translate = pos; };
	void OnCollision() override;
	void StateChange(IEnemyState* iEnemyState) { enemyState = iEnemyState; }
	//const EnemyBullet GetBullets() const { return bullet; }
private:
	Obj3D* obj3d_;
	Coordinate pos_;
	const float speed = -0.05f;
	Vector3 Velocty_ = { 0.0f, 0.0f, speed };
	//Coordinate bulletPos_;
	Coordinate bulletpos_;
	IEnemyState* enemyState = nullptr;
	EnemyBullet* bullet;
	bool isAlive_ = true;
};
