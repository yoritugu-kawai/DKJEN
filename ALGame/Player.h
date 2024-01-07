#pragma once
#include"../DKJEN/Type/Sprite.h"
#include"../DKJEN/Base/ImageLoading.h"
#include"../DKJEN/Math/Math.h"
#include"../DKJEN/Type/Obj3D.h"
#include"../DKJEN/Utilipy/rektyk.h"
#include"../DKJEN/Management/FrameManagement.h"
#include"../DKJEN/Management/PSOCopileManagement.h"
class Player
{
public:
	void Initialize();
	void Updet(int t);
	void Draw();
	void Release();
	int Getdes() { return  des; };
	void stedes(int dess);
private:
	Sprite* SpriteTex;
	Obj3D* obj3D[4];
	ImGguiTransfrom imGui3D[4];
	float enemySpeed = 0.05f;
	int shot = 1;
	int des = 0;
};
