#include "Particle.h"

void Particle::Initialize()
{

}

void Particle::Draw()
{
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.vertices.push_back({ vertexData.position = {1.0f,1.0f,0.0f,1.0f}, vertexData.texcoord = {0.0f,0.0f},vertexData.normal = {0.0f,0.0f,1.0f} });
	modelData.material.textureFilePath = "./resoures/uvChecker.png";

}
