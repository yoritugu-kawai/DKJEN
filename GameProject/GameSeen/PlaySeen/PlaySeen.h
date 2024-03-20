#pragma once
#include"../StateSeen/StateSeen.h"
#include"../../Enemy/Enemy.h"
#include"../../Player/Player.h"

class PlaySeen : public StateSeen {
public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
private:
	Player* player_;
	Enemy* enemy_;
	bool des = false;
	
};