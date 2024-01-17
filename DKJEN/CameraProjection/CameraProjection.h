#pragma once
#include"../Math/Math.h"
#include"../Base/WinApp.h"

struct CameraProjection {
	Matrix4x4 projection;      
	Matrix4x4 view;
	Vector3 rotate;
	Vector3 translate;

	float aspectRiot_ =1280.0f / 720.0f;
	float fov_ = 0.45f;

	float nearClip_ = 0.1f;
	float farClip_= 1000.0f;

	void Initialize();

	void Update();
};


