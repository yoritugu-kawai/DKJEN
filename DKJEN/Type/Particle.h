#pragma once
#include"../Math/Math.h"
#include"../Base/DxCommon.h"
#include"../Base/SpritePSO.h"
#include"../Base/TexturePSO.h"
#include"../Base/LightPSO.h"
#include"../Base/ImageLoading.h"
#include"../Type/Obj3D.h"
#include<fstream>
#include<sstream>
class Particle
{
public:
	void Initialize();
	void Draw();
private:
	ModelData model;
	VertexData v;
};
