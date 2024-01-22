#include "EnemyLeaveh.h"

void EnemyStateLeave::Update(Enemy* enemy)
{

	
		pos_.translate.x += 0.1f;
		pos_.translate.y += 0.1f;
		
	if (pos_.translate.z <= -10) {
		pos_.translate.z = 10.0f;
		pos_.translate.x = 0.0f;
		pos_.translate.y = 0.0f;

	}
		enemy->SetPos(pos_);
}
