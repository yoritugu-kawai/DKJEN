#include "Enemy.h"

void Enemy::Intiailize(TexProeerty tex, const std::string& directoryPath, const std::string& filename, Coordinate pos)
{
	obj3d_ = new Obj3D;
	obj3d_->Initialize(tex, directoryPath, filename);

	pos_ = pos;

	
}

void Enemy::Update()
{
	pos_.translate.z -= 0.05f;
	if (pos_.translate.z<=-10) {
		pos_.translate.z = 10.0f;
		pos_.translate.x = 0.0f;
		pos_.translate.y = 0.0f;
	}
	if (pos_.translate.z<3)
	{

		pos_.translate.x += 0.1f;
		pos_.translate.y += 0.1f;
	}
}

void Enemy::Draw(CameraProjection pro)
{
	obj3d_->Draw(pos_.scale, pos_.rotate, pos_.translate, pos_.color, pro);
}
