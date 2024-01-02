#pragma once
#include"Obj3D.h"
#include"../Base/ImageLoading.h"
class Particle
{
public:
	void Initialize();
	void SRV();
	void Draw();
private:
	ModelData modelData;
	VertexData vertexData;
};


