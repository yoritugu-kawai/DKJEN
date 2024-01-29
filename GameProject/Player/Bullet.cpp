#include "Bullet.h"
#include"../../DKJEN/Utilipy/Input.h"
void Bullet::Intiailize(Coordinate pos, const Vector3& velocuty)
{
	pos_ = pos;
	ImageLoading* imageLoading = new ImageLoading;
	imageLoading->Initiluze();
	tex = imageLoading->LoadTexture("GameResource/Bullet.png");
	
	obj3d_ = new Obj3D;
	obj3d_->Initialize("GameResource", "Bullet.obj");

	velocuty_ = velocuty;
	steCollisionAttribute(kCollisionAttributePlayer);
	steCollisionMask(~kCollisionAttributePlayer);
}
Vector3 Bullet::GetWorldPosition() {
	Vector3 result = pos_.translate;
		/*
	{
		this->pos_.matWorld.m[3][0],
		this->pos_.matWorld.m[3][1],
		this->pos_.matWorld.m[3][2]
	};*/
	return result;
}

void Bullet::Updet()
{
	pos_.translate = Add(pos_.translate, velocuty_);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
	pos_.UpdateMatrix();
}

void Bullet::Draw(CameraProjection pro)
{

	if (isDead_ == false) {
		obj3d_->Draw(pos_.scale, pos_.rotate, pos_.translate, pos_.color, pro,tex );
	}
}

void Bullet::OnCollision()
{
	isDead_ = true;
}
