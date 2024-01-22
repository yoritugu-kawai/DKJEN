#pragma once
#include "../Enemy/IEnemyState.h"
#include "../Enemy/Enemy.h"
#include "../../DKJEN/Math/Math.h"
class EnemyStateLeave : public IEnemyState {
public:
	void Update(Enemy* enemy) override;

private:
	
};
