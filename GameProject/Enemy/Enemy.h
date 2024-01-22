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
	void SetPos(Coordinate pos);

	void StateChange(IEnemyState* iEnemyState) { enemyState = iEnemyState; }
private:
	Obj3D* obj3d_;
	Coordinate pos_;
	
	//Coordinate bulletPos_;
	IEnemyState* enemyState = nullptr;
};
