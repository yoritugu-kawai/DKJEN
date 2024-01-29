#pragma once
#include"../../DKJEN/Management/TypeManagement.h"
#include"Bullet.h"
#include"../Collder/Collder.h"
#include"../Collder/CollisionConfig.h"

class Player :public Collider
{
public:
	~Player();
	void Intiailize( const std::string& directoryPath, const std::string& filename, Coordinate pos);
	void Update();
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
	
};



