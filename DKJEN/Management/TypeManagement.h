#pragma once
#include"../Type/Obj3D.h"
#include"../Type/Polygon.h"
#include"../Type/Sphere.h"
#include"../Type/Sprite.h"
#include"../Type/Texture.h"
class TypeManagement
{
public:
	static TypeManagement* GetInstance();
	static void Initialize3DObj();
	static void InitializeSprite();
	static void Draw3DObj();
	static void DrawSprite();
private:
	Obj3D* obj3D;
	Sprite* sprite;
};
