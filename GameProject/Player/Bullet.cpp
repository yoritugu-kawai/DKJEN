#include "Bullet.h"
#include"../../DKJEN/Utilipy/Input.h"
void Bullet::Intiailize(Coordinate pos, const Vector3& velocuty)
{
	pos_ = pos;
	ImageLoading* imageLoading = new ImageLoading;
	imageLoading->Initiluze();
	TexProeerty tex = imageLoading->LoadTexture("GameResource/Bullet.png");
	obj3d_ = new Obj3D;
	obj3d_->Initialize(tex,"GameResource", "Bullet.obj");

	velocuty_ = velocuty;
	
}

void Bullet::Updet()
{
	pos_.translate = Add(pos_.translate, velocuty_);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void Bullet::Draw(CameraProjection pro)
{
	obj3d_->Draw(pos_.scale, pos_.rotate, pos_.translate, pos_.color, pro);
}
