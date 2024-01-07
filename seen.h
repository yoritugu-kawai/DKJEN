#pragma once

#include"DKJEN/Base/WinApp.h"
#include"DKJEN/Base/ImageLoading.h"

#include"DKJEN/Math/Math.h"


#include"DKJEN/Type/Polygon.h"
#include"DKJEN/Type/Sprite.h"

#include"DKJEN/Type/Sphere.h"
#include"DKJEN/Type/Obj3D.h"
#include"DKJEN/Utilipy/rektyk.h"

#include "DKJEN/Management/FrameManagement.h"
#include"DKJEN/Management/PSOCopileManagement.h"
class seen
{
public:
	void Initialize(TexProeerty  tex, TexProeerty  tex2);
	void Updet();
	void Draw();

private:
	Sprite* SpriteTex;
	Sprite* SpriteTex2;
	ImGguiTransfrom imGuiSprite;
	
};
