#pragma once
#include"DxCommon.h"
#include"../Shader/LightCompileShader.h"

class PaticlePSO
{
public:
	static PaticlePSO* GetInstance();

	//PSO

	static void CreatePSO();
	static void Release();
	static PSO GetPSO() { return PaticlePSO::GetInstance()->pso_; }
private:
	//
	static void ShapePSO();
	HRESULT hr;//

	PSO pso_;
};
