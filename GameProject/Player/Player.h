#pragma once
#include"../../DKJEN/Management/TypeManagement.h"
class Player
{
public:
	void Intiailize(TexProeerty  tex, const std::string& directoryPath, const std::string& filename, ImGguiTransfrom pos);
	void Updet();
	void Draw(CameraProjection pro);

private:
	Obj3D* obj3d_;
	ImGguiTransfrom pos_;
};



