#pragma once
#include "../Enemy/IEnemyState.h"
#include "../Enemy/Enemy.h"
#include "../../DKJEN/Math/Math.h"
#include"EnemyLeaveh.h"
class EnemyStateApproach : public IEnemyState {
public:
	void Update(Enemy* enemy)override;

private:
	Coordinate pos_ ;
};
