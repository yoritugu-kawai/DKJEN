#include "Particle.h"

void Particle::Initialize()
{

	model.vertices.push_back({ v.position = {1.0f,1.0f,0.0f,1.0f}, v.texcoord = {0.0f,0.0f}, v.normal = {0.0f,0.0f,1.0f} });
	model.vertices.push_back({ v.position = {-1.0f,1.0f,0.0f,1.0f}, v.texcoord = {0.0f,0.0f}, v.normal = {0.0f,0.0f,1.0f} });
	model.vertices.push_back({ v.position = {1.0f,-1.0f,0.0f,1.0f}, v.texcoord = {0.0f,0.0f}, v.normal = {0.0f,0.0f,1.0f} });
	model.vertices.push_back({ v.position = {1.0f,-1.0f,0.0f,1.0f}, v.texcoord = {0.0f,0.0f}, v.normal = {0.0f,0.0f,1.0f} });
	model.vertices.push_back({ v.position = {-1.0f,1.0f,0.0f,1.0f}, v.texcoord = {0.0f,0.0f}, v.normal = {0.0f,0.0f,1.0f} });
	model.vertices.push_back({ v.position = {-1.0f,-1.0f,0.0f,1.0f}, v.texcoord = {0.0f,0.0f}, v.normal = {0.0f,0.0f,1.0f} });
	model.material.textureFilePath = "./resource/uvChecker.png";
}

void Particle::Draw()
{
}
