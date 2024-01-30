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
	void Intiailize(TexProeerty  tex,const std::string& directoryPath, const std::string& filename, Coordinate pos);
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
	Coordinate pos_;
	list<Bullet*>bullets_;
	
	Coordinate bulletPos_;
	//
	Coordinate worldTransform3DReticle_;
	// 2Dレティクル用スプライト
	Sprite* sprite2DReticle_ = nullptr;
	Coordinate ReticlePos ;
	Vector3 positionReticle;
	
	//
	XINPUT_STATE joyState;
	const float kCharacterSpeed = 0.2f;
};



