#pragma once
#include"../../DKJEN/Management/TypeManagement.h"
#include"../../DKJEN/Utilipy/Input.h"
class Player
{
public:
	void Initialize(TexProeerty  tex, const std::string& filename, ImGguiTransfrom transfrom);
	void Update();
	void Draw();
private:
	Obj3D* obj3D;
	ImGguiTransfrom transfrom_;
};
