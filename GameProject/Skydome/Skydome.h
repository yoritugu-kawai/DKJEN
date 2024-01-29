#pragma once
#include"../../DKJEN/Management/TypeManagement.h"
class Skydome
{
public:
	
	void Intiailize( const std::string& directoryPath, const std::string& filename);
	void Update();
	void Draw(TexProeerty  tex, CameraProjection pro);
private:
	Obj3D* obj3d_;
	Coordinate pos_;
};
