#pragma once
#include"../StateSeen/StateSeen.h"
#include"../PlaySeen/PlaySeen.h"
class StartSeen : public StateSeen {
public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
private:

};