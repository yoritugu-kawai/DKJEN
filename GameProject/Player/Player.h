#pragma once
#include"../../DKJEN/Management/TypeManagement.h"
#include"Bullet.h"
#include"../Collder/Collder.h"
#include"../Collder/CollisionConfig.h"
#include"./../../DKJEN/Utilipy/Input.h"
class Player :public Collider
{
public:
	~Player();
	void Intiailize(TexProeerty  tex,const std::string& directoryPath, const std::string& filename, const std::string& directoryPath2, const std::string& filename2, Coordinate pos);
	void Update(CameraProjection pro);
	void Attack();
	void GetMouse(CameraProjection viewProjection);
	void Draw(TexProeerty  tex, CameraProjection pro);
	void OnCollision() override;
	Vector3 GetWorldPosition() override;
	Coordinate GetPos() { return pos_; }
	const std::list<Bullet*>& GetBullets() const { return bullets_; }
private:
	Obj3D* obj3d_;
	Obj3D* obj3d2_;
	Coordinate pos_;
	list<Bullet*>bullets_;
	Vector3 rot = { 0.0f,0.0f,0.0f };
	Vector3 trn = { 0.5f,0.0f,0.0f };
	Coordinate bulletPos_;
	//
	Coordinate worldTransform3DReticle_;
	// 2Dレティクル用スプライト
	Sprite* sprite2DReticle_ = nullptr;
	Coordinate ReticlePos ;
	Vector3 positionReticle;
	
	//
	int sta = 0;
	int tim = 0;
	XINPUT_STATE joyState;
	const float kCharacterSpeed = 0.2f;
};



