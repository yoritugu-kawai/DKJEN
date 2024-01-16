#include "TypeManagement.h"
TypeManagement* TypeManagement::GetInstance()
{
	static TypeManagement instance;

	return &instance;
}
void TypeManagement::Initialize3DObj()
{
	obj3D = new Obj3D;

}

void TypeManagement::InitializeSprite()
{
	sprite = new Sprite;


}

void TypeManagement::Draw3DObj()
{
}

void TypeManagement::DrawSprite()
{
}
