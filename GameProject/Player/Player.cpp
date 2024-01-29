#include "Player.h"
#include"../../DKJEN/Utilipy/Input.h"

Player::~Player()
{

	for (Bullet* bullet : bullets_) {
		delete bullet;
	}
}
Vector3 Player::GetWorldPosition() {
	Vector3 result
	{
		this->pos_.matWorld.m[3][0],
		this->pos_.matWorld.m[3][1],
		this->pos_.matWorld.m[3][2]
	};
	return result;
}
void Player::Intiailize( const std::string& directoryPath, const std::string& filename, Coordinate pos)
{
	//GameResource
	obj3d_ = new Obj3D;
	obj3d_->Initialize( directoryPath, filename);

	pos_ = pos;
	
	bulletPos_.color = { 1.0f,1.0f,1.0f,1.0f };
	steCollisionAttribute(kCollisionAttributePlayer);
	steCollisionMask(~kCollisionAttributePlayer);
}

void Player::Update()
{
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		//velocity = TransFormNormal(velocity, pos_.matWorld);
		velocity = Normalize(velocity);

		Bullet* newBullet = new Bullet();
		newBullet->Intiailize(bulletPos_, velocity);
		
		bullets_.push_back(newBullet);
	}

	for (Bullet* bullet : bullets_) {
		bullet->Updet();
	}
	if (Input::GetInstance()->PushKey(DIK_A)) {
		pos_.translate.x -= 0.05f;
	}
	if (Input::GetInstance()->PushKey(DIK_D)) {
		pos_.translate.x += 0.05f;
	}
	if (Input::GetInstance()->PushKey(DIK_S)) {
		pos_.translate.y -= 0.05f;
	}
	if (Input::GetInstance()->PushKey(DIK_W)) {
		pos_.translate.y += 0.05f;
	}
	if (Input::GetInstance()->PushKey(DIK_K)) {
		pos_.rotate.y += 0.05f;

	}
	if (Input::GetInstance()->PushKey(DIK_UP)) {

		pos_.translate.z += 0.05f;
	}

	if (Input::GetInstance()->PushKey(DIK_DOWN)) {

		pos_.translate.z -= 0.05f;
	}

	bulletPos_.scale = pos_.scale;
	bulletPos_.rotate = pos_.rotate;
	bulletPos_.translate = pos_.translate;
	bullets_.remove_if([](Bullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});
	pos_.UpdateMatrix();
}

void Player::Draw(TexProeerty  tex, CameraProjection pro)
{
	obj3d_->Draw(pos_.scale, pos_.rotate, pos_.translate, pos_.color, pro, tex );
	for (Bullet* bullet : bullets_) {
		bullet->Draw(pro);
	}
}

void Player::OnCollision()
{
}
