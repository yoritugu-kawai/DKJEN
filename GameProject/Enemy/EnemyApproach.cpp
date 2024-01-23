#include "EnemyApproach.h"

void EnemyStateApproach::Update(Enemy* enemy)
{
	/*pos_.translate.x = 0;
	pos_.translate.y = 0;
	pos_.translate.z = 0;

	pos_.rotate.x = 0;
	pos_.rotate.y = 0;
	pos_.rotate.z = 0;
	
	pos_.scale.x = 0;
	pos_.scale.y = 0;
	pos_.scale.z = 0;
	pos_.color = { 1.0f,1.0f,1.0f,1.0f };
	pos_.translate.z -= 0.05f;*/
	enemy->SetPos(Add(enemy->GetPos().translate, enemy->GetVelocty()));
	if (enemy->GetPos().translate.z < 5)
	{
		enemy->StateChange(new EnemyStateLeave);
	}


}
