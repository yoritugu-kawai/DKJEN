#pragma once

#include"../Math/Math.h"
#include"../Base/DxCommon.h"
class WorldTransform
{
public:
	void Create();
	void UpdateMatrix();
	ID3D12Resource* CreateBufferResource(size_t sizeInbyte);

#pragma region Get
	Matrix4x4 GetMatWorld_() { return matWorld_; }
	Vector3 GetScale() { return scale_; }
	Vector3 GetRotate() { return rotate_; }
	Vector3 GetTranslate() { return translate_; }
	Vector4 GetColor() {return color_;}
	ID3D12Resource* GetColl() { return buffer_.Get(); }
#pragma endregion

#pragma region Set
	void SetScale(Vector3 scale) { scale_ = scale; }
	void SetRotate(Vector3 rotate) { rotate_ = rotate; }
	void SetTranslate(Vector3 translate) { translate_ = translate; }
	void SetColor(Vector4 color) { color_ = color; }

#pragma endregion
private:
	Vector3 scale_;
	Vector3 rotate_;
	Vector3 translate_;
	Vector4 color_;
	Matrix4x4 matWorld_;
	Vector3 data_ ;
	ComPtr<ID3D12Resource> buffer_ = nullptr;
};
