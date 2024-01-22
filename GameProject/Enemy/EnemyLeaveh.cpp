#include "EnemyLeaveh.h"

void EnemyStateLeave::Update(Enemy* enemy)
{

	if (enemy->GetPos().translate.z < 3)
	{

		enemy->SetPos().translate.x += 0.1f;
		pos_.translate.y += 0.1f;
	}
}
