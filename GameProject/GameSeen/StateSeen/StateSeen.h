#pragma once
#include"../../../DKJEN/Utilipy/Input.h"
class StateSeen {
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

private:
	
};