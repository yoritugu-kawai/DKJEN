#include "EnemyApproach.h"

void EnemyStateApproach::Update(Enemy* enemy)
{
	pos_.translate.z -= 0.05f;
	enemy->SetPos(pos_);
	if (enemy->GetPos().translate.z < 3)
	{
		enemy->StateChange(new EnemyStateLeave);
	}
}
