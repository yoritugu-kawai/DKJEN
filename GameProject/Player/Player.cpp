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
void Player::Intiailize(TexProeerty  tex, const std::string& directoryPath, const std::string& filename, const std::string& directoryPath2, const std::string& filename2, Coordinate pos)
{
	//GameResource
	obj3d_ = new Obj3D;
	obj3d_->Initialize( directoryPath, filename);
	obj3d2_ = new Obj3D;
	obj3d2_->Initialize(directoryPath2, filename2);
	sprite2DReticle_ = new Sprite;
	sprite2DReticle_->Initialize(tex);
	pos_ = pos;
	ReticlePos.translate = { 720.0f,360.0f,0.0f };
	ReticlePos.scale = { 0.1f,0.2f,0.1f };
	ReticlePos.rotate = { 0.0f,0.0f,0.0f };
	ReticlePos.color = { 1.0f,1.0f,1.0f,1.0f };
	bulletPos_.color = { 1.0f,1.0f,1.0f,1.0f };
	steCollisionAttribute(kCollisionAttributePlayer);
	steCollisionMask(~kCollisionAttributePlayer);
}

void Player::Update(CameraProjection pro)
{


	Input::GetInstance()->NoneJoyState(joyState);
	if (Input::GetInstance()->GetJoystickState(joyState)) {
		pos_.translate.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		pos_.translate.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}
	if (Input::GetInstance()->PushKey(DIK_A)) {
		pos_.translate.x -= 0.05f;
		pro.translate.x -= 0.05f;
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

	const float kDistancePlayerTo3DRetocle = 50.0f;

	// 3Dレティクル
	Vector3 Pos;
	Pos.x = pos_.matWorld.m[3][0];
	Pos.y = pos_.matWorld.m[3][1];
	Pos.z = pos_.matWorld.m[3][2];
	Vector3 offset = { 0, 0, 1.0f };
	offset = TransFormNormal(offset, pos_.matWorld);
	offset = Normalize(offset);
	offset.x *= kDistancePlayerTo3DRetocle;
	offset.y *= kDistancePlayerTo3DRetocle;
	offset.z *= kDistancePlayerTo3DRetocle;
	worldTransform3DReticle_.translate.x = offset.x + Pos.x;
	worldTransform3DReticle_.translate.y = offset.y + Pos.y;
	worldTransform3DReticle_.translate.z = offset.z + Pos.z;
	worldTransform3DReticle_.UpdateMatrix();
	//worldTransform3DReticle_.TransferMatrix();

	// 2Dレティクル

	positionReticle.x = worldTransform3DReticle_.matWorld.m[3][0];
	positionReticle.y = worldTransform3DReticle_.matWorld.m[3][1];
	positionReticle.z = worldTransform3DReticle_.matWorld.m[3][2];

	if (Input::GetInstance()->GetJoystickState(joyState)) {
		ReticlePos.translate.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 5.0f;
		ReticlePos.translate.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 5.0f;
		//sprite2DReticle_->SetPosition(ReticlePos);
	}


	GetMouse(pro);

	Attack();
	
	if (!Input::GetInstance()->GetJoystickState(joyState)) {
		return;
	}
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		sta = 1;
	}
	if (sta == 1) {
		tim += 1;
	pos_.translate.z += 0.05;
	}
	if (tim == 599) {
		sta = 0;
		pos_.translate.z = 0;
		tim = 0;
	}

	for (Bullet* bullet : bullets_) {
		bullet->Updet();
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

void Player::Attack()
{
	if (!Input::GetInstance()->GetJoystickState(joyState)) {
		return;
	}
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		//velocity = TransFormNormal(velocity, pos_.matWorld);
		Bullet* newBullet = new Bullet();
		
		velocity.x = worldTransform3DReticle_.translate.x - pos_.translate.x;
		velocity.y = worldTransform3DReticle_.translate.y - pos_.translate.y;
		velocity.z = worldTransform3DReticle_.translate.z - pos_.translate.z;
		velocity = Normalize(velocity);
		velocity.x *= kBulletSpeed;
		velocity.y *= kBulletSpeed;
		velocity.z *= kBulletSpeed;
	
		newBullet->Intiailize(bulletPos_, velocity);

		bullets_.push_back(newBullet);
	}
}

void Player::GetMouse(CameraProjection viewProjection) {
	POINT mousePosition;
	GetCursorPos(&mousePosition);
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);
	Vector2 Reticle;
	Reticle.x = float(ReticlePos.translate.x);
	Reticle.y = float(ReticlePos.translate.y);
	//sprite2DReticle_->SetPosition(Reticle);

	Matrix4x4 matVPV = Multiply(
		viewProjection.view,
		Multiply(
			viewProjection.projection,
			MakeViewportMatrix(0, 0, float(WinApp::Width()), float(WinApp::Height()), 0, 1)));
	Matrix4x4 matInveresVPV = Inverse(matVPV);

	Vector3 PosNear = Vector3(float(ReticlePos.translate.x), float(ReticlePos.translate.y), 0);
	Vector3 PosFar = Vector3(float(ReticlePos.translate.x), float(ReticlePos.translate.y), 1);
	//
	PosNear = Transform3(PosNear, matInveresVPV);
	PosFar = Transform3(PosFar, matInveresVPV);
	// マウスレイ
	Vector3 mouseDirection = Add(PosFar, PosNear);
	mouseDirection = Normalize(mouseDirection);
	const float kDistanceTestobject = 50.0f;
	worldTransform3DReticle_.translate.x = PosNear.x + mouseDirection.x * kDistanceTestobject;
	worldTransform3DReticle_.translate.y = PosNear.y + mouseDirection.y * kDistanceTestobject;
	worldTransform3DReticle_.translate.z = PosNear.z + mouseDirection.z * kDistanceTestobject;
	//
	worldTransform3DReticle_.UpdateMatrix();
	//worldTransform3DReticle_.TransferMatrix();
	rot.y += 0.05f;
}
void Player::Draw(TexProeerty  tex, CameraProjection pro)
{
	

	obj3d_->Draw(pos_.scale, pos_.rotate, pos_.translate, pos_.color, pro, tex );
	obj3d2_->Draw(pos_.scale, rot, pos_.translate, pos_.color, pro, tex);
	for (Bullet* bullet : bullets_) {
		bullet->Draw(pro);
	}
	sprite2DReticle_->Darw(ReticlePos.scale, ReticlePos.rotate, ReticlePos.translate, ReticlePos.color);
}

void Player::OnCollision()
{
}
