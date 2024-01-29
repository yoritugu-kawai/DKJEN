#include "Enemy.h"

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos = pos_.translate;
	//{
	//	this->pos_.matWorld.m[3][0],
	//	this->pos_.matWorld.m[3][1],
	//	this->pos_.matWorld.m[3][2]
	//};
	return worldPos;
}

void Enemy::OnCollision()
{
	isAlive_ = false;
}

void Enemy::Intiailize( const std::string& directoryPath, const std::string& filename, Coordinate pos)
{
	obj3d_ = new Obj3D;
	obj3d_->Initialize( directoryPath, filename);

	pos_ = pos;
	enemyState = new EnemyStateApproach;
	bulletpos_.scale = pos_.scale;
	bulletpos_.rotate = pos_.rotate;
	bulletpos_.translate = pos_.translate;
	bulletpos_.color = { 1.0f,1.0f,0.0f,1.0f };
	bullet = new EnemyBullet;
	bullet->Intiailize(bulletpos_);
	steCollisionAttribute(kCollisionAttributeEnemyr);
	steCollisionMask(~kCollisionAttributeEnemyr);
}

void Enemy::Update(Player* player)
{
	
	enemyState->Update(this);
	const float kBulletSpeed = -1.0f;
	//
	bullet->Updet(pos_,player);
	pos_.UpdateMatrix();
}

void Enemy::Draw(TexProeerty tex, CameraProjection pro)
{
	if (isAlive_)
	{
		obj3d_->Draw(pos_.scale, pos_.rotate, pos_.translate, pos_.color, pro, tex);
		bullet->Draw(pro);
	}

}
