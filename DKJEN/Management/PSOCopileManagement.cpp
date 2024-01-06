#include"PSOCopileManagement.h"

//PSOCopileManagement PSOCopileManagement::GetInstance()
//{
//	static PSOCopileManagement instance;
//
//	return &instance;
//}

PSOCopileManagement* PSOCopileManagement::GetInstance()
{
	static PSOCopileManagement instance;
	return &instance;
}

void PSOCopileManagement::Set()
{
	TextureCompileShader::DXC();
	PolygonCompileShader::DXC();
	SpriteCompileShader::DXC();
	LightCompileShader::DXC();
	PaticleCompileShader::DXC();

	TextureCompileShader::ShaderCompile();
	PolygonCompileShader::ShaderCompile();
	SpriteCompileShader::ShaderCompile();
	LightCompileShader::ShaderCompile();
	PaticleCompileShader::ShaderCompile();
	
	TexturePSO::CreatePSO();
	PolygonPSO::CreatePSO();
	SpritePSO::CreatePSO();
	LightPSO::CreatePSO();
	Paticle::CreatePSO();

}

void PSOCopileManagement::Release()
{
	TextureCompileShader::Release();
	PolygonCompileShader::Release();
	SpriteCompileShader::Release();
	LightCompileShader::Release();
	PaticleCompileShader::Release();

	TexturePSO::Release();
	PolygonPSO::Release();
	SpritePSO::Release();
	LightPSO::Release();
	Paticle::Release();

}
