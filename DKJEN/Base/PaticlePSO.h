#pragma once
#include"DxCommon.h"
#include"../Shader/PaticleCompileShader.h"

class Paticle
{
public:
	static Paticle* GetInstance();

	//PSO

	static void CreatePSO();
	static void Release();
	static PSO GetPSO() { return Paticle::GetInstance()->pso_; }
private:
	//
	static void PPso();
	HRESULT hr;//

	PSO pso_;
};
