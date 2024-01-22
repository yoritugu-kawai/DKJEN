#pragma once
#include"../../DKJEN/Management/TypeManagement.h"
#include"Bullet.h"
class Player
{
public:
	void Intiailize(TexProeerty  tex, const std::string& directoryPath, const std::string& filename, Coordinate pos);
	void Update();
	void Draw(CameraProjection pro);

private:
	Obj3D* obj3d_;
	Coordinate pos_;
	list<Bullet*>bullets_;
	Coordinate bulletPos_;
	
};



