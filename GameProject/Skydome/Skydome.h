#pragma once
#include"../../DKJEN/Management/TypeManagement.h"
class Skydome
{
public:
	
	void Intiailize(TexProeerty  tex, const std::string& directoryPath, const std::string& filename);
	void Update();
	void Draw(CameraProjection pro);
private:
	Obj3D* obj3d_;
	Coordinate pos_;
};
