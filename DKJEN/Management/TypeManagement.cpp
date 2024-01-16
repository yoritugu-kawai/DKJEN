#include "TypeManagement.h"
TypeManagement* TypeManagement::GetInstance()
{
	static TypeManagement instance;

	return &instance;
}
void TypeManagement::Initialize()
{
}

void TypeManagement::Draw3DObj()
{
}

void TypeManagement::DrawSprite()
{
}
