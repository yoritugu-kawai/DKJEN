#include "EnemyBullet.h"
#include"../../DKJEN/Utilipy/Input.h"
void EnemyBullet::Intiailize(Coordinate pos)
{
	pos_ = pos;
	ImageLoading* imageLoading = new ImageLoading;
	imageLoading->Initiluze();
	 tex = imageLoading->LoadTexture("GameResource/Bullet.png");
	obj3d_ = new Obj3D;
	obj3d_->Initialize( "GameResource", "Bullet.obj");

	

}

void EnemyBullet::Updet(  Coordinate pos,Player*player)
{

	Vector3 PlayerPos_;
	PlayerPos_ = Subract(player->GetWorldPosition(), pos_.translate);
	Vector3 NormalizePlayerPos_= Normalize(PlayerPos_);
	Vector3 NormalizeVelocity_ = Normalize(velocity_);
	velocity_ = SlerpFanc(NormalizeVelocity_, NormalizePlayerPos_, 0.05f);

	float velocityXZ_ = sqrt(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
	float velocityY_ = velocity_.y;
	int time = 240;

	time--;
	pos_.rotate.y = atan2(velocity_.x, velocity_.z);
	pos_.rotate.x = atan2(velocityY_, velocityXZ_);

	pos_.translate = Add(pos_.translate, velocity_);
	if (pos_.translate.z <= -50) {
		pos_.translate = pos.translate;
		time = 0;

	}
	else if(time==0){
		time = 0;
		pos_.translate = pos.translate;
	} 
}

void EnemyBullet::Draw(CameraProjection pro)
{
	if (isDead_ == false) {
		obj3d_->Draw(pos_.scale, pos_.rotate, pos_.translate, pos_.color, pro, tex);
	}
}

void EnemyBullet::OnCollision()
{
	isDead_ = true;
}

Vector3 EnemyBullet::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = pos_.translate.x;
	worldPos.y = pos_.translate.y;
	worldPos.z = pos_.translate.z;
	return worldPos;
}
