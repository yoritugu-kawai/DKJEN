#include "Skydome.h"

void Skydome::Intiailize( const std::string& directoryPath, const std::string& filename)
{
	obj3d_ = new Obj3D;
	obj3d_->Initialize( directoryPath, filename);
	pos_.scale = { 50.0f,50.0f,50.0f };
	pos_.rotate = { 0.0f,0.0f,0.0f };
	pos_.translate = { 0.0f,0.0f,0.0f };
	pos_.color = { 1.0f,1.0f,1.0f,1.0f };
}

void Skydome::Update()
{
}

void Skydome::Draw(TexProeerty tex, CameraOperation pro)
{
	obj3d_->Draw(pos_.scale, pos_.rotate, pos_.translate, pos_.color, pro,tex );
}
