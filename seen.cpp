#include "seen.h"

void seen::Initialize(TexProeerty  tex, TexProeerty  tex2)
{
	SpriteTex = new Sprite();
	SpriteTex2 = new Sprite();

	SpriteTex->Initialize(tex);
	SpriteTex2->Initialize(tex2);
	imGuiSprite.scale = { 1.0f,1.0f,1.0f };
	imGuiSprite.rotate = { 0.0f,0.0f,0.0f };
	imGuiSprite.translate = { 0.0f,0.0f,0.0f };
	imGuiSprite.color = { 1.0f, 1.0f, 1.0, 1.0f };
}

void seen::Updet()
{




}

void seen::Draw()
{

	SpriteTex->Darw(imGuiSprite.scale, imGuiSprite.rotate, imGuiSprite.translate, imGuiSprite.color);
	SpriteTex2->Darw(imGuiSprite.scale, imGuiSprite.rotate, imGuiSprite.translate, imGuiSprite.color);
}
