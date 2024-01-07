#pragma once
#include"DKJEN/Type/Sprite.h"
#include"DKJEN/Base/ImageLoading.h"
#include"DKJEN/Math/Math.h"
#include"DKJEN/Type/Obj3D.h"
#include"DKJEN/Utilipy/rektyk.h"
#include"DKJEN/Management/FrameManagement.h"
#include"DKJEN/Management/PSOCopileManagement.h"
class seen
{
public:
	void Initialize(TexProeerty  tex);
	void Updet();
	void Draw();

private:
	Sprite* SpriteTex;
	Sprite* SpriteTex2;
};
