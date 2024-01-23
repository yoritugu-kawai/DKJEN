#pragma once
#include"../../DKJEN/Management/TypeManagement.h"
#include"IEnemyState.h"
#include"EnemyLeaveh.h"
#include "EnemyApproach.h"
class Enemy
{
public:
	void Intiailize(TexProeerty  tex, const std::string& directoryPath, const std::string& filename, Coordinate pos);
	void Update();
	void Draw(CameraProjection pro);
	Coordinate GetPos() { return  pos_; };
	Vector3 GetVelocty() { return Velocty_; }
	void SetPos(Vector3 pos) { pos_.translate = pos; };

	void StateChange(IEnemyState* iEnemyState) { enemyState = iEnemyState; }
private:
	Obj3D* obj3d_;
	Coordinate pos_;
	const float speed = -0.05f;
	Vector3 Velocty_ = { 0.0f, 0.0f, speed };
	//Coordinate bulletPos_;
	IEnemyState* enemyState = nullptr;
};
