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
	static void Initialize();
	static void Draw3DObj();
	static void DrawSprite();
private:

};
